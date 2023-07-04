//
// Created by Elad on 27/06/2023.
//

#ifndef OOP5_OBSERVER_H
#define OOP5_OBSERVER_H

template <class T>
class Observer {
public:
    Observer() = default;
    virtual void handleEvent(const T&) = 0;
};

#endif //OOP5_OBSERVER_H
