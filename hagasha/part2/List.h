//
// Created by amirb on 27/06/2023.
//

#ifndef OOP5_LIST_H
#define OOP5_LIST_H

template<typename... TT>
struct List {
    enum{ size = sizeof...(TT)};
};

template<typename T, typename... TT >
struct List<T, TT... > {
    enum{ size = sizeof...(TT)+1};
    typedef T head;
    typedef List<TT...> next;
};

template<typename HEAD, typename... TAIL>
struct MakeList{
    typedef List<HEAD,TAIL...> result;
};


//basic occasion
template<typename T, typename List>
struct PrependList {
    typedef typename MakeList<T>::result list;
};

template<typename T,typename S, typename... TT>
struct PrependList<T,List<S, TT...>> {
    typedef typename MakeList<T,S,TT...>::result list;
};

template<int N, typename T>
struct GetAtIndex{};

template<int N, typename T, typename... TT>
struct GetAtIndex<N, List<T, TT...>>{
    typedef typename GetAtIndex<N - 1,  List<TT...>>::value value;
};

template<typename T, typename... TT>
struct GetAtIndex<0, List<T, TT...>>{
    typedef T value;
};

template<int N, typename S, typename T>
struct SetAtIndex{};

template<int N, typename S, typename T, typename... TT>
struct SetAtIndex<N, S, List<T, TT...>>{
    typedef typename SetAtIndex<N - 1, S, List<TT...>>::list tmp;
    typedef typename PrependList<T,tmp>::list list;
};

template<typename S, typename T, typename... TT>
struct SetAtIndex<0, S, List<T, TT...>>{
    typedef typename PrependList<S, List<TT...>>::list list;
};

#endif //OOP5_LIST_H
