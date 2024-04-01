#include <iostream>
#include <ctime>

std::tm *getDateFromTime(long long milliseconds)
{
    // Convert milliseconds to time_t (seconds since epoch)
    time_t seconds = milliseconds / 1000;

    // Convert time_t to struct tm
    std::tm *timeinfo = std::localtime(&seconds);

    timeinfo->tm_year += 1900;
    timeinfo->tm_mon += 1;
    return timeinfo;
}
