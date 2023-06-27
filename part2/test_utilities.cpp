//
// Created by amirb on 28/06/2023.
//

#include "Utilities.h"
#include "Int.h"
#include <iostream>
using namespace std;

int main(){
    int val = ConditionalInteger<(0 != 1), 0, 1>::value;
    cout << (val == 0) << endl;
    val = ConditionalInteger<(0 == 1), 0, 1>::value; // = 1
    cout << (val == 1) << endl;
    typedef typename Conditional<(0 != 1), Int<0>, Int<1>>::value test1; // = Int<0>
    cout << std::is_same<test1,Int<0>>::value << endl;
    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>::value test2; // = Int<1>
    cout << std::is_same<test2,Int<1>>::value << endl;
}