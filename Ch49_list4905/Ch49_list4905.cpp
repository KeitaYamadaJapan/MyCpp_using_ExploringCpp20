//
//  main.cpp
//  Ch49_list4905
//
//  Created by 山田啓太 on 2022/09/24.
//

/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner 
*/

#include <iostream>
#include <string>
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
    
    int numerator() const noexcept { return numerator_; }
    int denominator() const noexcept { return denominator_; }
    
    rational const &operator*= (rational const& rhs);
    
    friend std::ostream& operator<< (std::ostream& os, rational const& r);
private:
    int numerator_;
    int denominator_;
    void reduce();
};

//class zero_denominator{
//public:
    //zero_denominator(std::string s){
        //std::cout << s << std::endl;
    //}
//};

inline void rational::reduce(){
    if(denominator_ == 0){
        throw zero_denominator("0 dominator");
    }
    if(denominator_ < 0){
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    int div{ std::gcd(numerator_, denominator_)};
    numerator_ /= div;
    denominator_ /= div;
}

inline std::ostream& operator<< (std::ostream& os, rational const& r){
    //if(r.denominator() == 0){
        //os << "";
    //}else{
        //os << double(r.numerator())/r.denominator();
    //}
    std::cout << r.numerator() <<"/" << r.denominator();
    return os;
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


/** @file list4905.hh */
/** Listing 49-5. Implementing the Multiplication Assignment Operator */
inline rational const& rational::operator*=(rational const& rhs)
{
  numerator_ *= rhs.numerator();
  denominator_ *= rhs.denominator();
  reduce();
  return *this;
}


int main() {
    rational r{10, 4};
    r *= r;
    std::cout << r << '\n';
}
