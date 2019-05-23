#!/usr/bin/env python
# coding=utf-8

import datetime
import calendar

today = datetime.date.today()
target_day = calendar.FRIDAY
this_day = today.weekday()
delta_to_target = (this_day - target_day) % 7
last_friday = today - datetime.timedelta(days = delta_to_target)

print(last_friday.strftime("%d-%b-%y"))
