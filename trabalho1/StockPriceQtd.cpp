//
// Created by pedro on 09/05/2023.
//

#include "StockPriceQtd.h"

StockPriceQtd::StockPriceQtd() {
    this->stockIndex = -1;
    this->totalPrice = 0;
    this->unitPrice = 0;
    this->newQuantity = 0;
}

StockPriceQtd::StockPriceQtd(int stockIndex, int price, int unitPrice, int quantity) : stockIndex(stockIndex),
                                                                                       totalPrice(price),
                                                                                       unitPrice(unitPrice),
                                                                                       newQuantity(quantity) {}

int StockPriceQtd::getStockIndex() const {
    return stockIndex;
}

void StockPriceQtd::setStockIndex(const int &stockIndex) {
    StockPriceQtd::stockIndex = stockIndex;
}

int StockPriceQtd::getPrice() const {
    return totalPrice;
}

void StockPriceQtd::setPrice(const int &price) {
    StockPriceQtd::totalPrice = price;
}

int StockPriceQtd::getUnitPrice() const {
    return unitPrice;
}

void StockPriceQtd::setUnitPrice(const int &unitPrice) {
    StockPriceQtd::unitPrice = unitPrice;
}

int StockPriceQtd::getNewQuantity() const {
    return newQuantity;
}

void StockPriceQtd::setNewQuantity(const int &newQuantity) {
    StockPriceQtd::newQuantity = newQuantity;
}