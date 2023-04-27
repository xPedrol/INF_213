#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>    // std::sort
#include <sstream>
#include <string>
#include "HistoryPrice.h"
#include "HistoryEarning.h"
#include "Wallet.h"
#include "MinMax.h"

using namespace std;

template<class T>
class TickerCompare {
public:
    bool operator()(const T &a,
                    const T &b) const { //retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        if (a.getTicker() == b.getTicker())
            return a.getDate() < b.getDate();
        return a.getTicker() < b.getTicker();
    }
};

template<class T>
class DateCompare {
public:
    bool operator()(const T &a,
                    const T &b) const { //retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        if (a.getDate() == b.getDate())
            return a.getTicker() < b.getTicker();
        return a.getDate() < b.getDate();
    }
};

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

template<class T>
int buscaBin(T *array, int begin, int end, string chave, int maior, bool getBiggestIndex) {
    if (begin > end)
        return maior;
    int meio = (end - begin) / 2 + begin;
    if (array[meio].getDate() == chave) {
        if (getBiggestIndex) {
            if (meio < end && array[meio + 1].getDate() == chave) {
                return buscaBin(array, meio + 1, end, chave, maior, getBiggestIndex);
            }
        } else {
            if (meio > 0 && array[meio - 1].getDate() == chave) {
                return buscaBin(array, begin, meio - 1, chave, maior, getBiggestIndex);
            }
        }
        return meio;
    }
    if (array[meio].getDate() > chave) {
        maior = meio;
        return buscaBin(array, begin, meio - 1, chave, maior, getBiggestIndex);
    }
    return buscaBin(array, meio + 1, end, chave, maior, getBiggestIndex);
}

