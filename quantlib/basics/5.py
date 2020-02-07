# Term structures and their reference dates
from QuantLib import *

Settings.instance().evaluationDate = Date(3, October, 2014)

helpers = [ SwapRateHelper(QuoteHandle(SimpleQuote(rate/100.0)),
    Period(*tenor), TARGET(),
    Annual, Unadjusted,
    Thirty360(),
    Euribor6M())
    for tenor, rate in [((2, Years), 0.201),
        ((3, Years), 0.258),
        ((5, Years), 0.464),
        ((10, Years), 1.151),
        ((15, Years), 1.588)] ]
curve1 = PiecewiseFlatForward(0, TARGET(), helpers, Actual360())

#TODO: check zip
dates, rates = zip(*curve1.nodes())
zip(dates, rates)
[(Date(3, 10, 2014), 0.001977769487929138),
    (Date(7, 10, 2016), 0.001977769487929138),
    (Date(9, 10, 2017), 0.0036475517704511913),
    (Date(7, 10, 2019), 0.007660760701876774),
    (Date(8, 10, 2024), 0.018414773669420816),
    (Date(8, 10, 2029), 0.025311634328221432)]

curve2 = ForwardCurve(dates, rates, Actual360())

f"{curve1.referenceDate()} to {curve1.maxDate()}"
f"{curve2.referenceDate()} to {curve2.maxDate()}"

curve1.zeroRate(5.0, Continuous)
curve2.zeroRate(5.0, Continuous)

curve1.zeroRate(Date(7, September, 2019), Actual360(), Continuous)
curve2.zeroRate(Date(7, September, 2019), Actual360(), Continuous)

%%capture
%pylab inline --no-import-all
import matplotlib.pyplot as plt
import pylab
pylab.rcParams['figure.figsize'] = [12, 8]
import numpy as np

times = np.linspace(0.0, 15.0, 400)
rates = [ curve1.zeroRate(t, Continuous).rate() for t in times ]
plt.plot(times, rates)

Settings.instance().evaluationDate = Date(19, September, 2014)

f"{curve1.referenceDate()} to {curve1.maxDate()}"
f"{curve2.referenceDate()} to {curve2.maxDate()}"

curve1.zeroRate(5.0, Continuous)
curve2.zeroRate(5.0, Continuous)

curve1.zeroRate(Date(7, September, 2019), Actual360(), Continuous)
curve2.zeroRate(Date(7, September, 2019), Actual360(), Continuous)

def make_observer(i):
    def say():
        s = f"Observer {i} notified"
        print("-"*len(s))
        print(s)
        print("-"*len(s))
    return Observer(say)

obs1 = make_observer(1)
obs2 = make_observer(2)


q1 = SimpleQuote(1.0)
obs1.registerWith(q1)

q2 = SimpleQuote(1.0)
obs2.registerWith(q2)

q3 = SimpleQuote(3.0)
obs1.registerWith(q3)
obs2.registerWith(q3)

q1.setValue(1.5)

q2.setValue(1.9)

q3.setValue(3.1)

obs1.registerWith(curve1)
obs2.registerWith(curve2)

Settings.instance().evaluationDate = Date(23, September, 2014)