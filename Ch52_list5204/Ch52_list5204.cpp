//
//  main.cpp
//  Ch52_list5204
//
//  Created by 山田啓太 on 2022/10/01.
//

/** @file list5204.cpp */
/** Listing 52-4. Simple I/O Test of the rational Class Template */
#import <iostream>
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
    rational(value_type num) : numerator_{num}, denominator_{1}{}
    rational(value_type num, value_type den);
    
    value_type const& numerator() const{ return numerator_; }
    value_type const& denominator() const{ return denominator_; }
    
    void assign(value_type num, value_type den);
    
private:
    value_type numerator_;
    value_type denominator_;
    void reduce();
  
};

template<class T>
void rational<T>::reduce()
{
    if(denominator() == value_type{}) throw zero_denominator("divided by 0 denominator.");
    if(denominator() < value_type{})
    {
        numerator_ = -numerator();
        denominator_ = -denominator();
    }
    T div{ std::gcd(numerator(), denominator()) };
    numerator_ = numerator() / div;
    denominator_ = denominator() / div;
}

template <class T>
void rational<T>::assign(value_type num, value_type den)
{
    numerator_ = num;
    denominator_ = den;
    reduce();
}

template<class T>
std::ostream &operator<< (std::ostream& stream, rational<T> const& r)
{
    std::cout << r.numerator() << '/' << r.denominator();
    return stream;
}

template<class T>
std::istream &operator>> (std::istream& in, rational<T>& rat)
{
    T n{},d{};
    char sep{};
    if(not(in >> n >> sep))
    {
        in.setstate(in.failbit);
    }
    else if(sep != '/')
    {
        in.unget();
        rat.assign(n, 1);
    }
    else if(in >> d)
    {
        rat.assign(n, d);
    }
    else
    {
        in.setstate(in.failbit);
    }
    return in;
}

int main()
{
    std::cout<<'\n';
    rational<int> r{};
  while (std::cin >> r)
    std::cout << r << '\n';
}
