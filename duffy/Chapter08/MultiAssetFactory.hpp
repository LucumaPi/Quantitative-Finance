// MultiAssetFactory.hpp
//
// Application of Factory Method pattern to create
// 2-factor asset payout functions.
//
// In this case we use an integer identifier (GOF page 110-111). This
// is handy and extendible. The actual data for the object is via console
// but we could use a Bridge at a later stage.
//
// Code is inline in this version.
//
// (C) Datasim Education BV 2006
//

#ifndef MultiAssetFactory_HPP
#define MultiAssetFactory_HPP

#include "MultiAssetPayoffStrategy.hpp"
#include <string>
#include <map>
#include <iostream>
using namespace std;

class MultiAssetFactory
{
public:
		MultiAssetFactory()
		{
			desc = map<int, string>();

			desc.insert(pair<int, string>(1, "Exchange option\n"));
			desc.insert(pair<int, string>(2, "Rainbow option\n"));
			desc.insert(pair<int, string>(3, "Basket option\n"));
			desc.insert(pair<int, string>(4, "BestWorst option\n"));
			desc.insert(pair<int, string>(5, "Quotient option\n"));
			desc.insert(pair<int, string>(6, "Quanto option\n"));
			desc.insert(pair<int, string>(7, "SpreadStrategy option\n"));
			desc.insert(pair<int, string>(8, "Dual Strike Strategy option\n"));
			desc.insert(pair<int, string>(9, "Out Perfomance option\n"));
		}

		virtual MultiAssetPayoffStrategy* create(int N)
		{

			if (N == 1) return CreateExchangeStrategy();
			if (N == 2) return CreateRainbowStrategy();
			if (N == 3) return CreateBasketStrategy();
			if (N == 4) return CreateBestWorstStrategy();
			if (N == 5) return CreateQuotientStrategy();
			if (N == 6) return CreateQuantoStrategy();
			if (N == 7) return CreateSpreadStrategy();
			if (N == 8) return CreateDualStrikeStrategy();
			if (N == 9) return CreateOutPerformanceStrategy();

			// Exception
			if (N > 9 || N < 1)
			{
				throw string("Outside range\n");

			}
		}

		void display()
		{ // Show options for a choice

			map<int, string>:: const_iterator it;

			for (it = desc.begin(); it != desc.end(); it++)
			{
				cout << (*it).first << ", " << (*it).second << endl;
			}
		}

private:

		map<int, string> desc;	// Description

MultiAssetPayoffStrategy* CreateExchangeStrategy()
{
	cout << desc[1];

	return new ExchangeStrategy;
}

MultiAssetPayoffStrategy* CreateRainbowStrategy()
{
	cout << desc[2];

	cout << "Strike K: "; double K; cin >> K;
	cout << "Call +1, Put -1: "; double w; cin >> w;
	cout << "Max(max) 1 or Max(min) 2: "; int type; cin >> type;

	return new RainbowStrategy(K, w, type);
}


MultiAssetPayoffStrategy* CreateBasketStrategy()
{
	cout << desc[3];

L1:
	cout << "Strike K: "; double K; cin >> K;
	cout << "Call +1, Put -1: "; double w; cin >> w;
	cout << "First weight: "; double w1; cin >> w1;
	cout << "Second weight: "; double w2; cin >> w2;
	if (w1 + w2 != 1.0)
	{
		cout << "Weights must add up to 1";
		goto L1;
	}

	return new BasketStrategy(K, w, w1, w2);

}

MultiAssetPayoffStrategy* CreateBestWorstStrategy()
{
	cout << desc[4];

	cout << "Strike(cash) K: "; double K; cin >> K;
	cout << "Best +1, Worst -1: "; double w; cin >> w;

	return new BestWorstStrategy(K, w);
}

MultiAssetPayoffStrategy* CreateQuotientStrategy()
{

	cout << desc[5];

	cout << "Strike K: "; double K; cin >> K;
	cout << "Call +1, Put -1: "; double w; cin >> w;

	return new QuotientStrategy(K, w);
}

MultiAssetPayoffStrategy* CreateQuantoStrategy()
{
	cout << desc[6];

	cout << "Strike K in foreign currency: "; double K; cin >> K;
	cout << "Fixed exchange rate: "; double fer; cin >> fer;
	cout << "Call +1, Put -1: "; double w; cin >> w;

	return new QuantoStrategy(K, w, fer);
}

MultiAssetPayoffStrategy* CreateSpreadStrategy()
{
	cout << desc[7];

	cout << "Strike K: "; double K; cin >> K;
	cout << "Call +1, Put -1: "; double w; cin >> w;
	cout << "Value 'a' > 0: "; double a; cin >> a;
	cout << "Value 'b' < 0: "; double b; cin >> b;

	return new SpreadStrategy(w, K, a, b);

}


MultiAssetPayoffStrategy* CreateDualStrikeStrategy()
{

	cout << desc[8];


	cout << "Strike K1: "; double K1; cin >> K1;
	cout << "Option1: Call  +1, Put -1: "; double w1; cin >> w1;

	cout << "Strike K2: "; double K2; cin >> K2;
	cout << "Option2: Call  +1, Put -1: "; double w2; cin >> w2;

	return new DualStrikeStrategy(K1, K2, w1, w2);

	
}


MultiAssetPayoffStrategy* CreateOutPerformanceStrategy()
{

	cout << desc[9];


	cout << "Underlying I1: "; double I1; cin >> I1;
	cout << "Underlying I2: "; double I2; cin >> I2;
	cout << "Strike rate of option: "; double k; cin >> k;
	cout << "Call  +1, Put -1: "; double w; cin >> w;

	return new OutPerformanceStrategy(I1, I2, w, k);

}

};

#endif