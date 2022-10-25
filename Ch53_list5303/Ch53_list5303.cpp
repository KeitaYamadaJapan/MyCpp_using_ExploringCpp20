//
//  main.cpp
//  Ch53_list5303
//
//  Created by 山田啓太 on 2022/10/08.
//

/**
     Modifyed sample program from "Exploring C++20"
        Auther: Ray Lischner 
*/

/** @file list5303.cpp */
/** Listing 53-3. Specializing std::less to Compare person Objects by Name */

#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <map>

class person
{
public:
    person() : name_{},address_{}, phone_{} {}
    person(std::string_view name,
           std::string_view address,
           std::string_view phone)
    : name_{name}, address_{address}, phone_{phone}
    {}
    
    std::string const& name() const { return name_; }
    std::string const& address() const {return address_; }
    std::string const& phone() const { return phone_; }
    
private:
    std::string name_, address_, phone_;
};

namespace std{
template<>
    struct less<person>{
        bool operator() (person const& a, person const& b) const {
            return a.name() < b.name();
        }
    };

template<>
    struct greater<person>{
        bool operator() (person const& a, person const& b) const {
            return a.name() > b.name();
        }
    };

}

int main()
{
    std::map<person, int>people;
    people[person{"Ray","123 Erren", "555-2350"}]=23;
    people[person{"Tonny","3 45 1 Otta","787-2234"}]=45;
    std::cout << people.begin()->first.name() << '\n';
    
    std::map<person, int, std::greater<person>>people2;
    people2[person{"Ray","123 Erren", "555-2350"}]=23;
    people2[person{"Tonny","3 45 1 Otta","787-2234"}]=45;
    std::cout << people2.begin()->first.name() << '\n';
}
