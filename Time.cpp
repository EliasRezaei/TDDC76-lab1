#include "Time.h"
#include <sstream>
#include <iomanip>

// free function definition
std::ostream& operator<<(std::ostream& os, const Time& rhs)
{
    os << rhs.to_string();
    return os;
}


Time::Time()
    : m_hours(0), m_minutes(0), m_seconds(0), m_ms(0)
{

}


Time::Time(int hours, int minutes, int seconds, int ms)
    : m_hours(hours), m_minutes(minutes), m_seconds(seconds), m_ms(ms)
{
    if (!valid_time(hours, minutes, seconds, ms))
    {
        throw std::logic_error("Not a valid time!");
    }
}



Time::Time(std::string time_string)
// do not use initializtion list since we need to read from the string first
{
    std::string str;
    std::stringstream time_stream{time_string};
    
    getline(time_stream, str, ':');
    try
    {
        m_hours = std::stoi(str);
    }
    catch (const std::exception& e)
    {
        throw std::logic_error("Not a valid input! don't use letters for hour, use numbers");
    }

    getline(time_stream, str, ':');
    try
    {
        m_minutes = std::stoi(str);
    }
    catch (const std::exception& e)
    {   
        throw std::logic_error("Not a valid input! don't use letters for minutes, use numbers");
    }


    getline(time_stream, str, '.');
    try
    {
        m_seconds = std::stoi(str);
    }
    catch (const std::exception& e)
    {
        throw std::logic_error("Not a valid input! don't use letters for seconds, use numbers");
    }


    getline(time_stream, str);
    try 
    {
        m_ms = std::stoi(str);
    }
    catch (const std::exception& e)
    {
        throw std::logic_error("Not a valid input! don't use letters for mili seconds, use numbers");
    }

    if (!valid_time(m_hours, m_minutes, m_seconds, m_ms))
    {
        throw std::logic_error("Not a valid time!");
    }
    // convert string to three ints

}

bool Time::valid_time(const int hours, const int minutes, const int seconds, const int ms) const
{
    if (hours < 0 || hours > 23 || minutes < 0 || seconds < 0 || seconds > 59 || minutes > 59 || ms > 999 || ms < 0)
        return false;
    else
        return true;
}

std::string Time::to_string(TimeFormat setting) const
{
    std::string res_string;

    switch (setting)
    {
        case (TimeFormat::Format24h):
        {
            res_string = format_string(m_hours, m_minutes, m_seconds, m_ms);
            break;
        }
        case (TimeFormat::Format12h):
        {
            if (is_am())
            {
                res_string = format_string(m_hours, m_minutes, m_seconds, m_ms) + "am";
            }
            else
            {
                res_string = format_string(m_hours - 12, m_minutes, m_seconds, m_ms)  + "pm";
            }
            break;
        }    
    
    }
    return res_string;
}

std::string Time::format_string(const int hours, const int minutes, const int seconds, const int ms) const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) <<  minutes << ":"
        << std::setfill('0') << std::setw(2) <<  seconds;
    if (ms != 0)
    {
        ss << "." 
        << std::setfill('0') << std::setw(3) <<  ms;
    }
    return ss.str();
}


bool Time::is_am() const
{
    if(m_hours < 12)
        return true;
    else
        return false; 
}


int Time::get_hour() const
{
    return m_hours;
}


int Time::get_minute() const
{
    return m_minutes;
}


int Time::get_second() const
{
    return m_seconds;
}

int Time::get_ms() const
{
    return m_ms;
}

Time& Time::operator++()
{
    int hours = m_hours;
    int minutes = m_minutes;
    int seconds = m_seconds;

    if (m_seconds == 59 )
    {
        seconds = 0;
        if (m_minutes == 59)
        {
            minutes = 0;
            if (m_hours == 23)
            {
                hours = 0;
            }
            else
                hours++;

        }
        else 
        {
            minutes++;
        }

    }
    else
        seconds++;

    m_hours = hours;
    m_minutes = minutes;
    m_seconds = seconds;

    return (*this);
}

Time Time::operator++(int)
{
    int hours = m_hours;
    int minutes = m_minutes;
    int seconds = m_seconds;

    if (m_seconds == 59 )
    {
        seconds = 0;
        if (m_minutes == 59)
        {
            minutes = 0;
            if (m_hours == 23)
            {
                hours = 0;
            }
            else
                hours=m_hours+1;
        }
        else 
        {
            minutes++;
        }

    }
    else
        seconds++;

    Time resultTime{m_hours, m_minutes, m_seconds, m_ms};

    m_hours = hours;
    m_minutes = minutes;
    m_seconds = seconds;
    
    return resultTime;
}


bool Time::operator<(const Time &rhs) const
{
    return (this->time_in_ms() < rhs.time_in_ms());
}

bool Time::operator>(const Time &rhs) const
{
    return (this->time_in_ms() > rhs.time_in_ms());
}

bool Time::operator<=(const Time &rhs) const
{
    return (this->time_in_ms() <= rhs.time_in_ms());
}

bool Time::operator>=(const Time &rhs) const
{
    return (this->time_in_ms() >= rhs.time_in_ms());
}

bool Time::operator==(const Time &rhs) const
{
    return (this->time_in_ms() == rhs.time_in_ms());
}

bool Time::operator!=(const Time &rhs) const
{
    return (this->time_in_ms() != rhs.time_in_ms());
}

float Time::operator-(const Time &rhs) const
{
    return ( float(this->time_in_ms() -(rhs.time_in_ms())) / 1000.f);

}


int Time::time_in_ms() const
{
    return (m_hours * 3600 * 1000) + (m_minutes * 60 * 1000) + (m_seconds * 1000) + m_ms;
}
