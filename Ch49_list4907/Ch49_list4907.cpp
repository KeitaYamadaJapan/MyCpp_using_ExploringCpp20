//
//  main.cpp
//  Ch49_list4907
//
//  Created by 山田啓太 on 2022/09/25.
//
#include <iostream>
#include <numeric>
#include <string>
#include <stdexcept>

class rational{
public:
    class zero_denominator : public std::logic_error
    {
        using std::logic_error::logic_error;
    };
    rational(int num, int den);
    
    int numerator() const noexcept{ return numerator_; }
    int denominator() const noexcept{ return denominator_; }
    
    rational const& operator+= (rational const& rhs);
    rational const& operator-= (rational const& rhs);
    rational const& operator/= (rational const& rhs);
    friend std::ostream &operator << (std::ostream& os, rational const& r);
    
private:
    int numerator_;
    int denominator_;
    void reduce();
};

//class zero_denominator{
//public:
    //zero_denominator(std::string s){
        //std::cout << s;
    //}
//};

inline void rational::reduce(){
    if(denominator_ == 0){
        throw zero_denominator("0 denominator");
    }
    if(denominator_  < 0){
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    int div{ std::gcd(numerator_, denominator_) };
    numerator_ /= div;
    denominator_ /= div;
}

/** @file list4901.hh */
/** Listing 49-1. Using Conditional Expressions in a Constructor’s Initializer */
/// Construct a rational object from a numerator and a denominator.
/// If the denominator is zero, throw zero_denominator. If the denominator
/// is negative, normalize the value by negating the numerator and denominator.
/// @post denominator_ > 0
/// @throws zero_denominator
rational::rational(int num, int den)
: numerator_{den < 0 ? -num : num},
  denominator_{den == 0 ? throw zero_denominator("0 denominator") :
                          (den < 0 ? -den : den)}
{
  reduce();
}

/** @file list4907.hh */
/** Listing 49-7. Other Arithmetic Assignment Operators */
rational const& rational::operator+= (rational const& rhs)
{
  numerator_ = numerator() * rhs.denominator() + rhs.numerator() * denominator();
  denominator_ *= rhs.denominator();
  reduce();
  return *this;
}

rational const& rational::operator-= (rational const& rhs)
{
  numerator_ = numerator() * rhs.denominator() - rhs.numerator() * denominator();
  denominator_ *= rhs.denominator();
  reduce();
  return *this;
}

rational const& rational::operator/= (rational const& rhs)
{
  if (rhs.numerator() == 0)
    throw zero_denominator{"divide by zero"};
  numerator_ *= rhs.denominator();
  denominator_ *= rhs.numerator();
  if (denominator_ < 0)
  {
    denominator_ = -denominator_;
    numerator_ = -numerator_;
  }
  reduce();
  return *this;
}

std::ostream& operator<<(std::ostream& os, rational const& r){
    //if(r.denominator() == 0){
        //os << "";
    //}else{
        //os << double(r.numerator())/r.denominator();
    //}
    std::cout << r.numerator() << "/" << r.denominator();
    return os;
}

int main() {
  rational r1{1,2};
    rational r2{1,3},r3{2,3},r4{1,4};
    r1 += r2;
    r1 /= r3;
    r1 -= r4;
    
    
  r1 += rational{1,3};
  r1 /= rational{2,3};
  r1 -= rational{1,4};
  std::cout << r1 << '\n';
}
