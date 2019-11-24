//
//
//		Title: MCDirector.cpp
//		
//		A dicussion of this software can be found in
//
//		Daniel Duffy, Joerg Kienitz "Monte Carlo Methods in Quantitative 
//		Finance: Generic and Efficient MC Solver in C++"
//
//		The framework in this MC is similar to those as described in chapters
//		15 and 16.
//
//		You can change values, uncomment out stuff and play around with the
//		framework.
//
//		Author: J. Kienitz	       
//		Date:   25.05.2005
/*
    Sources:
		MCStuff:
		--------
		MCVarReduction.cpp  
		MCPathGenerator.cpp
		MCPathEvolver
		MCPath.cpp
  		MCUnderlying.cpp,
		MCPayOff.cpp, 
		MCPathStructure.cpp

		Output Stuff:
		-------------
		MCOutput.cpp, 
		MCOutputStats.cpp

		Distributions:
		--------------
		NormalDistribution.cpp
		
		RNG:
		----
		CongRNG.cpp
		MT.cpp
		Halton.cpp
		MCRandomNumbers.cpp

		Options:
		--------
		Asian.cpp
		UpOut.cpp
  */


#include <iostream>
#include <valarray>
#include <vector>

using namespace std;

// MC Stuff
#include"MCVarReduction.h"
#include"MCPathGenerator_Euler.h"

// MC Output Stuff
#include"MCOutputStats.h"
#include"MCStats.h"

// Options
#include"Asian.h"
#include"UpOut.h"

//Random Numbers
#include"CongRNG.h"
#include"Halton.h"
#include"MT.h"
#include"RandomGeneratorTemplate.h"

int main()
{
// Input values, could come from other applications... e.g. Excel
	double Expiry=1.0;
	double Strike=23; 
	vector<double> Spot; 
	double Vol=0.25; 
	double r=0.03;
    double d=0.01;
	double quantile = 2.33;
	int CallPut = 0;
	int Type = 0;
//	int Dimension;
	unsigned long NumberMCPaths=100;
    unsigned long NumberOfDates=10;//=10;
	unsigned long NumberOfAssets=2;//=2;

	for (int i=0; i < NumberOfAssets; i++) Spot.push_back(100);

//	cin >> Dimension;

	MCPath times(NumberOfAssets, NumberOfDates);
	//valarray<MCPath> test(Dimension);
	//test[1]=times;

	
	cout <<"\nEnter Number of Dates\n";
	cin >> NumberOfDates;


	cout <<"\nNumber of Assets\n";
	cin >> NumberOfAssets;
/*
	cout <<"\nType\n";
	cin >> Type;

	cout <<"\nEnter spot\n";
	cin >> Spot;

	cout <<"\nEnter vol\n";
	cin >> Vol;


	cout <<"\nr\n";
	cin >> r;

    cout <<"\nd\n";
    cin >> d;

	cout <<"\nCall/Put 0/1\n";
	cin >> CallPut;

    cout <<"Number of dates\n";
    cin >> NumberOfDates;

	cout <<"\nNumber of paths\n";
	cin >> NumberMCPaths;
*/	
	PayOffCall thePayOff(Strike);

    for (int i=0; i < NumberOfDates; i++)// int i DD June 2006
        times[i] = (i+1.0)*Expiry/NumberOfDates;
	
	//MCPath montecarlopath(NumberOfAssets, NumberOfDates);
	MCPath montecarlopath;
	montecarlopath.resize(NumberOfDates, NumberOfAssets);

	//test[2]=montecarlopath;

	//Works with constant parameters, i.e. the Black-Scholes model
    MCUnderlyingParamsConstant VolParam(Vol);
    MCUnderlyingParamsConstant rParam(r);
    MCUnderlyingParamsConstant dParam(d);

	//For testing purposes choose between UpOut, Asian, PlainVanilla
    Asian theOption(times, Expiry, thePayOff);
	//UpOut theOption(times,Expiry,thePayOff);

    //StatsParam statscollect(quantile);

    //MCOutput statscollectTwo(statscollect);
	
	//Init RNGs, currently ran0, ran1, Mersenne Twister
	//RandGen<Ran0> rangen(15,15);
	RandGen<Halton> rangenerator(NumberOfAssets * NumberOfDates, 15);
	rangenerator.GenerateUniforms(montecarlopath);
	
	//generator.SetSeed(0);
	
	//generator.GenerateNormals(montecarlopath);
	//generator.GenerateQuasiRandomSequence(montecarlopath);  
	//generator.GenerateUniforms(montecarlopath);	
	//generator.GenerateNormals(montecarlopath);
	//VarReduction
    //AntiThetic GenTwo(generator);

	//GeneratePath theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot, Type);
	//GeneratePath_Euler theEngine(theOption, rParam, dParam, VolParam, rangenerator, Spot, Type);

    //theEngine.MCSimulation(statscollectTwo, NumberMCPaths);

    //vector<vector<double>> results = statscollectTwo.GetResults();

	cout <<"\nFor the Options call price the results are \n";
	cout <<"\nRunning Average, Running Vol, CI_Low, CI_High, Runs \n";

	//montecarlopath.insert(0,0,5555.0);
	
	for(int i=0; i < NumberOfAssets;++i)	// DD int i declared
	{		
		for (int j=0; j < NumberOfDates; ++j)
		{
			cout << i <<";" << j <<" :" << montecarlopath(i,j) <<"   ";
			cout <<"\n";
		}
	}

	double tmp;
    cin >> tmp;

	return 0;
}
