from QuantLib import *
import math

calendar = UnitedStates()
business_convention = ModifiedFollowing
settlement_days = 0
day_count = ActualActual()

interest_rate = 0.00105
calc_date = Date(1, 12, 2015)
yield_curve = FlatForward(calc_date, interest_rate, day_count, Compounded, Continuous)
Settings.instance().evaluationDate = calc_date
option_maturity_date = Date(24, 12, 2015)
strike = 119
spot = 126.953 #future price
volatility = 11.567/100
flavor = Option.Call

discount = yield_curve.discount(option_maturity_date)
strikepayoff = PlainVanillaPayoff(flavor, strike)
T = yield_curve.dayCounter().yearFraction(calc_date, option_maturity_date)
stddev = volatility*math.sqrt(T)
black = BlackCalculator(strikepayoff, spot, stddev, discount)

f"Option Price: {black.value()}"
f"Delta: {black.delta(spot)}"
f"Gamma: {black.gamma(spot)}"
f"Theta: {black.theta(spot, T)}"
f"Vega: {black.vega(T)}"
f"Rho: {black.rho(T)}"

interest_rate = 0.0015
calc_date = Date(23, 9, 2015)
yield_curve = FlatForward(calc_date, interest_rate, day_count, Compounded, Continuous)
Settings.instance().evaluationDate = calc_date
T = 96.12/365

strike = 3.5
spot = 2.919
volatility = 0.4251
flavor = Option.Call

discount = yield_curve.discount(T)
strikepayoff = PlainVanillaPayoff(flavor, strike)
stddev = volatility*math.sqrt(T)

strikepayoff = PlainVanillaPayoff(flavor, strike)
black = BlackCalculator(strikepayoff, spot, stddev, discount)
f"Option Price: {black.value()}"
f"Delta: {black.delta(spot)}"
f"Gamma: {black.gamma(spot)}"
f"Theta: {black.theta(spot, T)}"
f"Vega: {black.vega(T)}"
f"Rho: {black.rho(T)}"

