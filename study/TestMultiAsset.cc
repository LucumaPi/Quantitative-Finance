// TestMultiAsset.cpp

#include <duffy/MultiAssetFactory.hh>

int main()
{

	MultiAssetFactory fac;
	fac.display();

	MultiAssetPayoffStrategy* Payoff;

	std::cout << "Choice: "; int choice; std::cin >> choice;

	try
	{
		Payoff = fac.create(choice);
	}
	catch(std::string& error)
	{
		std::cout << error << std::endl;
	}

	return 0;
}