//
// Created by pedro on 09/05/2023.
//

#ifndef TRABALHO1_STOCKPRICEQTD_H
#define TRABALHO1_STOCKPRICEQTD_H


class StockPriceQtd {
    int stockIndex;
    int price;
public:
    StockPriceQtd();

    StockPriceQtd(int stockIndex, int quantity);

    int getStockIndex() const;

    void setStockIndex(const int & stockIndex);

    int getPrice() const;

    void setPrice(const int & price);

};


#endif //TRABALHO1_STOCKPRICEQTD_H
