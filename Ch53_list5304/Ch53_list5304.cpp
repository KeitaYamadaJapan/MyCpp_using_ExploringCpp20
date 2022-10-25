//
//  main.cpp
//  Ch53_list5304
//
//  Created by 山田啓太 on 2022/10/09.
//

#include <iostream>
/** @file list5304.hh */
/** Listing 53-4. The Primary std::less Class Template */

template <class T>
struct less
{
    bool operator()(T const& a, T const& b) const { return a < b;}
};



int main()
{
    less<int> const x;
    if(x(1,2)) std::cout << "success\n";
    else std::cout << "false\n";
        
}
