#include "tFile.h"

std::vector<int> tFile::getFileData(std::string path)
{
    /*
	 * Função responsavel por coletar informações do arquivo
	 * e retornar um vector contendo o ano e o yday (dia do ano 1-365/366)
	 * da ultima modificação feita no mesmo
	 *
	 */

	std::vector<int> fdate;
	struct stat buf;
	char buffer[4];
	tm* timeinfo;

    stat ( path.c_str ( ), &buf );
	time_t timeAr = buf.st_ctim.tv_sec;
	timeinfo = localtime ( &timeAr );
	strftime ( buffer, 4, "%y", timeinfo );
	fdate.push_back ( timeinfo->tm_year + 1900 );
	fdate.push_back ( timeinfo->tm_yday );

	return fdate;
}
