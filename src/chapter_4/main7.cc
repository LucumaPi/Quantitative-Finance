#include <iostream>

class Rectangle5
{
public:
    Rectangle5(double length, double width);

    // Mutators
    void SetLength(double x);
    void SetWidth(double x);

    // Accessors
    double GetArea() const; // other accessors are not defined to limit steps to define the class
private:
    // Mutator for the area
    // Prototype is not bright (parameters are clearly  intended to be the data attributes)
    // but is useful to make my point below
    void SetArea(double length, double width);
private:
    double area_ = -1.e20;
    double length_ = -1.e20;
    double width_ = -1.e20;
};

Rectangle5::Rectangle5(double length, double width) : length_(length), width_(width)
{
    SetArea(width_, length_);
}

double Rectangle5::GetArea() const
{
    return area_;
}

void Rectangle5::SetLength(double x)
{
    length_ = x;
    SetArea(width_, length_);
}

void Rectangle5::SetWidth(double x)
{
    width_ = x;
    SetArea(width_, length_);
}

void Print5(const Rectangle5& r)
{
    std::cout << "Area is" << r.GetArea() << std::endl;
}

int main(int argc, char** argv)
{
    Rectangle5 rect(3., 4.);
    Print5(rect);

    rect.SetLength(8.);
    Print5(rect);

    rect.SetWidth(2.);
    Print5(rect);

    return 0;
}
