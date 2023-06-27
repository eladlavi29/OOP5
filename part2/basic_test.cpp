//
// Created by amirb on 27/06/2023.
//

#include <iostream>
using namespace std;
#include "List.h"
#include "Int.h"

int main() {
    typedef List <Int<1>, Int<2>, Int<3>> list;
    typedef typename list::head intOne;
    cout << std::is_same<intOne,Int<1>>::value << endl;
    typedef typename list::next listTail; // = List<Int<2>, Int<3>>
    typedef typename listTail::head intTwo;
    cout << std::is_same<intTwo,Int<2>>::value << endl;
    static_assert(list::size == 3, "ERROR!");

    typedef typename PrependList<Int<4>, list>::list newList;
    typedef typename newList::head intFour;
    cout << std::is_same<intFour,Int<4>>::value << endl;

    typedef typename GetAtIndex<0, list>::value intOne;
    typedef typename GetAtIndex<2, list>::value intThree;
    cout << std::is_same<intOne,Int<1>>::value << endl;
    cout << std::is_same<intThree,Int<3>>::value << endl;

    typedef List<Int<1>, Int<2>, Int<3>> list;
    typedef typename SetAtIndex<0, Int<5>, list>::list listA;
    typedef typename SetAtIndex<2, Int<7>, list>::list listB;

    typedef typename GetAtIndex<0, listA>::value int5;
    typedef typename GetAtIndex<2, listB>::value int7;
    cout << std::is_same<int5,Int<5>>::value << endl;
    cout << std::is_same<int7,Int<7>>::value << endl;

}