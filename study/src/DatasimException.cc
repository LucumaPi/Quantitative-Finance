// DatasimException.cpp
//
//
// Last Modification Dates:
//
// 2005-12-16 DD Kick-off
//
// (C) Datasim Education BV 2005-2006
//

#include <duffy/DatasimException.hh>

DatasimException::DatasimException()
{
		mess = meth = why = std::string();
		result = std::vector<std::string>(3);
		result[0] = mess;
		result[1] = meth;
		result[2] = why;

}

DatasimException::DatasimException (const std::string& message, const std::string& method,
									const std::string& extraInfo)
{
		mess = message;
		meth = method;
		why = extraInfo;
		result = std::vector<std::string>(3);
		
		result[0] = mess;
		result[1] = meth;
		result[2] = why;

}

std::string DatasimException::Message() const
{ 
	return mess; 
}

std::string DatasimException::rationale() const
{ 
	return why; 
}

std::string DatasimException::Method() const
{ 
	return meth; 
}

std::vector<std::string> DatasimException::MessageDump() const
{ // Full message
	
	return result;
}
	
void DatasimException::print() const
{ 

	// Variant part
	std::vector<std::string> r = MessageDump();

	std::cout << std::endl << r[0] << std::endl;
	// Invariant part
	for (int j = 1; j < r.size(); j++)
	{
		std::cout << '\t' << r[j] << std::endl;
	}
}