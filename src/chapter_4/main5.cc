#include <iostream>

class Rectangle3
{
public:
   Rectangle3(double length, double width);
   void Print() const;

   void SetLength(double x);
   void SetWidth(double x);

private:
    double length_;
    double width_;
    double area_;
};

Rectangle3::Rectangle3(double length, double width) : length_(length), width_(width), area_(length * width)
{ }

void Rectangle3::Print() const
{
    std::cout << "My rectangle is " << length_ << " x " << width_ << " so its area is " << area_ << std::endl;
}

void Rectangle3::SetLength(double x)
{
    length_ = x;
    area_ = length_ * width_;
}

void Rectangle3::SetWidth(double x)
{
    width_ = x;
    area_ = length_ * width_;

}

int main(int argc, char** argv)
{

    Rectangle3 rect(5., 4.);
    rect.Print();
    rect.SetLength(23.);
    rect.Print();


    return 0;
}
