//
//  main.cpp
//  Ch32_list3206
//
//  Created by 山田啓太 on 2022/10/03.
//
/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner
*/
/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner 
*/

#include <iostream>
#include <numeric>
#include <stdexcept>

class zero_denominator : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

template <class T>
class rational
{
public:
    using value_type = T;
    rational() : rational{0} {}
    rational(value_type num) : numerator_{num},denominator_{1} {}
    rational(value_type num, value_type den);
    
    void assign(value_type num, value_type den);
    
    value_type const& numerator() const{ return numerator_;}
    value_type const& denominator() const{ return denominator_;}
    
    rational const& operator /= (rational const& rhs);
    
private:
    void reduce();
    value_type numerator_;
    value_type denominator_;
};

template<class T>
rational<T>::rational(value_type num, value_type den)
: numerator_{num}, denominator_{den}
{
    reduce();
}

template <class T>
void rational<T>::reduce()
{
    if(denominator() == value_type{})
    {
        throw zero_denominator("devided by zero denominator");
    }
    if(denominator() < value_type{})
    {
        numerator_ = -numerator();
        denominator_ = -denominator();
    }
    T div{ std::gcd(numerator(), denominator())};
    numerator_ = numerator() / div;
    denominator_ = denominator() / div;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, rational<T> const& r)
{
    std::cout << r.numerator() << '/' << r.denominator();
    return stream;
}

/** @file list5206.hh */
/** Listing 52-6. Invoking a Default Constructor of a Template Parameter */
template<class T>
rational<T> const& rational<T>::operator/=(rational const& rhs)
{
    if(rhs.numerator() == T{})
    {
        throw zero_denominator("divided by zero dominator.");
    }
    numerator_ *= rhs.denominator();
    denominator_ *= rhs.numerator();
    if(denominator_ < T{})
    {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    reduce();
    return *this;
}

int main()
{
   rational n{710};
   rational d{226};
   n /= d;
   std::cout << n << '\n';
}
