//
// Created by pedro on 20/04/2023.
//
#include <string>
#include "HistoryEarning.h"

HistoryEarning::HistoryEarning(int price, string date, string ticker) {
    this->price = price;
    this->date = date;
    this->ticker = ticker;
}

int HistoryEarning::getPrice() const {
    return price;
}

void HistoryEarning::setPrice(int price) {
    HistoryEarning::price = price;
}

const string HistoryEarning::getDate() const {
    return date;
}

void HistoryEarning::setDate(const string date) {
    HistoryEarning::date = date;
}

const string HistoryEarning::getTicker() const {
    return ticker;
}

void HistoryEarning::setTicker(const string ticker) {
    HistoryEarning::ticker = ticker;
}

HistoryEarning::HistoryEarning() {
    this->ticker = "";
    this->price = 0;
    this->date = "";
}
