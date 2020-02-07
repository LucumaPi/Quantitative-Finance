# 1. QuantLib Basics
# Date, Period, Calendar and Schedule
from QuantLib import *

# Date class
# month(), dayOfMonth(), year(), weekday()
date = Date(31, 3, 2015)
date

f"{date.month()} {date.dayOfMonth()} {date.year()}"

date.weekday() == Tuesday

# arithmetic operations: days, weeks, months
# The Date arithmetic not take holidays into account
f"Add a day: {date + 1}"
f"Substract a day: {date - 1}"

# Period class
# Period(num_periods, period_type)
# num_periods is an integer 
# period_type: Weeks, Months, Years
period = Period(60, Days)

f"Add a week: {date + Period(1, Weeks)}"
f"Add a month: {date + Period(1, Months)}"
f"Add a year: {date + Period(1, Years)}"

# logical operations
date == Date(31, 3, 2015)
date > Date(30, 3, 2015)
date > Date(1, 4, 2015)
date != Date(1,4,2015)

# Calendar Class
# Take holidays days
date = Date(1,4,2015)
us_calendar = UnitedStates()
italy_calendar = Italy()

period = Period(60, Days)
raw_date = date + period
us_date = us_calendar.advance(date, period)
italy_date = italy_calendar.advance(date, period)

f"Add 60 days: {raw_date}"
f"Add 60 business days in US: {us_date}"
f"Add 60 business days in Italy: {italy_date}"

# addHoliday, removeHoliday, businessDaysBetween are methods of Calendar class
us_busdays = us_calendar.businessDaysBetween(date, us_date)
italy_busdays = italy_calendar.businessDaysBetween(date, italy_date)

f"Business days US: {us_busdays}"
f"Business days Italy {italy_busdays}"

joint_calendar = JointCalendar(us_calendar, italy_calendar)
join_date = joint_calendar.advance(date, period)
joint_busdays = joint_calendar.businessDaysBetween(date, join_date)

f"Add 60 business days in US-Italy: {join_date}"
f"Business days US-Italy: {joint_busdays}"

# Schedule Class
# Schedule(const Date& effectiveDate,
#     const Date& terminationDate,
#     const Period& tenor,
#     const Calendar& calendar,
#     BusinessDayConvention convention,
#     BusinessDayConvention terminationDateConvention,
#     DateGeneration::Rule rule,
#     bool endOfMonth,
#     const Date& firstDate = Date())

# Schedule(const std::vector<Date>&,
#     const Calendar& calendar,
#     BusinessDayConvention rollingConvention)

effective_date = Date(1, 1, 2015)
termination_date = Date(1, 1, 2016)
tenor = Period(Monthly)
calendar = UnitedStates()
business_convention = Following
termination_business_convention = Following
date_generation = DateGeneration.Forward
end_of_month = False

schedule = Schedule(effective_date,
    termination_date,
    tenor,
    calendar,
    business_convention,
    termination_business_convention,
    date_generation,
    end_of_month)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

# short stub in the front
effective_date = Date(1, 1, 2015)
termination_date = Date(1, 1, 2016)
first_date = Date(15, 1, 2015)

schedule = Schedule(effective_date,
    termination_date,
    tenor,
    calendar,
    business_convention,
    termination_business_convention,
    DateGeneration.Backward,
    end_of_month,
    first_date)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

# short stub at the back
effective_date = Date(1, 1, 2015)
termination_date = Date(1, 1, 2016)
penultimate_date = Date(15, 12, 2015)

schedule = Schedule(effective_date,
    termination_date,
    tenor,
    calendar,
    business_convention,
    termination_business_convention,
    DateGeneration.Forward,
    end_of_month,
    Date(),
    penultimate_date)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

# long stub in the front
first_date = Date(1, 2, 2015)
effective_date = Date(15, 12, 2014)
termination_date = Date(1, 1, 2016)

schedule = Schedule(effective_date,
    termination_date,
    tenor,
    calendar,
    business_convention,
    termination_business_convention,
    DateGeneration.Backward,
    end_of_month,
    first_date)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

# long stub at the back
effective_date = Date(1, 1, 2015)
penultimate_date = Date(1, 12, 2015)
termination_date = Date(15, 1, 2016)

schedule = Schedule(effective_date,
    termination_date,
    tenor,
    calendar,
    business_convention,
    termination_business_convention,
    DateGeneration.Forward,
    end_of_month,
    Date(),
    penultimate_date)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

dates = [Date(2, 1, 2015), Date(2, 2, 2015),
    Date(2, 3, 2015), Date(1, 4, 2015),
    Date(1, 5, 2015), Date(1, 6, 2015),
    Date(1, 7, 2015), Date(3, 8, 2015),
    Date(1, 9, 2015), Date(1, 10, 2015),
    Date(2, 11, 2015), Date(1, 12, 2015),
    Date(4, 1, 2016)]

rolling_convention = Following
schedule  = Schedule(dates, calendar, rolling_convention)

for i, d in enumerate(schedule):
    print(f"{i + 1} {d}")

# Interest Rate
annual_rate = 0.05
day_count = ActualActual()
compound_type = Compounded
frequency = Annual

interest_rate = InterestRate(annual_rate,
    day_count,
    compound_type,
    frequency)

t = 2.0
interest_rate.compoundFactor(t)
(1 + annual_rate)*(1.0 + annual_rate)

# discountFactor
interest_rate.discountFactor(t)
1.0/interest_rate.compoundFactor(t)

new_frequency = Semiannual
new_interest_rate = interest_rate.equivalentRate(compound_type, new_frequency, t)
new_annual_rate = new_interest_rate.rate()

new_annual_rate

interest_rate.discountFactor(t)
new_interest_rate.discountFactor(t)

# impliedRate, equivalenceRate are methods of InterestRate class