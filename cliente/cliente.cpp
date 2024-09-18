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
    if (argc < 2) 
    {
        cerr << "USO: " << argv[0] << " <nome_do_servidor>\n";
        return 1;
    }

    if (argc > 2)
    {
        cerr << "USO: " << argv[0] << " <nome_do_servidor>   ~// e nada posterior //~\n";
        return 2;
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

        string chave, valor, valorRecuperado;
        int carrousel = 1;
        Boolean cadastrada;

        cout << "O que voce deseja fazer?\n";

        while (carrousel != 0)
        {
            cout << "\n~/~/~/~/~/~/~/~/~/~/~/~/~\n\n";
            cout << "1.Adicionar valor a uma chave na tabela.\n";
            cout << "2.Procurar por chave e retornar valor.\n";
            cout << "3.Deletar chave e valor da tabela.\n";
            cout << "0.Para sair da aplicacao.\n";
            cin >> carrousel;

            switch (carrousel)
            {
            case 1:
                cout<< "Digite a chave: "; cin >> chave;
                cout<< "Digite a valor: "; cin >> valor;

                cadastrada = conta->put(chave, valor);
                if (cadastrada)
                {
                    cout << "chave nova cadastrada\n";
                } 
                else
                {
                    cout << "chave  existente, valor alterado\n";
                }
                break;
            
            case 2:
                try
                {
                    cout << "chave a ser procurada: ";
                    cin >> chave;
                    valorRecuperado = conta->get(chave);
                    cout << "valor encontrado: " << valorRecuperado << endl;
                }
                catch(const InvalidKey& e)
                {
                    cerr << "InvalidKey exception: " << e._name() << endl;
                }
                break;

            case 3:
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
                break;

            default:
                cout << "Escolha uma das opcoes existentes\n";
                break;
            };
        };

        orb->destroy();
    }
    catch (const CORBA::Exception& e)
    {
        cerr << "ERRO CORBA: " << e << endl;
    }
    
    return 0;
}