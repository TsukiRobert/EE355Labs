#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;
class Date{
    private:
        int month, day, year;
        string d;

    public: 
        Date(std::string date);
        void print_date(std::string str);
        int get_month() const;
        std::string get_month_name() const;
        int get_day() const;
        int get_year() const;
        string get_date() const;
};

#endif 
