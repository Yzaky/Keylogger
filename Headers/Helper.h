//
// Created by youssef on 10/05/17.
//

#ifndef MYKEYLOGGER_HELPER_H
#define MYKEYLOGGER_HELPER_H
#include <sstream>
#include <ctime>
#include <fstream>

using namespace std;


template<typename T>
string toString(const T t)
{
    stringstream str;
    str<<t;
    return str.str();
}

class Helper {

public:
    struct dateTime
    {
        int Day,Month,Year,Min,Hour,Seconds;

        dateTime(){
            time_t ms;
            time(&ms);
            struct tm *info=localtime(&ms);
            Day = info->tm_mday;
            Month = info->tm_mon+1;
            Year = info->tm_year + 1900;
            Min=info->tm_min;
            Hour=info->tm_hour;
            Seconds=info->tm_sec;
        }

      /*  dateTime(int Day,int Month, int Year, int Min, int Hour, int Seconds):
                Day(Day), Month(Month), Year(Year), Min(Min), Hour(Hour), Seconds(Seconds){}

        dateTime(int Day, int Month, int Year):Day(Day),Month(Month),Year(Year){}*/

        dateTime Now() const {
        return dateTime();
        }

    string getDate() const         //to Return Day.Month.Year
    {
        return string(Day<10?"0":"")+toString(Day)+"."
                +string(Month<10?"0":"")+toString(Month)+"."
                +toString(Year);
    }

        string getTime()const {

            return string(Hour<10?"0":"")+toString(Hour)+":"
                    +string(Min<10?"0":"")+toString(Min)+":"
                    +string(Seconds<10?"0":"")+toString(Seconds);

        }

        string getDateTime()const{
            return getDate()+" : "+getTime();
        }
    };


};

void writeLog(const string s)
{
    ofstream file("log.txt",ios::app);
    file<<"["<< Helper::dateTime().getDateTime()<< "]"<<endl;
    file<<s<<endl;
    file.close();
}


#endif //MYKEYLOGGER_HELPER_H
