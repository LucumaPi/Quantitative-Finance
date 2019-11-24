// TestMultiAsset.cpp

#include "MultiAssetPayoffStrategy.hpp"
#include "MultiAssetFactory.hpp"

int main()
{

	MultiAssetFactory fac;
	fac.display();

	MultiAssetPayoffStrategy* Payoff;

	cout << "Choice: "; int choice; cin >> choice;

	try
	{
		Payoff = fac.create(choice);
	}
	catch(string& error)
	{
		cout << error << endl;
	}

	return 0;
}
