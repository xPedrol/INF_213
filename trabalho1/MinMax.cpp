//
// Created by pedro on 26/04/2023.
//
#include <string>
#include "MinMax.h"


MinMax::MinMax() {}

MinMax::MinMax(string maxDate, int maxPrice, string minDate, int minPrice) {
    this->maxDate = maxDate;
    this->maxPrice = maxPrice;
    this->minDate = minDate;
    this->minPrice = minPrice;
}

const string MinMax::getMaxDate() const {
    return maxDate;
}

void MinMax::setMaxDate(const string maxDate) {
    this->maxDate = maxDate;
}

int MinMax::getMaxPrice() const {
    return maxPrice;
}

void MinMax::setMaxPrice(int maxPrice) {
    this->maxPrice = maxPrice;
}

const string MinMax::getMinDate() const {
    return minDate;
}

void MinMax::setMinDate(const string minDate) {
    this->minDate = minDate;
}

int MinMax::getMinPrice() const {
    return minPrice;
}

void MinMax::setMinPrice(int minPrice) {
    this->minPrice = minPrice;
}

