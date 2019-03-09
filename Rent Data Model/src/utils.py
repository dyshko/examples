import calendar
import datetime

from dateutil import relativedelta


def str_to_date(s):
    if s == "":
        return None
    return datetime.datetime.strptime(s, "%Y-%m-%d").date()


def read_csv(filename):
    with open(filename) as f:
        return f.readlines()[1:]  # omit header


def months_between(date1, date2):
    r = relativedelta.relativedelta(date2, date1)
    return abs(12 * r.years) + abs(r.months)


def add_months(source_date, months):
    month = source_date.month - 1 + months
    year = source_date.year + month // 12
    month = month % 12 + 1
    day = min(source_date.day, calendar.monthrange(year, month)[1])
    return datetime.date(year, month, day)
