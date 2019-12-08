#include <iostream>

class MoreSecureRectangle
{
public:
    MoreSecureRectangle(double length, double width);
    void Print() const;

private:
    double length_;
    double width_;
    double area_;
};

MoreSecureRectangle::MoreSecureRectangle(double length, double width) : length_(length), width_(width), area_(length * width)
{ }

void MoreSecureRectangle::Print() const
{
    std::cout << "My rectangle is " << length_ << "x" << width_ << " so its area is " << std::endl;

}

int main(int argc, char** argv)
{

    MoreSecureRectangle rect(5., 4.);
    rect.Print();
//    rect.length_ = 0.;

    return 0;

}
