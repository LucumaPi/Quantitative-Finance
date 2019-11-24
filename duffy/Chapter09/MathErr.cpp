// MathErr.cpp
//
// C++ exception hierarchy (sample) to show 
// how to model exceptions.
// We have modelled the exceptions based on the
// .NET way of treating exceptions.
//
// (C) Datasim Education BV 2005
//

#include <string>
#include <vector>
using namespace std;
#include <iostream>

class MathErr
{ // Base class for my current exceptions
private:
		string mess;	// The error message
		string meth;	// The method that threw the exception
public:
		MathErr()
		{
			mess = meth = string();
		}

		MathErr (const string& message, const string& method)
		{
			mess = message;
			meth = method;
		}

		string Message() const { return mess; }
		string Method() const { return meth; }

		virtual vector<string> MessageDump() const = 0;
	
		virtual void print() const
		{ 
			// This uses a Template method pattern

			// Variant part
			vector<string> r = MessageDump();

			// Invariant part
			for (int j = 0; j < r.size(); j++)
			{
				cout << r[j] << endl;
			}
		}

};


class ZeroDivide : public MathErr
{
private:

		string mess;	// Extra information

public:
		ZeroDivide() : MathErr()
		{
			mess = string();
		}

		ZeroDivide(const string& message,const string& method, const string& annotation ) 
			: MathErr (message, method)
		{
			mess = annotation;
		}

		vector<string> MessageDump() const
		{ // Full message

			vector<string> result(3);
			result[0] = Message();
			result[1] = Method();
			result[2] = mess;
			return result;
		}

};

class OutOfBounds : public MathErr
{
private:
			int ind;
public:
		OutOfBounds() : MathErr()
		{
		}

		OutOfBounds(const string& message, const string& method, int index) 
			: MathErr (message, method)
		{
			ind = index;
		}

		int offendingIndex() const { return ind;}

		vector<string> MessageDump() const
		{ // Full message

			vector<string> result(3);
			result[0] = Message();
			result[1] = Method();
		//	result[2] = ind;
			return result;
		}

};

class GeneralMathErr : public MathErr
{ // Kind of 'catch all' exception object

private:

public:
		GeneralMathErr() : MathErr()
		{
			
		}

		GeneralMathErr(const string& message, const string& method) 
			: MathErr (message, method)
		{}

};
