//
// Created by pedro on 07/05/2023.
//
using namespace std;
#include "BoughtStock.h"

BoughtStock::BoughtStock() {
    this->ticker = "";
    this->quantity = 0;
    this->price = 0;
}

BoughtStock::BoughtStock(string newTicker, int newQuantity, int newPrice) {
    this->ticker = newTicker;
    this->quantity = newQuantity;
    this->price = newPrice;
}

string BoughtStock::getTicker() {
    return ticker;
}

int BoughtStock::getQuantity() const {
    return quantity;
}

int BoughtStock::getPrice() const {
    return price;
}

int BoughtStock::getTotal() const {
    return quantity * price;
}

void BoughtStock::setQuantity(int newQuantity) {
    this->quantity = newQuantity;
}

void BoughtStock::setPrice(int newPrice) {
    this->price = newPrice;
}