#include "tSystem.h"

bool tSystem::leapYear ( int year )
{
	/*
	 * Função responsvel por detectar se o ano é bissexto
	 *
	 */

	if ( year % 4 != 0 )
	{
		return false;
	}
	if  ( year % 100 == 0 && year % 400 != 0 )
	{
		return false;
	}

	return true;
}


std::vector<std::string> tSystem::tList ( std::string path )
{
    /*
	 * Função responsavel por listar o conteudo do diretorio de backup
	 * e retornar um vector contendo o nome de todos os arquivos e
	 * diretorios
	 *
	 */

	DIR *dir = 0;
	struct dirent *input = 0;
	std::vector<std::string> dirs;

	dir = opendir ( path.c_str ( ) );

	if ( dir == 0 )
	{
		std::cerr << "Erro ao abrir o diretorio" << std::endl;
		exit ( 1 );
	}

	while ( ( input = readdir( dir ) ) )
	{
		dirs.push_back ( input->d_name );
	}
	closedir ( dir );

	return dirs;
}

void tSystem::tDelete ( std::string path )
{
    /*
	 * Função responsavel por deletar o arquivo ou diretorio
	 * quando o mesmo passar da data limite
	 *
	 */

	DIR *dir = opendir ( path.c_str ( ) );
	std::string command = "/bin/rm -rvf '" + path + "'";

	system ( command.c_str ( ) );
}

unsigned long tSystem::getCurrentDays ( )
{
	/*
	 * Função responsavel por retornar a quantidade de dias desde o ano 2000 até a data atual
	 *
	 */

	struct tm *timeinfo;
	time_t seconds;
	time ( &seconds );
	timeinfo = localtime ( &seconds );

	unsigned long returnDays = timeinfo->tm_yday;
	int years = timeinfo->tm_year + 1900;

	for ( int i = 2000; i < years; i++ )
	{
		if ( leapYear ( i ) )
		{
			returnDays += 366;
		}
		else
		{
			returnDays += 365;
		}
	}

	return returnDays;
}

int tSystem::diffDates ( std::vector<int> fdate, unsigned long systemDays )
{
    /*
	 * Função responsavel por retornar a diferença em dias entre a data do sistema
	 * e a data da modificação do arquivo
	 *
	 */

	int year = fdate.front ( );
	unsigned long days = fdate.back ( );
	for ( int i = 2000; i < year; i++ )
	{

		if ( leapYear ( i ) )
		{
			days += 366;
		}
		else
		{
			days += 365;
		}
	}

	return systemDays - days;
}

bool tSystem::validate ( std::string path )
{
    struct stat buffer;
    return ( stat ( path.c_str( ), &buffer ) == 0 );
}

