// Angle.hpp
//
// Angle class
//
// (C) Datasim Education BV 1998

#ifndef Angle_hpp
#define Angle_hpp

#include "Common.hpp"

class Angle
{
private:
	double an;							// The angle in radians

public:
	// Constructors and destructor
	Angle()
	{ // Default constructor

		an=0.0;
	}

	Angle(const Angle& source)
	{ // Copy constructor
		
		an=source.an;
	}

	virtual ~Angle()
	{ // Destructor
	}

	// Selectors
	double degrees() const
	{ // Return the angle in degrees

		return an*180.0/PI;
	}

	double radians() const
	{ // Return angle in radians

		return an;
	}

	double sin() const
	{ // Return sine

		return ::sin(an);
	}

	double cos() const
	{ // Return cosine

		return ::cos(an);
	}

	double tan() const
	{ // Return tangent

		return ::tan(an);
	}

	// Modifiers
	void degrees(double deg)
	{ // Set the angle in degrees
    
		an=deg*PI/180.0;
	}

	void radians(double rad)
	{ // Set the angle in radians

		an=rad;
	}

	// Operators
	Angle& operator = (const Angle& source)
	{ // Assignment operator

		// Exit if same object
		if (this==&source) return *this;

		// Copy state
		an=source.an;

		return *this;
	}
};

class Radian: public Angle
{
public:
	// Constructors and destructors
	Radian(): Angle()
	{ // Default constructor
	}

	Radian(double rad): Angle()
	{ // Constructor with radians

		radians(rad);
	}

	Radian(const Radian& source): Angle(source)
	{ // Copy constructor
	}

	virtual ~Radian()
	{ // Destructor
	}

	Radian& operator = (const Radian& source)
	{ // Assignment operator

		Angle::operator = (source);
		return *this;
	}
};

class Degree: public Angle
{
public:
	// Constructors and destructors
	Degree(): Angle()
	{ // Default constructor
	}

	Degree(double deg): Angle()
	{ // Constructor with Degrees

		degrees(deg);
	}

	Degree(const Degree& source): Angle(source)
	{ // Copy constructor
	}

	virtual ~Degree()
	{ // Destructor
	}

	Degree& operator = (const Degree& source)
	{ // Assignment operator

		Angle::operator = (source);
		return *this;
	}
};

#endif // Angle_hpp