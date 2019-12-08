#include <iostream>

struct Rectangle
{
    Rectangle(double length, double width);

    double length_;
    double width_;
    double area_;

    void Print() const;
};

Rectangle::Rectangle(double length, double width) : length_(length), width_(width), area_(length*width) {}

void Rectangle::Print() const
{
    std::cout << "My rectangle is " << length_ << "x" << width_ << " so its area is " << area_ << std::endl;
}

int main(int argc, char** argv)
{

    Rectangle rect(5., 4.);
    rect.Print(); // Ok
    rect.length_ = 23.;
    rect.Print();

    return 0;
}
