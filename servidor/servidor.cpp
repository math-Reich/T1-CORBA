#include <iostream>
#include <fstream>
#include <string>
#include "CEtcdI.h"
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

        Object_ptr temp = orb->resolve_initial_references("RootPOA");
        POA_var poa = POA::_narrow(temp);
        POAManager_var ger = poa->the_POAManager();
        ger->activate();

        CEtcd_i servant1;
        CEtcd_var CEtcd = servant1._this();

        temp = orb->resolve_initial_references("NameService");
        NamingContext_var ns = NamingContext::_narrow(temp);

        Name nome(1);
        nome.length(1);
        nome[0].id = string_dup(argv[1]);

        ns->rebind(nome, CEtcd.in());

        cout << "Aguardando comandos..\n";
        orb->run();

        poa->destroy(1, 1);
        orb->destroy();
    }
    catch(const CORBA::Exception& e)
    {
        cerr << "ERRO CORBA: " << e << endl;
    }
    
    return 0;
}