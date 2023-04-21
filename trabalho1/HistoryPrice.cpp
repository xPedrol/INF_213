//
// Created by pedro on 20/04/2023.
//
#include <string>
#include "HistoryPrice.h"

HistoryPrice::HistoryPrice() {
    this->ticker = "";
    this->price = 0;
    this->date = "";
}

HistoryPrice::HistoryPrice(int price, string date, string ticker) {
    this->ticker = ticker;
    this->price = price;
    this->date = date;
}

int HistoryPrice::getPrice() const {
    return price;
}

void HistoryPrice::setPrice(int price) {
    HistoryPrice::price = price;
}

const string HistoryPrice::getDate() const {
    return date;
}

void HistoryPrice::setDate(const string date) {
    HistoryPrice::date = date;
}

const string HistoryPrice::getTicker() const {
    return ticker;
}

void HistoryPrice::setTicker(const string ticker) {
    HistoryPrice::ticker = ticker;
}