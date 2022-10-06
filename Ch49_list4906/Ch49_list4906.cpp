//
//  main.cpp
//  Ch49_list4906
//
//  Created by 山田啓太 on 2022/09/24.
//

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
    //rational(rational &rhs);
    
    int numerator() const noexcept { return numerator_; }
    int denominator() const noexcept { return denominator_; }
    
    rational const& operator*= (rational const& rhs);
    friend std::ostream& operator<< ( std::ostream& os, rational const& r);
    
    
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
    };
    if(denominator_ < 0){
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

//rational::rational(rational &rhs):numerator_{rhs.numerator() },denominator_{rhs.denominator()}
//{}

/** @file list4905.hh */
/** Listing 49-5. Implementing the Multiplication Assignment Operator */
rational const& rational::operator*=(rational const& rhs)
{
  numerator_ *= rhs.numerator();
  denominator_ *= rhs.denominator();
  reduce();
  return *this;
}

/** @file list4906.hh */
/** Listing 49-6. Reimplementing Multiplication in Terms of an Assignment Operator */
rational operator*(rational const& lhs, rational const& rhs)
{
  rational result{lhs};
  result *= rhs;
  return result;
}

inline std::ostream& operator<<(std::ostream& os, rational const& r){
    //if(r.denominator() == 0){
        //os << "";
    //}else{
        //os << double(r.numerator())/r.denominator();
    //}
    os << r.numerator() << "/" << r.denominator();
    return os;
}


int main() {
    rational r1{rational{3,2}};
    rational r2{rational{2,3}};
    rational r3{r1*r2};
    std::cout << r3 << '\n';
    
    std::cout << rational{3,2} * rational{2,3} << '\n';
}
