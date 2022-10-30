//
//  main.cpp
//  Ch02_list0201
//
//  Created by 山田啓太 on 2022/08/23.
//

/**
     For my text.
     Sample program from "Exploring C++20"
        Auther: Ray Lischner 
     Not modifyed.
*/


/** @file list0201.cpp */
/** Listing 2-1. Reading Test */
/// Read the program and determine what the program does.

#import <iostream>
#import <limits>

int main()
{
    int min{std::numeric_limits<int>::max()};
    int max{std::numeric_limits<int>::min()};
    bool any{false};
    int x;
    std::cout << "Input:" <<std::endl;
    while (std::cin >> x)
    {
        any = true;
        if (x < min)
            min = x;
        if (x > max)
            max = x;
    }

    if (any)
        std::cout << "min = " << min << "\nmax = " << max << '\n';
}
