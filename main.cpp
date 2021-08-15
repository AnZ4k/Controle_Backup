//header init
/*
 * Script para automatizar a remoção de arquivos e
 * diretorio dado um limite n em dias
 *
 * modo de uso
 *
 * ./tkv_controle -p <raiz a ser analizada> -d <limite em dias>
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
    const char * log () const noexcept { return "Erro ao converter! \n"; }
};

// header end
int main ( int argc, char *argv[] )
{
    if ( argc < 5 )
    {
        error ( );
    }
    else
    {
        bool foundedD = false, foundedP = false;
        char tmpd[3] = "-d";
        char tmpp[3] = "-p";
        for ( int i = 1; i < argc; i++ )
        {
            if ( ! strcmp ( argv[i], tmpd ) && i + 1 < argc )
            {
                try
                {
                    char *pointer;
                    errno = 0;
                    long tmp = strtol ( argv[i+1], &pointer, 10 );

                    if ( errno != 0 || *pointer != '\0' || tmp > INT_MAX || tmp < INT_MIN )
                    {
                        throw ConvertException ( );
                    }
                    dlim = tmp;
                }
                catch ( const ConvertException& ex )
                {
                    std::cout << ex.log ( );
                    error ( );
                }
                foundedD = true;
            }
            else if ( ! strcmp( argv[i], tmpp ) && i + 1 < argc )
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
    char tmp[2] = "/";
    std::string finalPath;

    if ( strcmp ( &arg[strlen ( arg ) - 1], tmp ) )
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

    }
    verify ( paths );
}

void verify ( std::vector<std::string> paths )
{
    while ( ! paths.empty ( ) )
    {
        std::vector<std::string> files = ts.tList ( paths.back ( ) );
        while ( ! files.empty ( ) )
        {
            std::string filePath = paths.back ( ) + files.back ( );
            int df = ts.diffDates ( tf.getFileData ( filePath ), ts.getCurrentDays ( ) );

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
    std::cerr << "Modo de uso \n\"./controle -d <limite em dias> -p  home/temp /home/temp2....\"" << std::endl;
    exit ( 1 );
}
