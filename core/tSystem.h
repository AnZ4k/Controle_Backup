#include "includes.h"

class tSystem
{
public:
    void tDelete ( std::string path );
    std::vector<std::string> tList  ( std::string path );
    unsigned long getCurrentDays ( void );
    int diffDates ( std::vector<int> fdate, unsigned long systemDays );
    bool validate ( std::string path );

private:
    bool leapYear ( int year );
};
