#include "Time.h"
#include <sstream>
#include <iomanip>
// free function definition
std::ostream& operator<<(std::ostream& os, const Time& rhs)
{

}

Time::Time()
    : m_hours(0), m_minutes(0), m_seconds(0)
{

}


Time::Time(int hours, int minutes, int seconds, int ms)
    : m_hours(hours), m_minutes(minutes), m_seconds(seconds)
{
    if (!valid_time(hours, minutes, seconds))
    {
        throw std::logic_error("Not a valid time!");
    }
};



Time::Time(std::string time_string)
{
    std::string str;
    std::stringstream time_stream{time_string};
    getline(time_stream,str,':');
    m_hours=std::stoi(str);
    getline(time_stream,str,':');
    m_minutes=std::stoi(str);
    getline(time_stream,str,':');
    m_seconds=std::stoi(str);
    if (!valid_time(m_hours,m_minutes,m_seconds))
    {
        throw std::logic_error("Not a valid time!");
    }

    
    // convert string to three ints

};

bool Time::valid_time(int hours, int minutes, int seconds) const
{
    if (hours > 23 || hours < 0 || minutes < 0 || seconds < 0 || seconds > 59 || minutes > 59 )
        return false;
    else
        return true;
}

std::string Time::to_string(TimeFormat setting) const
{
    std::string res_string;
    std::stringstream string_stream;

    switch (setting)
    {
        case (Format24h):
        {
            //FIXME:
            string_stream << std::setfill('0') << std::setw(2) << m_hours << ":"
                << std::setfill('0') << std::setw(2) <<  m_minutes << ":"
                << std::setfill('0') << std::setw(2) <<  m_seconds;

                res_string = string_stream.str();

            break;
        }
        case (Format12h):
        {
            if (is_am() == true)
            {

                string_stream << std::setfill('0') << std::setw(2) << m_hours << ":"
                    << std::setfill('0') << std::setw(2) <<  m_minutes << ":"
                    << std::setfill('0') << std::setw(2) <<  m_seconds << "am";

                res_string = string_stream.str();
            }
            else
            {
                string_stream << std::setfill('0') << std::setw(2) << m_hours - 12 << ":"
                    << std::setfill('0') << std::setw(2) <<  m_minutes << ":"
                    << std::setfill('0') << std::setw(2) <<  m_seconds << "pm";
            

                res_string = string_stream.str();
            }
            break;
        }    
    
    }
    return res_string;
};

bool Time::is_am() const
{
    if(m_hours < 12)
        return true;
    else
        return false; 

};


int Time::get_hour() const
{
    return m_hours;
};


int Time::get_minute() const
{
    return m_minutes;
};


int Time::get_second() const
{
    return m_seconds;
};


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
};

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

    Time resultTime{m_hours, m_minutes, m_seconds};

    m_hours = hours;
    m_minutes = minutes;
    m_seconds = seconds;
    
    return resultTime;
};


bool Time::operator<(const Time &rhs) const
{
    return (this->time_in_seconds() < rhs.time_in_seconds());
};

bool Time::operator>(const Time &rhs) const
{
    return (this->time_in_seconds() > rhs.time_in_seconds());
};

bool Time::operator<=(const Time &rhs) const
{
    return (this->time_in_seconds() <= rhs.time_in_seconds());
};

bool Time::operator>=(const Time &rhs) const
{
    return (this->time_in_seconds() >= rhs.time_in_seconds());
};

bool Time::operator==(const Time &rhs) const
{
    return (this->time_in_seconds() == rhs.time_in_seconds());
};

bool Time::operator!=(const Time &rhs) const
{
    return (this->time_in_seconds() != rhs.time_in_seconds());
};


int Time::time_in_seconds() const
{
    return m_hours*3600 + m_minutes * 60 + m_seconds;
};


