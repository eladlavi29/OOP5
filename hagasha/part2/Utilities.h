//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_UTILITIES_H
#define OOP5_UTILITIES_H

template<bool g, typename T,typename E>
struct Conditional{
    typedef T value;
};

template<typename T,typename E>
struct Conditional<false, T, E>{
    typedef E value;
};

template<bool g, int T,int E>
struct ConditionalInteger{
    enum{value = T};
};

template<int T,int E>
struct ConditionalInteger<false, T, E>{
    enum{value = E};
};


#endif //OOP5_UTILITIES_H
