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

    int find_index(Observer<T>* obs_ptr){
        for(int i = 0; i<this->observers.size(); i++)
        {
            if(this->observers[i]==obs_ptr){
                return i;
            }
        }
        return -1;
    }

public:
    Subject()= default;

    void notify(const T& param){
        for(Observer<T>* obs : observers)
        {
            obs->handleEvent(param);
        }
    }

    void addObserver(Observer<T>& obs){
        if(find_index(&obs) != -1){
            throw ObserverAlreadyKnownToSubject();
        }
        observers.push_back(&obs);
    }

    void removeObserver(Observer<T>& obs){
        int ind = find_index(&obs);
        if(ind == -1) {//not found
            throw ObserverUnknownToSubject();
        }
        observers.erase(observers.begin() + ind);
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
