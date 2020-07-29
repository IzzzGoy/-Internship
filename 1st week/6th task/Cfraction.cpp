//
// Created by Alex on 28.07.2020.
//

#include "Cfraction.h"
#include <stdexcept>

Cfraction::Cfraction(long top, long bottom) : top(top){
    if (bottom == 0) {
        throw std::invalid_argument("Bottom must be not null");
    }
    this->bottom = bottom;
}

Cfraction::Cfraction(const Cfraction &other) : top(other.top), bottom(other.bottom) {}

Cfraction Cfraction::operator+(const Cfraction &other) const {
    return Cfraction(
            this->top * other.bottom + other.top * this->bottom,
            this->bottom * other.bottom);
}

Cfraction Cfraction::operator-(const Cfraction &other) const {
    return Cfraction(
            this->top * other.bottom - other.top * this->bottom,
            this->bottom * other.bottom);
}

Cfraction Cfraction::operator*(const Cfraction &other) const {
    return Cfraction(this->top * other.top, this->bottom * other.bottom);
}

Cfraction Cfraction::operator/(const Cfraction &other) const {
    return Cfraction(this->top * other.bottom, this->bottom * other.top);
}

void Cfraction::operator+=(const Cfraction &other) {
    this->top = this->top * other.bottom + other.top * this->bottom;
    this->bottom = this->bottom * other.bottom;
}

void Cfraction::operator-=(const Cfraction &other) {
    this->top = this->top * other.bottom - other.top * this->bottom;
    this->bottom = this->bottom * other.bottom;
}

void Cfraction::operator*=(const Cfraction &other) {
    this->top = this->top * other.top;
    this->bottom = this->bottom * other.bottom;
}

void Cfraction::operator/=(const Cfraction &other) {
    this->top = this->top * other.bottom;
    this->bottom = this->bottom * other.top;
}

void Cfraction::operator++() {
    this->top++;
}

void Cfraction::operator--() {
    this->top--;
}

Cfraction::operator double() const {
    return double(this->top) / this->bottom;
}

void Cfraction::operator()(long new_top, long new_bottom) {
    this->top = new_top;
    this->bottom = new_bottom;
}

bool Cfraction::operator==(const Cfraction &other) const {
    return (*this - other).top == 0;
}

bool Cfraction::operator!=(const Cfraction &other) const {
    return (*this - other).top != 0;
}

bool Cfraction::operator<=(const Cfraction &other) const {
    return (*this - other).top <= 0;
}

bool Cfraction::operator>=(const Cfraction &other) const {
    return (*this - other).top >= 0;
}

bool Cfraction::operator>(const Cfraction &other) const {
    return (*this - other).top > 0;
}

bool Cfraction::operator<(const Cfraction &other) const {
    return (*this - other).top < 0;
}

Cfraction &Cfraction::operator=(const Cfraction &other) {
    if (this == &other || other.bottom == 0) return *this;
    this->top = other.top;
    this->bottom = other.bottom;
    return *this;
}