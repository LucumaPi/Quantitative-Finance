// MathErr.cpp
//
// C++ exception hierarchy (sample) to show 
// how to model exceptions.
// We have modelled the exceptions based on the
// .NET way of treating exceptions.
//
// (C) Datasim Education BV 2005
//

#include <iostream>
#include <vector>
#include <string>

class MathErr
{ // Base class for my current exceptions
private:
		std::string mess;	// The error message
		std::string meth;	// The method that threw the exception
public:
		MathErr()
		{
			mess = meth = std::string();
		}

		MathErr (const std::string& message, const std::string& method)
		{
			mess = message;
			meth = method;
		}

		std::string Message() const { return mess; }
		std::string Method() const { return meth; }

		virtual std::vector<std::string> MessageDump() const = 0;
	
		virtual void print() const
		{ 
			// This uses a Template method pattern

			// Variant part
			std::vector<std::string> r = MessageDump();

			// Invariant part
			for (int j = 0; j < r.size(); j++)
			{
				std::cout << r[j] << std::endl;
			}
		}

};


class ZeroDivide : public MathErr
{
private:

		std::string mess;	// Extra information

public:
		ZeroDivide() : MathErr()
		{
			mess = std::string();
		}

		ZeroDivide(const std::string& message,const std::string& method, const std::string& annotation ) 
			: MathErr (message, method)
		{
			mess = annotation;
		}

		std::vector<std::string> MessageDump() const
		{ // Full message

			std::vector<std::string> result(3);
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

		OutOfBounds(const std::string& message, const std::string& method, int index) 
			: MathErr (message, method)
		{
			ind = index;
		}

		int offendingIndex() const { return ind;}

		std::vector<std::string> MessageDump() const
		{ // Full message

			std::vector<std::string> result(3);
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

		GeneralMathErr(const std::string& message, const std::string& method) 
			: MathErr (message, method)
		{}

};