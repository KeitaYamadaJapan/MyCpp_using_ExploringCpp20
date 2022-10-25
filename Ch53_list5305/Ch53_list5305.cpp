//
//  main.cpp
//  Ch53_list5305
//
//  Created by 山田啓太 on 2022/10/09.
//

/**
     For my text.
     Sample program from "Exploring C++20"
        Auther: Ray Lischner 
     Not modifyed.
*/


#include <iostream>
#include <string>
#include <limits>

#include <numeric>
#include <stdexcept>

class zero_denominator : public std::logic_error
{
public:
    using logic_error::logic_error;
};

class rational
{
public:
    using value_type = int;
    constexpr rational() : rational{0} {}
    //rational() : rational{0} {}
    constexpr rational(value_type num) : numerator_{num}, denominator_{1} {}
    //rational(value_type num) : numerator_{num}, denominator_{1} {}
    rational(value_type num, value_type den);
    
    constexpr value_type const& numerator() const { return numerator_; }
    //value_type const& numerator() const { return numerator_; }
    constexpr value_type const& denominator() { return denominator_; }
    //value_type const& denominator() const { return denominator_; }
    
private:
    void reduce();
    value_type numerator_;
    value_type denominator_;
};

void rational::reduce()
{
    if(denominator() == value_type{})
        throw zero_denominator("devided by zero denominator");
    if(denominator() < value_type{})
    {
        numerator_ = - numerator();
        denominator_ = -denominator();
    }
    value_type div{ std::gcd(numerator(), denominator())};
    numerator_ = numerator() / div;
    denominator_ = denominator() / div;
}

rational::rational(value_type num, value_type den)
: numerator_{num}, denominator_{den}
{
    reduce();
}


/** @file list5305.hh */
/** Listing 53-5. Specializing numeric_limits for the rational Class */
namespace std{
template<>
class numeric_limits<rational>
{
    public:
        static constexpr int digits { 2 * numeric_limits<int>::digits };
    };
}


int main()
{
    std::cout << std::numeric_limits<rational>::digits << '\n';
    
}
