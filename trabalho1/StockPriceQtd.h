//
// Created by pedro on 09/05/2023.
//

#ifndef TRABALHO1_STOCKPRICEQTD_H
#define TRABALHO1_STOCKPRICEQTD_H


class StockPriceQtd {
    int stockIndex;
    int totalPrice;
    int unitPrice;
    int newQuantity;
public:
    StockPriceQtd();

    StockPriceQtd(int stockIndex, int price, int unitPrice, int quantity);

    int getStockIndex() const;

    void setStockIndex(const int &stockIndex);

    int getPrice() const;

    void setPrice(const int &price);

    int getUnitPrice() const;

    void setUnitPrice(const int &unitPrice);

    int getNewQuantity() const;

    void setNewQuantity(const int &newQuantity);
};


#endif //TRABALHO1_STOCKPRICEQTD_H
