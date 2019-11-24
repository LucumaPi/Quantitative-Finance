// TestInstrument.cpp
//

#include "instrument.hpp"

InstrumentFactory* GetInstrumentFactory()
{

	return new ConsoleInstrumentFactory;
}

int main()
{
	InstrumentFactory* myFactory = GetInstrumentFactory();
	Option* myOption = myFactory ->CreateOption();

	class IBVPImp
	{

	};

	class BSImp : public IBVPImp
	{
	public:
	
		Option* opt;
		
		BSImp() {}
	};


	return 0;
}
