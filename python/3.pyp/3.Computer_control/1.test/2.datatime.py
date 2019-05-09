#!/usr/bin/env python
# coding=utf-8
import datetime,calendar

last_friday = datetime.date.today()
oneday = datetime.timedelta(days = 1)

while last_friday.weekday() != calendar.FRIDAY:
    last_friday -= oneday

print(last_friday.strftime('%A,%d-%b-%y'))


