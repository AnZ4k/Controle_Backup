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
void verify ( std::vector<std::string> paths );
void error ( void );

//public declarations
tFile tf;
tSystem ts;
int dlim;

//global structs
struct ConvertException : std::exception
{
    const char * log () const noexcept { return "Erro ao converter! \n";}
};

// header end
int main ( int argc, char *argv[])
{
    if ( argc <= 5 )
    {
        error ( );
    }
    else
    {
        bool foundedD = false, foundedP = false;
        char tmpd[2] = {'-','d'};
        char tmpp[2] = {'-','p'};
        for ( int i = 1; i < argc; i++ )
        {
            if ( strcmp( argv[i], tmpd) && i + 1 < argc)
            {
                try
                {
                    std::istringstream iss ( argv [i + 1] );

                    if (! iss >> dlim )
                    {
                        //throw ConvertException ( );
                    }
                }
                catch ( const ConvertException& ex )
                {
                    std::cout << ex.log ( );
                    error ( );
                }
                foundedD = true;
            }
            else if ( strcmp( argv[i], tmpp) && i + 1 < argc)
            {
                foundedP = true;
            }
        }
        if ( foundedD && foundedP )
        {
            run ( &argc, argv );
        }
        else
            error ( );
    }

    return 0;
}

std::string generatePath ( char *arg )
{
    char tmp[1] = { '/' };
    std::string finalPath;

    if ( strcmp(&arg[(sizeof ( *arg ) / sizeof ( arg[0] ) ) - 1], &tmp[0]) != 0 )
        finalPath = (std::string) arg + "/";
    else
        finalPath = (std::string) arg;

    return finalPath;
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
            std::cerr << "O caminho " << arglist[i] << " não é valido!" << std::endl;
            exit ( 1 );
        }
    }
    verify ( paths );
}

void verify(std::vector<std::string> paths)
{
    while ( ! paths.empty ( ) )
    {
        std::vector<std::string> files = ts.tList ( paths.back ( ) );
        while ( ! files.empty ( ) )
        {
            std::string filePath = paths.back ( ) + files.back ( );
            int df = ts.diffDates ( tf.getFileData ( filePath ),        ts.getCurrentDays ( ) );

            if ( df >= dlim )
			{
				std::cout << "O arquivo " << filePath << " Foi deletado após " << dlim << " dias. \n" << std::endl;
				ts.tDelete ( filePath );
			}
			else if ( df == ( dlim - 1 ) )
			{
				std::cout << "O arquivo " << filePath << " Sera deletado amanhã. \n" << std::endl;
			}
			else
			{
				std::cout << "O arquivo " << filePath << " Não foi deletado pois ainda faltam " << dlim - df << " dias. \n" << std::endl;
			}

            files.pop_back ( );
        }
        paths.pop_back ( );

    }
}

void error ( void )
{
    std::cerr << "Modo de uso \n./controle -d <limite em dias> -p  home/temp /home/temp2....\"" << std::endl;
    exit ( 1 );
}
