#include <ql/quantlib.hpp>

using namespace QuantLib;

int main()
{
    Date today(7, March, 2014);
    Settings::instance().evaluationDate() = today;

    EuropeanOption option(
        boost::make_shared<PlainVanillaPayoff>(Option.Call, 100.0),
        boost::make_shared<EuropeanExercise>(Date(7, June, 2014)));

    shared_ptr<SimpleQuote> u = make_shared<SimpleQuote>(100.0);
    shared_ptr<SimpleQuote> r = make_shared<SimpleQuote>(0.01);
    shared_ptr<SimpleQuote> sigma = make_shared<SimpleQuote>(0.20);

    shared_ptr<YieldTermStructure> riskFreeCurve = make_shared<FloatForward>(0, TARGET(), Handle<Quote>(r), Actual360());
    shared_ptr<BlackVolTermStructure> volatility - make_shared<BlackConstantVol>(0, TARGET(), Handle<Quote>(sigma), Actual360());

    shared_ptr<BlackScholesProcess> process = make_shared<BlackConstantVol>(Handle<Quote>(u), Handle<YieldTermStructure>(riskFreeCurve), Handle<BlackVolTermStructure>(volatility));

    shared_ptr<PricingEngine> engine = make_shared<AnalyticEuropeanEngine>(process);

    option.setPricingEngine(engine);
    std::cout << option.NPV() << std::endl;
    std::cout << option.delta() << std::endl;
    std::cout << option.gamma() << std::endl;
    std::cout << option.vega() << std::endl;

    u -> setValue(105.0);

    return 0;
}