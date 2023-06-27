//
// Created by Elad on 27/06/2023.
//

#ifndef OOP5_SUBJECT_H
#define OOP5_SUBJECT_H

#include <iostream>
#include <vector>

#include "OOP5EventException.h"
#include "Observer.h"
using namespace std;


template <class T>
class Subject{
    vector<Observer<T>> observers;

public:
    Subject(){}

    void notify(const T&){
        for(auto obs : observers)
        {
            obs.handleEvent();
        }
    }

    void addObserver(Observer<T>& obs){
        if(find(observers.begin(), observers.end(), obs) == observers.end()){
            throw ObserverAlreadyKnownToSubject();
        }
        observers.pushback(obs);
    }

    void removeObserver(Observer<T>& obs){
        auto it = find(observers.begin(), observers.end(), obs);
        if(it == observers.end()) {//not found
            throw ObserverUnknownToSubject();
        }
        observers.erase(it);
    }

    Subject<T>& operator+=(Observer<T>& obs){
        addObserver(obs);
        return *this;
    }

    Subject<T>& operator-=(Observer<T>& obs){
        removeObserver(obs);
        return *this;
    }

    Subject<T>& operator()(const T& val){
        notify(val);
        return *this;
    }
};
#endif //OOP5_SUBJECT_H
