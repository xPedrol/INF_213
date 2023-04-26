#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include "HistoryPrice.h"
#include "HistoryEarning.h"
#include "Wallet.h"

using namespace std;

string formatFloat(int n) {
    ostringstream stream;
    stream << (n / 100) << "." << setw(2) << setfill('0') << (n % 100);
    return stream.str();
}

int convertStringToInt(string s) {
    return round(stod(s) * 100);
}

template<class T>
void printData(T *array, int total) {
    for (int i = 0; i < total; ++i) {
        cout << "Price: " << array[i].getPrice() << endl;
        cout << "Date: " << array[i].getDate() << endl;
        cout << "Ticker: " << array[i].getTicker() << endl;
        cout << endl;
    }
}

void printWalletData(Wallet *array, int total) {
    for (int i = 0; i < total; ++i) {
        cout << "Ticker: " << array[i].getTicker() << endl;
        cout << "Quantity: " << array[i].getQuantity() << endl;
        cout << "Purchase price: " << array[i].getPurchasePrice() << endl;
        cout << "Total dividends: " << array[i].getTotalDividends() << endl;
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
        array[i] = T(convertStringToInt(price), date, ticker);
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
        array[i] = Wallet(quantity, ticker, convertStringToInt(purchasePrice), stod(totalDividends) * 100);
    }
}


int getStockDayPriceSequencial(HistoryPrice *prices, int totalPrices, string ticker, string date) {
    for (int i = 0; i < totalPrices; ++i) {
//        if(ticker == "bbas3"){
//            cout << "TickerT: " << prices[i].getTicker() << endl;
//            cout << "DateT: " << prices[i].getDate() << endl;
//            cout << "PriceT: " << prices[i].getPrice() << endl;
//            cout << endl;
//        }
        if (prices[i].getTicker() == ticker && prices[i].getDate() == date) {
            return prices[i].getPrice();
        }
    }
    return -1;
}

int getStockDayPriceBinary(HistoryPrice *prices, int totalPrices, string ticker, string date) {
    int left = 0;
    int right = totalPrices - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (prices[middle].getTicker() == ticker && prices[middle].getDate() == date) {
            return prices[middle].getPrice();
        } else if (prices[middle].getTicker() < ticker) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

void handleActions(string action, string params, string header, HistoryPrice *prices, int totalPrices,
                   HistoryEarning *earnings, int totalEarnings, Wallet *wallets, int totalWallets) {
    // get first and last param
    string *paramsArray = new string[2];
    int i = 0;
    stringstream ssin(params);
    while (ssin.good() && i < 2) {
        ssin >> paramsArray[i];
        ++i;
    }
    if (action == "valor") {
        // imprimir ação e pegar o preco total em certo dia
        int totalValue = 0;
        cout << left << setw(15) << "Ticker"
             << left << setw(20) << "Quantidade"
             << left << setw(15) << "Compra"
             << left << setw(15) << "Dividendo"
             << left << setw(15) << "Valor" << endl;
        for (int j = 0; j < totalWallets; ++j) {
            int price = getStockDayPriceSequencial(prices, totalPrices, wallets[j].getTicker(), paramsArray[0]) *
                        wallets[j].getQuantity();
            totalValue += price;
            // Data
            cout << left << setw(15) << wallets[j].getTicker()
                 << left << setw(20) << wallets[j].getQuantity()
                 << left << setw(15) << formatFloat(wallets[j].getPurchasePrice())
                 << left << setw(15) << formatFloat(wallets[j].getTotalDividends())
                 << left << setw(15) << formatFloat(price) << endl;
        }
        cout << "Valor total da carteira: ";
        cout << left << setw(40) << "" << formatFloat(totalValue) << endl;
        cout << endl;
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
        cout << "--------------------------------------------" << endl;
        cout << "Printing history earnings: " << endl;
        printData(earnings, totalEarnings);
        cout << "--------------------------------------------" << endl;
        cout << "Printing wallets: " << endl;
        printWalletData(wallets, totalStocks);

        // Reading rest of inputs
        string line;
        string header = "";
        int i = 0;

        while (getline(cin, line)) {
            if (line != header && header == "") {
                header = line;
            } else if (header != "") {
                string action = line.substr(0, line.find(" "));
                string params = line.substr(line.find(" ") + 1, line.length());
                handleActions(action, params, header, prices, totalPrices, earnings, totalEarnings, wallets,
                              totalStocks);
                i++;
            }
        }
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}