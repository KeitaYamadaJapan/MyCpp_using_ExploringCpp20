//
//  main.cpp
//  Ch49_list4909
//
//  Created by 山田啓太 on 2022/09/25.
//

/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner 
*/

#include <iostream>
//#include <string>
#include <numeric>
#include <stdexcept>

class rational{
public:
    class zero_denominator : public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
    };
    
    rational(int num, int den);
    //int init_denominator(int den);
    
    int numerator() const noexcept{ return numerator_; }
    int denominator() const noexcept{ return denominator_; }
    
    rational operator++(int);
    rational operator--(int);
    
    friend std::ostream& operator<< (std::ostream& os, rational const& r);
    
private:
    int init_denominator(int den);
    int numerator_;
    int denominator_;
    void reduce();
};

inline void rational::reduce(){
    
    if(denominator_ == 0){
        throw zero_denominator("0 denominator");
    }
    if(denominator_ < 0){
        denominator_ = -denominator_;
    }
    int div{ std::gcd(numerator_, denominator_)};
    numerator_ /= div;
    denominator_ /= div;
}

//class zero_denominator{
//public:
    //zero_denominator(std::string s){
        //std::cout << s;
    //}
//};

/** @file list4902.hh */
/** Listing 49-2. Using a Function and Conditional Statements Instead of Conditional Expressions */
/// Construct a rational object from a numerator and a denominator.
/// If the denominator is zero, throw zero_denominator. If the denominator
/// is negative, normalize the value by negating the numerator and denominator.
/// @post denominator_ > 0
/// @throws zero_denominator
rational::rational(int num, int den)
: numerator_{den < 0 ? -num : num}, denominator_{init_denominator(den)}
{
  reduce();
}

/// Return an initial value for the denominator_ member. This function is used
/// only in a constructor's initializer list.
int rational::init_denominator(int den)
{
  if (den == 0)
    throw zero_denominator("0 denominator");
  else if (den < 0)
    return -den;
  else
    return den;
}


/** @file list4909.hh */
/** Listing 49-9. Postfix Increment and Decrement Operators */
rational rational::operator++(int)
{
  rational result{*this};
  numerator_ += denominator_;
  return result;
}

rational rational::operator--(int)
{
  rational result{*this};
  numerator_ -= denominator_;
  return result;
}

inline std::ostream& operator<< (std::ostream& os, rational const& r){
    //os << r.numerator() << "/" << r.denominator();
    std::cout << r.numerator() << "/" << r.denominator();
    //if(r.denominator() == 0){
        //os << "";
    //}else{
        //os << double(r.numerator())/r.denominator();
    //}
    return os;
}


int main() {
  rational r{1,2};
    std::cout << r << '\n';
  std::cout << r++ << '\n';
    std::cout << r << '\n';
  std::cout << r-- << '\n';
  std::cout << r << '\n';
}
