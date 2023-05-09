//
// Created by pedro on 09/05/2023.
//

#include "StockPriceQtd.h"

StockPriceQtd::StockPriceQtd() {}

StockPriceQtd::StockPriceQtd(int stockIndex, int price) : stockIndex(stockIndex), price(price) {}

int StockPriceQtd::getStockIndex() const {
    return stockIndex;
}

void StockPriceQtd::setStockIndex(const int &stockIndex) {
    StockPriceQtd::stockIndex = stockIndex;
}

int StockPriceQtd::getPrice() const {
    return price;
}

void StockPriceQtd::setPrice(const int &price) {
    StockPriceQtd::price = price;
}