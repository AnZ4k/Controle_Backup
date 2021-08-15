//header init
/*
 * Script para automatizar a remoção de backups com mais de 60 dias
 *
 * Autor: Gustavo Henrrike
 *
 * github: AnZ4K
 *
 * contato: anzak.h.sanders@gmail.com
 *
 * criado em: 01/07/2021
 *
 */

// preprocessor diretives
#include "core/includes.h"
#include "core/tFile.h"
#include "core/tSystem.h"

// functions prototipe
std::string generatePath ( char *arg );
void run ( int *argc, char ** arglist );

//public declarations
tFile tf;
tSystem ts;
// header end
int main ( int argc, char **argv)
{
    if ( argc < 2 )
    {
        std::cerr << "Modo de uso \n./controle /home/temp /home/temp2....\"" << std::endl;

        exit ( 1 );
    }
    else
    {
        run ( &argc, argv );
    }

    return 0;
}

std::string generatePath ( char *arg )
{
    return " ";
}


void run ( int *argc, char ** arglist )
{
    std::vector<std::string> paths;
    for ( int i = 1; i < *argc; i++ )
    {
        if ( ts.validate ( generatePath ( arglist[i] ) ) )
            paths.push_back ( generatePath ( arglist[i] ) );
        else
        {
            std::cerr << "O caminho " << argc[i] << " não é valido!" << std::endl;
            exit ( 1 );
        }
    }
}
