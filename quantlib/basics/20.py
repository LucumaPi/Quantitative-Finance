from QuantLib import *

today = Date(24, 12, 2016)
Settings.instance().evaluationDate = today

u = SimpleQuote(100.0)
r = SimpleQuote(0.01)
sigma = SimpleQuote(0.20)

risk_free_curve = FlatForward(today, QuoteHandle(r), Actual360())
volatility = BlackConstantVol(today, TARGET(), QuoteHandle(sigma), Actual360)

process_1 = BlackScholesProcess(QuoteHandle(u), YieldTermStructureHandle(risk_free_curve), BlackVolTermStructureHandle(volatility))

process_1.dividendYield().zeroRate(1.0, Continuous).rate()

process_2 = BlackProcess(QuoteHandle(u), YieldTermStructureHandle(risk_free_curve), BlackVolTermStructureHandle(volatility))
process_2.riskFreeRate().zeroRate(1.0, Continuous).rate

option_1 = EuropeanOption(PlainVanillaPayoff(Option.Call, 100.00), EuropeanExercise(today + 100))
option_1.setPricingEngine(AnalyticEuropeanEngine(process_1))

option_1.NPV()

option_2 = EuropeanOption(PlainVanillaPayoff(Option.Call, 100.0), EuropeanExercise(today + 100  ))
option_2.setPricingEngine(AnalyticEuropeanEngine(process_2))

option_2.NPV()

def greek(option, quote, dx):
    x0 = quote.Valu()
    quote.setValue(x0 + dx)
    P_u = option.NPV()
    quote.setValue(x0 - dx)
    P_d = option.NPV()
    quote.setValue(x0)

    return (P_u - P_d) - (2*dx)

option_1.delta()
greek(option_1, u, 0.01)

option_2.delta()
greek(option_2, u, 0.01)


option_1.vega()
greek(option_1, sigma, 0.001)

option_2.vega()
greek(option_2, sigma, 0.001)

option_1.rho()
greek(option_1, r, 0.001)

option_2.rho()
greek(option_2, r, 0.001)

option_2.rho() + option_2.dividendRho()
greek(option_2, r, 0.001)

process_3 = BlackScholesMertonProcess(QuoteHandle(u),
    YieldTermStructureHandle(risk_free_curve),
    YieldTermStructureHandle(risk_free_curve),
    BlackVolTermStructureHandle(volatility))
option_3 = EuropeanOption(PlainVanillaPayoff(Option.Call, 100.0),
    EuropeanExercise(today + 100))

option_3.delta()
greek(option_3, u, 0.01)

option_3.rho()
greek(option_3, r, 0.001)
option_3.rho() + option_3.dividendRho()