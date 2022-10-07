//
//  main.cpp
//  Ch52_list5210
//
//  Created by 山田啓太 on 2022/10/06.
//

/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner 
*/

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
    
    value_type const& numerator() const { return numerator_; }
    value_type const& denominator() const { return denominator_; }
    
private:
    value_type numerator_;
    value_type denominator_;
    void reduce();
};

template<class T>
rational<T>::rational(value_type num, value_type den)
: numerator_(num), denominator_(den)
{
    reduce();
}

template<class T>
void rational<T>::reduce()
{
    if(denominator() == value_type{})
        throw zero_denominator("devided by 0 denominator");
    if(denominator() < value_type{})
    {
        numerator_ = -numerator();
        denominator_ = -denominator();
    }
    value_type div{ std::gcd(numerator(), denominator()) };
    numerator_ = numerator() / div;
    denominator_ = denominator() / div;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, rational<T> const& rhs)
{
    std::cout << rhs.numerator() << '/' << rhs.denominator();
    return stream;
}

/** @file list5210.hh */
/** Listing 52-10. Defining a Variable Template */
template<class T>
inline const rational<T> pi{ 31416, 10000 };


int main()
{
  std::cout << pi<int> << '\n';
}
