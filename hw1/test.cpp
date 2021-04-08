#include <ctime>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>

using namespace std;
int main()
{
    time_t tt;
    time(&tt);
    tt = tt + 8*3600;
    struct timeval  tv;
    struct timezone tz;
    struct tm         *p;
    gettimeofday(&tv, &tz);
    p = localtime(&tv.tv_sec);
    char str[20] = {0};
    struct timeval stuCurrentTime;

    gettimeofday(&stuCurrentTime, NULL);
    sprintf(str, "%ld%03ld", stuCurrentTime.tv_sec, (stuCurrentTime.tv_usec)/1000);
    unsigned long time_now = (unsigned long)stuCurrentTime.tv_sec * 1000 + ((unsigned long)stuCurrentTime.tv_usec)/1000;
    cout << str << endl;
    cout << time_now << endl;
}