//
// Created by pedro on 20/04/2023.
//
#include <string>
#include "Wallet.h"

Wallet::Wallet() {
    quantity = 0;
    ticker = "";
    purchasePrice = 0;
    totalDividends = 0;
}

Wallet::Wallet(int quantity, string ticker, int purchasePrice, int totalDividends) {
    this->quantity = quantity;
    this->ticker = ticker;
    this->purchasePrice = purchasePrice;
    this->totalDividends = totalDividends;
}

int Wallet::getQuantity() {
    return quantity;
}

string Wallet::getTicker() {
    return ticker;
}

int Wallet::getPurchasePrice() {
    return purchasePrice;
}

int Wallet::getTotalDividends() {
    return totalDividends;
}

void Wallet::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Wallet::setTicker(string ticker) {
    this->ticker = ticker;
}

void Wallet::setPurchasePrice(int purchasePrice) {
    this->purchasePrice = purchasePrice;
}

void Wallet::setTotalDividends(int totalDividends) {
    this->totalDividends = totalDividends;
}
