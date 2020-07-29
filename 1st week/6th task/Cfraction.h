//
// Created by Alex on 28.07.2020.
//

#ifndef INC_6TH_TASK_CFRACTION_H
#define INC_6TH_TASK_CFRACTION_H
#include <iostream>

class Cfraction {
public:
    long top;
    long bottom;


    Cfraction(long top = 0, long bottom = 1);
    Cfraction(const Cfraction& other);

    Cfraction operator +(const Cfraction& other) const;
    Cfraction operator -(const Cfraction& other) const;
    Cfraction operator *(const Cfraction& other) const;
    Cfraction operator /(const Cfraction& other) const;

    void operator +=(const Cfraction& other);
    void operator -=(const Cfraction& other);
    void operator *=(const Cfraction& other);
    void operator /=(const Cfraction& other);

    void operator ++();
    void operator --();

    explicit operator double() const;
    void operator ()(long new_top, long new_bottom = 1);

    bool operator ==(const Cfraction& other) const;
    bool operator !=(const Cfraction& other) const;
    bool operator <=(const Cfraction& other) const;
    bool operator >=(const Cfraction& other) const;
    bool operator >(const Cfraction& other) const;
    bool operator <(const Cfraction& other) const;

    Cfraction& operator =(const Cfraction& other);

    friend std::ostream& operator<<(std::ostream& out, const Cfraction& cfraction){
        return out << cfraction.top << '/' << cfraction.bottom;
    }
private:
};

#endif //INC_6TH_TASK_CFRACTION_H
