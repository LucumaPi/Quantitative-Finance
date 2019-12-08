#include <iostream>

class Rectangle4
{
public:
    Rectangle4(double length, double width);

    // Mutators
    void SetLength(double x);
    void SetWidth(double x);

    // Accesors
    double GetLength() const;
    double GetWidth() const;
private:
    double length_ = -1.e20;
    double width_ = -1.e20;
};

Rectangle4::Rectangle4(double length, double width) : length_(length), width_(width)
{ }

void Rectangle4::SetLength(double x)
{
    length_ = x;
}

void Rectangle4::SetWidth(double x)
{
    width_ = x;
}

double Rectangle4::GetLength() const
{
    return length_;
}


double Rectangle4::GetWidth() const
{
    return width_;
}

double ComputeArea(const Rectangle4& r) // free function
{
    return r.GetLength() * r.GetWidth(); // ok: public methods! And no risk to inadvertible change the value here
}

int main(int argc, char** argv)
{
    Rectangle4 rect(4., 6.5);
    std::cout << "Area = " << ComputeArea(rect) << std::endl;

    rect.SetWidth(5.);
    std::cout << "Area = " << ComputeArea(rect) << std::endl;

    return 0;
}
