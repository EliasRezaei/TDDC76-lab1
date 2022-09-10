#ifndef TIME
#define TIME

#include <iostream>
#include <stdexcept>


enum TimeFormat
{
    Format24h = 0,
    Format12h
};


class Time;

std::ostream& operator<<(std::ostream& os, const Time& rhs);



class Time
{

public:
    Time();
    Time(int hours, int minutes, int seconds, int ms = 0);

    Time(std::string time_string);

    std::string to_string(TimeFormat setting = TimeFormat::Format24h) const;
    bool is_am() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    
    Time& operator++();
    Time operator++(int);

    bool operator<(const Time &rhs) const;
    bool operator>(const Time &rhs) const;
    bool operator<=(const Time &rhs) const;
    bool operator>=(const Time &rhs) const;
    bool operator==(const Time &rhs) const;
    bool operator!=(const Time &rhs) const;

private:
    bool valid_time(int hours, int minutes, int seconds) const;
    int time_in_seconds() const;



private:
    int m_hours;
    int m_minutes;
    int m_seconds;
    int m_ms;


};


#endif
