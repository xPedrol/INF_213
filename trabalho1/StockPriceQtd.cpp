//
// Created by pedro on 09/05/2023.
//
#include <string>
#include "Wallet.h"
#include "StockPriceQtd.h"

StockPriceQtd::StockPriceQtd() {
    this->stock = nullptr;
    this->totalPrice = 0;
    this->unitPrice = 0;
    this->newQuantity = 0;
}

StockPriceQtd::StockPriceQtd(Wallet *wallet, int price, int unitPrice, int quantity) {
    this->stock = wallet;
    this->totalPrice = price;
    this->unitPrice = unitPrice;
    this->newQuantity = quantity;
}

Wallet *StockPriceQtd::getStock() const {
    return stock;
}

void StockPriceQtd::setStock(Wallet *wallet) {
    StockPriceQtd::stock = wallet;
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