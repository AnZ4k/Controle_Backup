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

#include <sys/stat.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <dirent.h>
#include <cstdlib>
#include <string>

using namespace std;

bool leapYear ( int year );
vector<string> listDirs ( string path );
vector<int> getFileData ( string filePath );
int diffDates ( vector<int> daysMod, unsigned long daysSystem );
unsigned long getCurrentDays ( );
void deleteOutdatedDirs ( string path );


int main ( )
{
	vector<string> paths = {"/backups", "/share/backup-vm"};
	
	while ( ! paths.empty() )
	{
		vector<string> dirs = listDirs ( paths.back() );
		vector<int> dates;
		unsigned long actualDate = getCurrentDays ( );
		int limitDay = 60;				// data limite em dias

		while (! dirs.empty ( ) )	
		{
			string filePath = paths.back() + dirs.back ( );
			dates = getFileData ( filePath );
			dirs.pop_back ( );
			int diff = diffDates ( dates, actualDate );

			if ( diff >= limitDay )
			{
				cout << "O arquivo " << filePath << " Foi deletado após " << diff << " dias. \n" << endl;
				deleteOutdatedDirs ( filePath );
			}
			else if ( diff == (limitDay - 3))
			{
				cout << "O arquivo " << filePath << " Sera deletado em 3 dias. \n" << endl; 
			}
			else
			{	
				cout << "O arquivo " << filePath << " Não foi deletado pois ainda faltam " << 60 - diff << " dias. \n" << endl;
			}
		}
		paths.pop_back();
	}

	return 0;
}


bool leapYear ( int year )
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


vector<string> listDirs ( string path )
{
	/*
	 * Função responsavel por listar o conteudo do diretorio de backup
	 * e retornar um vector contendo o nome de todos os arquivos e 
	 * diretorios
	 *
	 */

	DIR *dir = 0;
	struct dirent *input = 0;
	vector<string> dirs;

	dir = opendir ( path.c_str () );

	if ( dir == 0 )
	{
		cerr << "Erro ao abrir o diretorio" << endl;
		exit ( 1 );
	}

	while ( input = readdir( dir ) )
	{ 
		dirs.push_back ( input->d_name );
	}
	closedir ( dir );

	return dirs;
}


vector<int> getFileData ( string filePath )
{
	/*
	 * Função responsavel por coletar informações do arquivo
	 * e retornar um vector contendo o ano e o yday (dia do ano 1-365/366) 
	 * da ultima modificação feita no mesmo
	 *
	 */

	vector<int> fdate;
	struct stat buf;
	char buffer[4];
	tm* timeinfo;
	
	stat ( filePath.c_str ( ), &buf );
	time_t timeAr = buf.st_ctim.tv_sec;
	timeinfo = localtime ( &timeAr );
	strftime ( buffer, 4, "%y", timeinfo );
	fdate.push_back ( timeinfo->tm_year + 1900 );
	fdate.push_back ( timeinfo->tm_yday );

	return fdate;
}


int diffDates ( vector<int> fdate, unsigned long systemDays )
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


unsigned long getCurrentDays ( )
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


void deleteOutdatedDirs ( string path )
{
	/*
	 * Função responsavel por deletar o arquivo ou diretorio
	 * quando o mesmo passar da data limite
	 * 
	 */

	DIR *dir = opendir ( path.c_str ( ) );
	string command = "/bin/rm -rvf '" + path + "'";
	
	system ( command.c_str ( ) );
}
