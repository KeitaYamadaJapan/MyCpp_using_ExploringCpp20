//
//  main.cpp
//  Ch02_list0203
//
//  Created by 山田啓太 on 2022/08/23.
//

/**
     For my text.
     Sample program from "Exploring C++20"
        Auther: Ray Lischner 
     Not modifyed.
*/


/** @file list0203.cpp */
/** Listing 2-3. Determining the Number of Bits in a bool */
#import <iostream>
#import <limits>

int main()
{
  // Note that "digits" means binary digits, i.e., bits.
  std::cout << "bits per bool: " << std::numeric_limits<bool>::digits << '\n';
}
