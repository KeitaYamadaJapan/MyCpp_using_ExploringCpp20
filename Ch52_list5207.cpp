//
//  main.cpp
//  Ch52_list5207
//
//  Created by 山田啓太 on 2022/10/04.
//

/** @file list5207.cxx */
/** Listing 52-7. Trying to Mix rational Base Types */

#include <iostream>
#include <stdexcept>
#include <numeric>

class zero_denominator : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

template<class T>
class rational
{
public:
    using value_type = T;
    rational() : rational{0} {}
    rational(value_type num) : numerator_{num}, denominator_{1} {}
    rational(value_type num, value_type den);
    
    void assign(value_type num, value_type den);
    
    value_type const& numerator() const { return numerator_; }
    value_type const& denominator() const { return denominator_; }
    
    rational const& operator= (rational const& rhs);
    
    template <class U>
    U convert()
    const
    {
        return static_cast<U>(numerator())/static_cast<U>(denominator());
    }
    
private:
    value_type numerator_;
    value_type denominator_;
    void reduce();
};

template <class T>
rational<T>::rational(value_type num, value_type den)
: numerator_{num}, denominator_{den}
{
    reduce();
}

template <class T>
void rational<T>::assign(value_type num, value_type den)
{
    numerator_ = num;
    denominator_ = den;
    reduce();
}

template<class T>
void rational<T>::reduce()
{
    if(denominator_ == value_type{})
    {
        throw zero_denominator("devided by zero denominator.");
    }
    if(denominator_ < value_type{})
    {
        denominator_ = -denominator();
        numerator_ = -numerator();
    }
    T div{ std::gcd(numerator(), denominator())};
    numerator_ = numerator() / div;
    denominator_ = denominator() / div;
}

template<class T>
rational<T> const& rational<T>::operator= (rational<T> const& rhs)
{
    if(denominator() == value_type{})
    {
        throw zero_denominator("deveded by zero denominator.");
    }
    if(denominator() < value_type{})
    {
        denominator_ = -denominator();
        numerator_ = -numerator();
    }
    denominator_ = rhs.denominator();
    numerator_ = rhs.numerator();
    return *this;
}


int main()
{
  rational<int> little{};
  rational<long> big{};
  big = little.convert<long>();
}
