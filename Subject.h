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
    vector<Observer<T>*> observers;

    typename vector<Observer<T>*>::iterator findObserver(Observer<T>& obs){
        for(auto observer : observers){
            if (observer == obs)
                return observer;
        }

        return observers.end();
    };

public:
    Subject()= default;

    void notify(const T& param){
        for(Observer<T>* obs : observers)
        {
            obs->handleEvent(param);
        }
    }

    void addObserver(Observer<T>& obs){
        if(findObserver() == observers.end()){
            throw ObserverAlreadyKnownToSubject();
        }
        observers.push_back(&obs);
    }

    void removeObserver(Observer<T>& obs){
        auto it = findObserver();
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
