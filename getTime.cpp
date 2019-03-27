#include "getTime.h"
#include <cstring>
#include <time.h>
using namespace std;
void getTime(char* p)
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    strcpy(p,tmp);
}