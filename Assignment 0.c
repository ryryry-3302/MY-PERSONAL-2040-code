

#include <iostream>
#include <cmath>


#define BOUND(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

RGB::RGB(int red, int green, int blue) :
    red_(BOUND(red, 0, 255)),
    green_(BOUND(green, 0, 255)),
    blue_(BOUND(blue, 0, 255)) { }

RGB::~RGB() { }

void RGB::print() {
  std::cout << "RGB(" << red_ << ", " << green_ << ", " << blue_ << ")"
    << std::endl;
}

RGB RGB::mix(const RGB& other) {
  
  int rednew = red_ + other.red() ;

  int bluenew = blue_ + other.blue() ;

  
  int greennew = green_ + other.green() ;
  


  return RGB(BOUND(rednew, 0, 255), BOUND(greennew, 0, 255), BOUND(bluenew, 0, 255 ));
}

RGB RGB::scale(double factor) {

  return RGB(std::round(red_ * factor), std::round(green_ * factor), std::round(blue_ * factor));
}
