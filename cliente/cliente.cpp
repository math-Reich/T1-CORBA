#include <iostream>
#include <string>
#include "../servidor/CEtcdI.h"
#include <orbsvcs/CosNamingC.h>

using namespace std;
using namespace CORBA;
using namespace PortableServer;
using namespace CosNaming;

ORB_var orb;

int main (int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "USO: " << argv[0] << " <nome_do_servidor>\n";
        return 1;
    }

    try
    {
        orb = ORB_init(argc, argv, "ORB");

        Object_ptr temp = orb->resolve_initial_references("NameService");
		NamingContext_var ns = NamingContext::_narrow(temp);

        Name nome(1);
        nome.length(1);
        nome[0].id = string_dup(argv[1]);

        temp = ns->resolve(nome);
        CEtcd_var conta = CEtcd::_narrow(temp);

        string chave, valor;

        cout<< "Digite a chave: ";
        cin >> chave;

        cout<< "Digite a valor: ";
        cin >> valor;

        Boolean cadastrada = conta->put(chave, valor);
        if (cadastrada)
        {
            cout << "chave nova cadastrada\n";
        } 
        else
        {
            cout << "chave  existente, valor alterado\n";
        }

        try
        {
            cout << "chave que quer buscar: ";
            cin >> chave;
            string valorRecuperado = conta->get(chave);
            cout << "valor encontrado: " << valorRecuperado << endl;
        }
        catch(const InvalidKey& e)
        {
            cerr << "InvalidKey exception: " << e._name() << endl;
        }
        
        try
        {
            cout << "chave para deletar: ";
            cin >> chave;
            conta->del(chave);
            cout << "chave deletada\n";
        }
        catch(const InvalidKey& e)
        {
            cerr << "InvalidKey exception: " << e._name() << endl;
        }

        orb->destroy();
    }
    catch (const CORBA::Exception& e)
    {
        cerr << "ERRO CORBA: " << e << endl;
    }
    
    return 0;
}