int getStockByTickerBinary(HistoryPrice *prices, int totalPrices, string ticker) {
    int left = 0;
    int right = totalPrices - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (prices[middle].getTicker() == ticker) {
            return middle;
        } else if (prices[middle].getTicker() < ticker) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

int getStockDayPriceSequencial(HistoryPrice *prices, int totalPrices, string ticker, string date) {
    for (int i = 0; i < totalPrices; ++i) {
        if (prices[i].getTicker() == ticker && prices[i].getDate() == date) {
            return prices[i].getPrice();
        }
    }
    return -1;
}

template<class T>
int getArrayPriceByTicker(T *prices, int totalPrices, string ticker, string date) {
    int left = 0;
    int right = totalPrices - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (prices[middle].getTicker() == ticker && prices[middle].getDate() == date) {
            return prices[middle].getPrice();
        } else if (prices[middle].getTicker() < ticker) {
            left = middle + 1;
        } else if (prices[middle].getTicker() > ticker) {
            right = middle - 1;
        } else {
            if (prices[middle].getDate() < date) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
    }
    return -1;
}

int getDividendByTickerAndRangeDate(HistoryEarning *dividends, int totalDividends, string ticker, string startDate,
                                    string endDate) {
    int left = 0;
    int right = totalDividends - 1;
    int fisrtDateInRange = buscaBin(dividends, left, right, startDate, -1, false);
    int lastDateInRange = buscaBin(dividends, left, right, endDate, -1, true);
    int totalDividendsInRange = 0;
    for (int i = fisrtDateInRange; i <= lastDateInRange; i++) {
        if (dividends[i].getTicker() == ticker) {
            totalDividendsInRange += dividends[i].getPrice();
        }
    }
    return totalDividendsInRange;
}

MinMax getMaxMinDayPrice(HistoryPrice *prices, int totalPrices, Wallet *stocks, int totalStocks, string startDate,
                         string endDate) {

    string *datesInRange = new string[totalPrices];
    int totalDatesInRange = 0;
    int left = 0;
    int right = totalPrices - 1;
    int fisrtDateInRange = buscaBin(prices, left, right, startDate, -1, false);
    int lastDateInRange = buscaBin(prices, left, right, endDate, -1, true);
    for (int i = fisrtDateInRange; i <= lastDateInRange; i++) {
        datesInRange[totalDatesInRange] = prices[i].getDate();
        totalDatesInRange++;
    }
    totalDatesInRange = unique(datesInRange, datesInRange + totalDatesInRange) - datesInRange;
    string minDate = "";
    string maxDate = "";
    int maxPrice = 0;
    int minPrice = 0;
    sort(prices, prices + totalPrices, TickerCompare<HistoryPrice>());
    for (int i = 0; i < totalDatesInRange; i++) {
        int dateTotalprice = 0;
        for (int j = 0; j < totalStocks; j++) {
            int stockDayPrice = getArrayPriceByTicker(prices, totalPrices, stocks[j].getTicker(), datesInRange[i]);
            if (stockDayPrice == -1)
                continue;
            dateTotalprice += stockDayPrice * stocks[j].getQuantity();
        }
        if (minPrice == 0) {
            minPrice = dateTotalprice;
            minDate = datesInRange[i];
        } else if (dateTotalprice < minPrice) {
            minPrice = dateTotalprice;
            minDate = datesInRange[i];
        }
        if (dateTotalprice > maxPrice) {
            maxPrice = dateTotalprice;
            maxDate = datesInRange[i];
        }
    }
    delete[] datesInRange;
    return MinMax(maxDate, maxPrice, minDate, minPrice);
}

void prindMinMaxOperatorHeader(string header, string startDate, string endDate) {
    if (header == "mostrarCabecalhos") {
        cout << "Minimos e maximos no intervalo: ";
        cout << startDate << " a " << endDate << endl;
    }
}

void printDividendOperatorHeader(string header, string startDate, string endDate) {
    if (header == "mostrarCabecalhos") {
        cout << "Dividendos no intervalo: ";
        cout << startDate << " a " << endDate << endl;
        cout << left << setw(15) << "Ticker"
             << left << setw(20) << "Quantidade"
             << left << setw(15) << "Compra"
             << left << setw(15) << "Dividendo"
             << left << setw(15) << "Div.inter." << endl;
    }
}

void printValorOperatorHeader(string header, string date) {
    if (header == "mostrarCabecalhos") {
        cout << "Data: " << date << endl;
        cout << left << setw(15) << "Ticker"
             << left << setw(20) << "Quantidade"
             << left << setw(15) << "Compra"
             << left << setw(15) << "Dividendo"
             << left << setw(15) << "Valor" << endl;
    }

}

void printValorOperator(string ticker, int quantity, int buyPrice, int dividend, int value) {
    cout << left << setw(15) << ticker
         << left << setw(20) << quantity
         << left << setw(15) << formatFloat(buyPrice)
         << left << setw(15) << formatFloat(dividend)
         << left << setw(15) << formatFloat(value) << endl;
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
        int totalValue = 0;
        printValorOperatorHeader(header, paramsArray[0]);
        for (int j = 0; j < totalWallets; ++j) {
            int price = getStockDayPriceSequencial(prices, totalPrices, wallets[j].getTicker(), paramsArray[0]) *
                        wallets[j].getQuantity();
            totalValue += price;
            printValorOperator(wallets[j].getTicker(), wallets[j].getQuantity(), wallets[j].getPurchasePrice(),
                               wallets[j].getTotalDividends(), price);
        }
        cout << "Valor total da carteira: ";
        cout << left << setw(40) << "" << formatFloat(totalValue) << endl;
    }
    if (action == "valorFast") {
        printValorOperatorHeader(header, paramsArray[0]);
        sort(prices, prices + totalPrices, TickerCompare<HistoryPrice>());
        int totalValue = 0;
        for (int j = 0; j < totalWallets; ++j) {
            int price = getArrayPriceByTicker(prices, totalPrices, wallets[j].getTicker(), paramsArray[0]) *
                        wallets[j].getQuantity();
            totalValue += price;
            printValorOperator(wallets[j].getTicker(), wallets[j].getQuantity(), wallets[j].getPurchasePrice(),
                               wallets[j].getTotalDividends(), price);
        }
        cout << "Valor total da carteira: ";
        cout << left << setw(40) << "" << formatFloat(totalValue) << endl;
    }
    if (action == "dividendo") {
        printDividendOperatorHeader(header, paramsArray[0], paramsArray[1]);
        sort(earnings, earnings + totalEarnings, TickerCompare<HistoryEarning>());
        int totalDividend = 0;
        for (int j = 0; j < totalWallets; ++j) {
            int dividend =
                    getDividendByTickerAndRangeDate(earnings, totalEarnings, wallets[j].getTicker(), paramsArray[0],
                                                    paramsArray[1]) *
                    wallets[j].getQuantity();
            totalDividend += dividend;
            printValorOperator(wallets[j].getTicker(), wallets[j].getQuantity(), wallets[j].getPurchasePrice(),
                               wallets[j].getTotalDividends(), dividend);
        }
        cout << "Valor de dividendos: ";
        cout << left << setw(44) << "" << formatFloat(totalDividend) << endl;
    }
    if (action == "mimax") {
        prindMinMaxOperatorHeader(header, paramsArray[0], paramsArray[1]);
        sort(prices, prices + totalPrices, DateCompare<HistoryPrice>());
        MinMax minMax = getMaxMinDayPrice(prices, totalPrices, wallets, totalWallets, paramsArray[0], paramsArray[1]);
        cout << setw(15) << "Valor minimo no dia " << minMax.getMinDate() << ": ";
        cout << setw(15) << "" << setw(15) << formatFloat(minMax.getMinPrice()) << endl;
        cout << setw(15) << "Valor maximo no dia " << minMax.getMaxDate() << ": ";
        cout << setw(15) << "" << setw(15) << formatFloat(minMax.getMaxPrice()) << endl;
    }
    if (header == "mostrarCabecalhos")
        cout << endl;
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