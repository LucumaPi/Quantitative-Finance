

//
//
//
//      MCPathGenerator_Euler.cpp
//
//		Implements Explicit Euler, Milstein Schemes for 1d-SDE. It is dero	
//
//		Author: J. Kienitz	       
//		Date:   11.08.2005

#include <MCPathGenerator_Euler.h>
#include <cmath>



void GeneratePath_Euler::GetOnePath(MCPath& SpotValues, int Type_) 
{

    TheGenerator->GenerateNormals(Variates);

    double CurrentSpot;

	for (unsigned long i = 0; i < NumberOfFactors; i++)
	{
		CurrentSpot = Spot[i];
		for (unsigned long j=0; j < NumberOfTimes; j++)
		{
			CurrentSpot += Drifts[i,j];
			CurrentSpot += Drifts2[i,j] * (Variates[i,j] * Variates[i,j]-1);
			CurrentSpot += Volatilities[i,j] * Variates[i,j];
			SpotValues[i,j] = CurrentSpot;
		}
	}
    return;
}


GeneratePath_Euler::GeneratePath_Euler(const MCTemplateClass<PathStructure>& TheProduct_,
						               const MCUnderlyingParams& R_,
						               const MCUnderlyingParams& D_,
						               const MCUnderlyingParams& Vol_,
						               const MCTemplateClass<Random>& TheGenerator_,
									   //const MCTemplateClass<QuasiRandom>& TheGenerator_,
									   std::vector<double> Spot_,
						               int Type_)
						               :
						               MCPathEvolver(TheProduct_,R_),
						               TheGenerator(TheGenerator_)
{
    MCPath Times(TheProduct_->DiscreteMonitorGetTimes());
    NumberOfTimes = Times.timesteps();
	NumberOfFactors = Times.factors();

    TheGenerator->ResetDimensionality(NumberOfTimes * NumberOfFactors);
	
	Drifts.resize(NumberOfTimes, NumberOfFactors);
	Drifts2.resize(NumberOfTimes, NumberOfFactors);
    Volatilities.resize(NumberOfTimes, NumberOfFactors);
	
    double Variance = Vol_.DiffusionPart(0,Times[0]);

	//Type = 0 Euler
	if(Type_ == 0)
	{
		for (unsigned long i=0; i < NumberOfFactors; ++i)
		{
			Drifts.insert(i,0,1.9);
			//Drifts[i,0] = 1.9;//R_.DriftPart(0.0,Times[i,0]);// - D_.DriftPart(0.0,Times[0]);
			//Drifts2[i,0] = 0.0;
			//Volatilities[i,0] = sqrt(Variance);
		 
		
			for (unsigned long j=1; j < NumberOfTimes; ++j)
			{   
				//Drifts[i,j] = R_.DriftPart(Times[j-1],Times[j]) - D_.DriftPart(Times[j-1],Times[j]);
				//Drifts2[i,j] = 0.0;
				//Volatilities[i,j] = sqrt(Vol_.DiffusionPart(Times[j-1],Times[j]));
			}
		}

		Spot[i] = Spot_[i];                                   
		Variates.resize(NumberOfTimes, NumberOfFactors);
	}

/*	//Type = 1 Milstein
	else
	{
		Drifts[0] = R_.DriftPart(0.0,Times[0])-D_.DriftPart(0.0,Times[0]);
		Drifts2[0] = 0.5 * Vol_.DiffusionPart(0.0, Times[0]);
		Volatilities[0] = sqrt(Variance);
		
		for (unsigned long j=1; j < NumberOfTimes; ++j)
		{   
			Drifts[j] = R_.DriftPart(Times[j-1],Times[j]) - D_.DriftPart(Times[j-1],Times[j]);
			Drifts2[j] = 0.5 * Vol_.DiffusionPart(0.0, Times[0]); 
			Volatilities[j] = sqrt(Vol_.DiffusionPart(Times[j-1],Times[j]));
		}

		Spot[i] = Spot_;                                   
		Variates.resize(NumberOfTimes, Variates.factors());
	}
*/

  }


