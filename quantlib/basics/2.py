from QuantLib import *

today = Date(7, March, 2014)
Settings.instance().evaluationDate = today

# Instrument class
option = EuropeanOption(PlainVanillaPayoff(Option.Call, 100.0),
    EuropeanExercise(Date(7, June, 2014)))

# First pricing method: analytic Black-Scholes formula
u = SimpleQuote(100.0)
r = SimpleQuote(0.01)
sigma = SimpleQuote(0.20)

riskFreeCurve = FlatForward(0, TARGET(), QuoteHandle(r), Actual360())
volatility = BlackConstantVol(0, TARGET(), QuoteHandle(sigma), Actual360())

process = BlackScholesProcess(QuoteHandle(u),
    YieldTermStructureHandle(riskFreeCurve),
    BlackVolTermStructureHandle(volatility))

engine = AnalyticEuropeanEngine(process)
option.setPricingEngine(engine)
option.NPV()

option.delta()
option.gamma()
option.vega()

# Market changes
u.setValue(105.0)
option.NPV()

%%capture
%pylab inline --no-import-all
import matplotlib.pyplot as plt
import numpy as np
from IPython.display import display

f, ax = plt.subplots()
xs = np.linspace(80.0, 120.0, 400)
ys = []
for x in xs:
    u.setValue(x)
    ys.append(option.NPV())
ax.set_title('Option value')
_ = ax.plot(xs, ys)

u.setValue(105.0)
r.setValue(0.01)
sigma.setValue(0.20)

option.NPV()

r.setValue(0.03)
option.NPV()

sigma.setValue(0.25)
option.NPV()

# Date changes
u.setValue(105.0)
r.setValue(0.01)
sigma.setValue(0.20)
option.NPV()

Settings.instance().evaluationDate = Date(7, April, 2014)
option.NPV()

ys = []
for x in xs:
    u.setValue(x)
    ys.append(option.NPV())
ax.plot(xs, ys, '--')
display(f)

Settings.instance().evaluationDate = Date(7, June, 2014)
option.NPV()

# Other pricing methods
Settings.instance().evaluationDate = today
u.setValue(105.0)
r.setValue(0.01)
sigma.setValue(0.20)

option.NPV()

model = HestonModel(HestonProcess(YieldTermStructureHandle(riskFreeCurve),
    YieldTermStructureHandle(FlatForward(0, TARGET(), 0.0, Actual360())),
    QuoteHandle(u),
    0.04, 0.1, 0.01, 0.05, -0.75))

engine = AnalyticHestonEngine(model)
option.setPricingEngine(engine)
option.NPV()


engine = MCEuropeanEngine(process, "PseudoRandom", timeSteps=20, requiredSamples=2500000)
option.setPricingEngine(engine)

%time option.NPV()

%time option.NPV()

u.setValue(104.0)

%time option.NPV()