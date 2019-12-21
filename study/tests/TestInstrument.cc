// TestInstrument.cpp
#include <duffy/Instrument.hh>
#include <duffy/BSIBVPImp.hh>

InstrumentFactory* GetInstrumentFactory()
{
	return new ConsoleInstrumentFactory;
}

int main()
{
	InstrumentFactory* myFactory = GetInstrumentFactory();
	Option* myOption = myFactory ->CreateOption();
	// class IBVPImp { };
	// class BSImp : public IBVPImp
	// {
	// public:
	// 	Option* opt;
	// 	BSImp() {}
	// };
 	// Derived implementation class
 	BSIBVPImp bs (*myOption);
 	bs.opt = myOption;

	return 0;
}