#include <iostream>
#include <string>
#include "HistoryPrice.h"
#include "HistoryEarning.h"
#include "Wallet.h"

using namespace std;

template<class T>
void printData(T *array, int total) {
    for (int i = 0; i < total; ++i) {
        cout << "Price at position " << i << ": " << array[i].getPrice() << endl;
        cout << "Date at position " << i << ": " << array[i].getDate() << endl;
        cout << "Ticker at position " << i << ": " << array[i].getTicker() << endl;
        cout << endl;
    }
}

void printWalletData(Wallet *array, int total) {
    for (int i = 0; i < total; ++i) {
        cout << "Ticker at position " << i << ": " << array[i].getTicker() << endl;
        cout << "Quantity at position " << i << ": " << array[i].getQuantity() << endl;
        cout << "Purchase price at position " << i << ": " << array[i].getPurchasePrice() << endl;
        cout << "Total dividends at position " << i << ": " << array[i].getTotalDividends() << endl;
        cout << endl;
    }
}

template<class T>
void readInitialData(T *array, int total) {
    for (int i = 0; i < total; ++i) {
        string price;
        string date;
        string ticker;
        cout << "Enter the date, ticker and price at position " << i << ": " << endl;
        cin >> date >> ticker >> price;
        array[i] = T(stod(price) * 100, date, ticker);
    }
}

void readWalletData(Wallet *array, int total) {
    for (int i = 0; i < total; ++i) {
        int quantity;
        string ticker;
        string purchasePrice;
        string totalDividends;
        cout << "Enter the ticker, quantity, purchase price and total dividends at position " << i << ": " << endl;
        cin >> ticker >> quantity >> purchasePrice >> totalDividends;
        array[i] = Wallet(quantity, ticker, stod(purchasePrice) * 100, stod(totalDividends) * 100);
    }
}


int main() {
    // Declaring variables
    int totalPrices;
    int totalEarnings;
    int totalStocks;
    HistoryPrice *prices;
    HistoryEarning *earnings;
    Wallet *wallets;
    // Reading inputs
    try {
        cout << "Enter the number of prices: " << endl;
        cin >> totalPrices;
        prices = new HistoryPrice[totalPrices];
        readInitialData(prices, totalPrices);

        cout << "Enter the number of earnings: " << endl;
        cin >> totalEarnings;
        earnings = new HistoryEarning[totalEarnings];
        readInitialData(earnings, totalEarnings);

        cout << "Enter the number of wallet's stocks: " << endl;
        cin >> totalStocks;
        wallets = new Wallet[totalStocks];
        readWalletData(wallets, totalStocks);



        // Printing data
        cout << "Printing history prices: " << endl;
        printData(prices, totalPrices);
        cout <<"--------------------------------------------" << endl;
        cout << "Printing history earnings: " << endl;
        printData(earnings, totalEarnings);
        cout <<"--------------------------------------------" << endl;
        cout << "Printing wallets: " << endl;
        printWalletData(wallets, totalStocks);

    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}