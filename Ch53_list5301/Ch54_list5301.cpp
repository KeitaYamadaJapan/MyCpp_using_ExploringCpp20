//
//  main.cpp
//  Ch53_list5301
//
//  Created by 山田啓太 on 2022/10/07.
//

/**
     For my text.
     Sample program from "Exploring C++20"
        Auther: Ray Lischner 
     Not modifyed.
*/

#include <iostream>

/** @file list5301.hh */
/** Listing 53-1. The is_void Class Template */
template<class T>
class is_void : public std::false_type
{};

template<>
class is_void<void> : public std::true_type
{};

int main()
{
  std::cout << std::boolalpha <<
    is_void<int>::value << '\n' <<
    is_void<void>::value << '\n';
}
