//
// Created by pedro on 20/04/2023.
//
using namespace std;

class Wallet {
    int quantity;
    string ticker;
    int purchasePrice;
    int totalDividends;

public:
    Wallet();

    Wallet(int quantity, string ticker, int purchasePrice, int totalDividends);

    int getQuantity();

    string getTicker();

    int getPurchasePrice();

    int getTotalDividends();

    void setQuantity(int quantity);

    void setTicker(string ticker);

    void setPurchasePrice(int purchasePrice);

    void setTotalDividends(int totalDividends);

    void printWallet();
};


