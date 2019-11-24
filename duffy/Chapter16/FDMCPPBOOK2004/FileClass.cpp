#include "FileClass.hpp"


FileClass::FileClass():leap(0){;}

FileClass::FileClass(const long & Start):leap(Start - 1){;}

FileClass::~FileClass(){;}

void FileClass::SetAxis(const Vector<double,long> & X,
                        const Vector<Vector<double,long>,long > & Y)
{
	X_Axis = X;
	Y_Axis = Y;
}
	
void FileClass::WriteToFile()
{
	// loop over the values at the x-axis. Skip the first "leap" values
	for(long i = X_Axis.MinIndex()+leap; i <= X_Axis.MaxIndex(); i++)
	{
		// print the current x-value to file
		fprintf(outputfile,"\n%f \t",X_Axis[i]);
		
		// loop over the possible y-values
		for(long j = Y_Axis.MinIndex();
		    j <= Y_Axis.MaxIndex();
		    j++)
		{
			// print current y-value to file
			fprintf(outputfile,"%f ",Y_Axis[j][i]);
		}
	}
	fclose(outputfile);	// close the output file

}

// set the filename
void FileClass::SetFileName(char * name)
{ outputfile = fopen(name,"w"); }
