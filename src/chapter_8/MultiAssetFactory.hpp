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

class MultiAssetFactory
{
public:
		MultiAssetFactory()
		{
			desc = std::map<int, std::string>();

			desc.insert(std::pair<int, std::string>(1, "Exchange option\n"));
			desc.insert(std::pair<int, std::string>(2, "Rainbow option\n"));
			desc.insert(std::pair<int, std::string>(3, "Basket option\n"));
			desc.insert(std::pair<int, std::string>(4, "BestWorst option\n"));
			desc.insert(std::pair<int, std::string>(5, "Quotient option\n"));
			desc.insert(std::pair<int, std::string>(6, "Quanto option\n"));
			desc.insert(std::pair<int, std::string>(7, "SpreadStrategy option\n"));
			desc.insert(std::pair<int, std::string>(8, "Dual Strike Strategy option\n"));
			desc.insert(std::pair<int, std::string>(9, "Out Perfomance option\n"));
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
				throw std::string("Outside range\n");
			}
		}

		void display()
		{ // Show options for a choice

			std::map<int, std::string>:: const_iterator it;

			for (it = desc.begin(); it != desc.end(); it++)
			{
				std::cout << (*it).first << ", " << (*it).second << std::endl;
			}
		}

private:

		std::map<int, std::string> desc;	// Description

MultiAssetPayoffStrategy* CreateExchangeStrategy()
{
	std::cout << desc[1];

	return new ExchangeStrategy;
}

MultiAssetPayoffStrategy* CreateRainbowStrategy()
{
	std::cout << desc[2];

	std::cout << "Strike K: "; double K; std::cin >> K;
	std::cout << "Call +1, Put -1: "; double w; std::cin >> w;
	std::cout << "Max(max) 1 or Max(min) 2: "; int type; std::cin >> type;

	return new RainbowStrategy(K, w, type);
}


MultiAssetPayoffStrategy* CreateBasketStrategy()
{
	std::cout << desc[3];

L1:
	std::cout << "Strike K: "; double K; std::cin >> K;
	std::cout << "Call +1, Put -1: "; double w; std::cin >> w;
	std::cout << "First weight: "; double w1; std::cin >> w1;
	std::cout << "Second weight: "; double w2; std::cin >> w2;
	if (w1 + w2 != 1.0)
	{
		std::cout << "Weights must add up to 1";
		goto L1;
	}

	return new BasketStrategy(K, w, w1, w2);

}

MultiAssetPayoffStrategy* CreateBestWorstStrategy()
{
	std::cout << desc[4];

	std::cout << "Strike(cash) K: "; double K; std::cin >> K;
	std::cout << "Best +1, Worst -1: "; double w; std::cin >> w;

	return new BestWorstStrategy(K, w);
}

MultiAssetPayoffStrategy* CreateQuotientStrategy()
{

	std::cout << desc[5];

	std::cout << "Strike K: "; double K; std::cin >> K;
	std::cout << "Call +1, Put -1: "; double w; std::cin >> w;

	return new QuotientStrategy(K, w);
}

MultiAssetPayoffStrategy* CreateQuantoStrategy()
{
	std::cout << desc[6];

	std::cout << "Strike K in foreign currency: "; double K; std::cin >> K;
	std::cout << "Fixed exchange rate: "; double fer; std::cin >> fer;
	std::cout << "Call +1, Put -1: "; double w; std::cin >> w;

	return new QuantoStrategy(K, w, fer);
}

MultiAssetPayoffStrategy* CreateSpreadStrategy()
{
	std::cout << desc[7];

	std::cout << "Strike K: "; double K; std::cin >> K;
	std::cout << "Call +1, Put -1: "; double w; std::cin >> w;
	std::cout << "Value 'a' > 0: "; double a; std::cin >> a;
	std::cout << "Value 'b' < 0: "; double b; std::cin >> b;

	return new SpreadStrategy(w, K, a, b);

}


MultiAssetPayoffStrategy* CreateDualStrikeStrategy()
{

	std::cout << desc[8];


	std::cout << "Strike K1: "; double K1; std::cin >> K1;
	std::cout << "Option1: Call  +1, Put -1: "; double w1; std::cin >> w1;

	std::cout << "Strike K2: "; double K2; std::cin >> K2;
	std::cout << "Option2: Call  +1, Put -1: "; double w2; std::cin >> w2;

	return new DualStrikeStrategy(K1, K2, w1, w2);

	
}


MultiAssetPayoffStrategy* CreateOutPerformanceStrategy()
{

	std::cout << desc[9];


	std::cout << "Underlying I1: "; double I1; std::cin >> I1;
	std::cout << "Underlying I2: "; double I2; std::cin >> I2;
	std::cout << "Strike rate of option: "; double k; std::cin >> k;
	std::cout << "Call  +1, Put -1: "; double w; std::cin >> w;

	return new OutPerformanceStrategy(I1, I2, w, k);

}

};

#endif