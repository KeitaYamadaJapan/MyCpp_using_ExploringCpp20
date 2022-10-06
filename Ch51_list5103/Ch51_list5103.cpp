//
//  main.cpp
//  Ch51_5103
//
//  Created by 山田啓太 on 2022/09/29.
//

/** @file list5103.cpp */
/** Listing 51-3. Testing the absval Function Template */
#import <iostream>
#import <stdexcept>
#include <numeric>
#include <string>

class rational
{
public:
    class zero_denominator : public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
    };
    
    rational() noexcept : rational{0} {}
    rational(int num) noexcept : numerator_{0}, denominator_{1} {}
    rational(int num, int den);
    
    
    int numerator() const noexcept{ return numerator_; }
    int denominator() const noexcept{ return denominator_; }
    
private:
    int init_denominator(int den);
    int numerator_;
    int denominator_;
    void reduce();
    //void normalize();
};  // Listing 49-10

//rational abs(rational const& r);

inline void rational::reduce()
{
    if(denominator_ == 0){
        throw zero_denominator("0 denominator");
    }
    if(denominator_ < 0){
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    int div{std::gcd(numerator_, denominator_) };
    numerator_ /= div;
    denominator_ /= div;
}

rational::rational(int num, int den) : numerator_{ den < 0 ? -den : den }, denominator_{init_denominator(den)}
{
    reduce();
}



int rational::init_denominator(int den)
{
    if(den == 0){
        throw zero_denominator("0 denomirator");
    }else if(den <0){
        return -den;
    }else{
        return den;
    }
}

rational operator-(rational const& r)
{
    return rational{-r.numerator(), r.denominator()};
}

inline bool operator <(rational const& lhs, rational const& rhs)
{
    if(lhs.denominator() == rhs.denominator()){
        return lhs.numerator() < rhs.numerator();
    }
    return lhs.numerator()*rhs.denominator() < rhs.numerator()*lhs.denominator();
}

inline std::ostream& operator<< (std::ostream& stream,rational const& rhs)
{
    std::cout << rhs.numerator() << "/" << rhs.denominator();
    return stream;
}

template<class T>
T absval(T x)
{
  if (x < 0)
    return -x;
  else
    return x;
}

int main()
{
  std::cout << absval(-42) << '\n';
  std::cout << absval(-4.2) << '\n';
  std::cout << absval(42) << '\n';
  std::cout << absval(4.2) << '\n';
  std::cout << absval(-42L) << '\n';
  std::cout << absval(rational{42, 5}) << '\n';
  std::cout << absval(rational{-42, 5}) << '\n';
  std::cout << absval(rational{42, -5}) << '\n';
}
