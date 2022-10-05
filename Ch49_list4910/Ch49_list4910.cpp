//
//  main.cpp
//  Ch49_list4910
//
//  Created by 山田啓太 on 2022/09/26.
//

#include <iostream>
#include <string>
#include <numeric>
#include <stdexcept>

class rational{
public:
    class zero_denominator : public std::logic_error
    {
        using std::logic_error::logic_error;
    };
    rational(int num, int den);
    //int init_denominator(int den);
    
    int numerator() const noexcept { return numerator_;}
    int denominator() const noexcept { return denominator_; }
    
private:
    int init_denominator(int den);
    int numerator_;
    int denominator_;
    void reduce();
};

//class zero_denominator{
//public:
    //zero_denominator (std::string s){
        //std::cout << s;
    //}
//};

//void rational::reduce(){
inline void rational::reduce(){
    //if(numerator_ != 0 && denominator_ != 0){
    if(denominator_ == 0){
        throw zero_denominator{"denominator is zero"};
    }
    if(denominator_ < 0){
        denominator_ = -denominator_;
        numerator_ = -numerator_;
    }
    int div{ std::gcd(numerator_, denominator_) };
    numerator_ /= div;
    denominator_ /= div;
}

// includes list4910.cc

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

inline bool operator ==(rational const& rhs, rational const&lhs){

    return rhs.numerator() == lhs.numerator() && rhs.denominator() == lhs.denominator();
}

int main() {
    std::cout << std::boolalpha << (rational{1,2} == rational{4,8}) << '\n';
}
