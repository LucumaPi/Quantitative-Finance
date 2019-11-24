class Payoff
{

public:
		double K;

		Payoff () { K = 120.0;}
		Payoff (double strike) { K = strike;}

		double Call(double S) {return S - K;}
		double Put(double S) {return K - S;}
};