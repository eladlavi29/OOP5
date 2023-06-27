//
// Created by amirb on 27/06/2023.
//

#ifndef OOP5_LIST_H
#define OOP5_LIST_H

template<typename T>
class List {};


template<typename T, typename... TT >
class List< T, TT... > {
    typedef typename GetNth<N-1, Tuple<TT... >>::Head Head;
};


#endif //OOP5_LIST_H
