#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "Date.h"

Date::Date() {
}

Date::Date(int year, int month, int day, int hour, int minute) {
    year_ = year;
    month_ = month;
    day_ = day;
    hour_ = hour;
    minute_ = minute;
}

int Date::getYear(void) const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth(void) const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.year_ > 9999 || date.year_ < 1000)
        return  false;
    if (date.month_ < 1 || date.month_ > 12)
        return  false;
    if (date.day_ < 1)
        return false;

    if (date.month_ == 2) {
      if ((date.year_%4 == 0 && date.year_%100 != 0)||(date.year_%400 == 0)) {
       if (date.day_ > 29)
         return false;
      } else if (date.day_ > 28) {
        return false;
       }
     } else if (date.day_ > months[date.month_-1]) {
         return false;
       }

    if (date.hour_ > 23 || date.hour_ < 0)
      return false;
    if (date.minute_ > 59 || date.minute_ < 0)
      return false;

    return true;
}

Date Date::stringToDate(std::string dateString) {
    std::string strYear, strMonth, strDay, strHour, strMinute;
    Date date;
    int dateLength = dateString.length();
    int intMonth, intDay, intHour;
    int dateYear, dateMonth, dateDay, dateHour, dateMinute;
    int i;

    for (i = 5; i < dateLength; i++) {
      if (dateString[i] == '-') {
        intMonth = i;
        break;
      }
    }

    for (i = i + 1; i < dateLength; i++) {
      if (dateString[i] == '/') {
        intDay = i;
        break;
      }
    }

    for (i = i + 1; i < dateLength; i++) {
      if (dateString[i] == ':') {
        intHour = i;
        break;
      }
    }

    strYear = dateString.substr(0, 4);
    dateYear = atoi(&strYear[0]);
    date.setYear(dateYear);
    strMonth = dateString.substr(5, intMonth-4-1);
    dateMonth = atoi(&strMonth[0]);
    date.setMonth(dateMonth);
    strDay = dateString.substr(intMonth+1, intDay-intMonth-1);
    dateDay = atoi(&strDay[0]);
    date.setDay(dateDay);
    strHour = dateString.substr(intDay+1, intHour-intDay-1);
    dateHour = atoi(&strHour[0]);
    date.setHour(dateHour);
    strMinute = dateString.substr(intHour+1, dateLength-intHour-1);
    dateMinute = atoi(&strMinute[0]);
    date.setMinute(dateMinute);

    return date;
}

std::string Date::dateToString(Date date) {
    std::string dateString;
    std::string str;
    char tmp1[10], tmp2[10], tmp3[10], tmp4[10], tmp5[10];

    snprintf(tmp1, sizeof(tmp1), "%d", date.year_);
    str = tmp1;
    dateString = str + '-';
    str = "";

    snprintf(tmp2, sizeof(tmp2), "%d", date.month_);
    str = tmp2;
    if (str.length() < 2)
      str = '0' + str;
    dateString = dateString + str + '-';
    str = "";

    snprintf(tmp3, sizeof(tmp3), "%d", date.day_);
    str = tmp3;
    if (str.length() < 2)
      str = '0' + str;
    dateString = dateString + str + '/';
    str = "";

    snprintf(tmp4, sizeof(tmp4), "%d", date.hour_);
    str = tmp4;
    if (str.length() < 2)
      str = '0' + str;
    dateString = dateString + str + ':';
    str = "";

    snprintf(tmp5, sizeof(tmp5), "%d", date.minute_);
    str = tmp5;
    if (str.length() < 2)
      str = '0' + str;
    dateString = dateString + str;
    str = "";

    return dateString;
}

Date& Date::operator= (const Date& date) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;

    return *this;
}

bool Date::operator== (const Date& date) const {
    if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_ &&
       hour_ == date.hour_ && minute_ == date.minute_)
       return true;
    else
       return false;
}

bool Date::operator> (const Date& date) const {
    if (year_ > date.year_)
     return true;
    else if (month_ > date.month_)
     return true;
    else if (day_ > date.day_)
     return true;
    else if (hour_ > date.hour_)
     return true;
    else if (minute_ > date.minute_)
     return true;
    else
     return false;
}

bool Date::operator< (const Date& date)const {
    if (*this > date || *this == date)
     return false;
    else
     return true;
}

bool Date::operator>= (const Date& date)const {
    if (*this > date || *this == date)
     return true;
    else
     return false;
}

bool Date::operator<= (const Date& date)const {
    if (*this > date)
     return false;
    else
     return true;
}
