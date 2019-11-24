// TestTwoBasketOption.cpp
//
// Two basket options (PUT)
//
// (C) Datasim Education BV 2006
//

#include "instrument.hpp"

InstrumentFactory* GetInstrumentFactory()
{

	return new ConsoleInstrumentFactory;
}

int main()
{
	InstrumentFactory* myFactory = GetInstrumentFactory();
	TwoFactorOptionData* myOption = myFactory ->CreateOption();

	return 0;
}
