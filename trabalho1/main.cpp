//#include <chrono>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm> // std::unique
#include <sstream>
#include <string>
#include "HistoryPrice.h"
#include "HistoryEarning.h"
#include "Wallet.h"
#include "MinMax.h"
#include "BoughtStock.h"    // BoughtStock
#include "StockPriceQtd.h"

using namespace std;

const string cp = "compacta";
const string mc = "mostrarCabecalhos";
const string ne = "naoMostrarCabecalhos";

bool compareDates(const string &date1, const string &date2) {
    int year1 = stoi(date1.substr(6));
    int year2 = stoi(date2.substr(6));
    if (year1 != year2)
        return year1 < year2;
    int month1 = stoi(date1.substr(3, 2));
    int month2 = stoi(date2.substr(3, 2));
    if (month1 != month2)
        return month1 < month2;
    int day1 = stoi(date1.substr(0, 2));
    int day2 = stoi(date2.substr(0, 2));
    return day1 < day2;
}


class DividendCompare {
public:
    bool operator()(Wallet &a,
                    Wallet &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        return a.getTotalDividends() > b.getTotalDividends();
    }
};

template<class T>
class OnlyTickerCompare {
public:
    bool operator()(T &a,
                    T &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"

        return a.getTicker() < b.getTicker();
    }
};

class DividendTickerCompare {
public:
    bool operator()(Wallet &a,
                    Wallet &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        if (a.getTotalDividends() == b.getTotalDividends()) {
            OnlyTickerCompare<Wallet> tickerCompare;
            return tickerCompare(a, b);
        }
        return a.getTotalDividends() > b.getTotalDividends();
    }
};

class QuantityCompare {
public:
    bool operator()(Wallet &a,
                    Wallet &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        return a.getQuantity() > b.getQuantity();
    }
};

class PriceCompare {
public:
    bool operator()(Wallet &a,
                    Wallet &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        return a.getPurchasePrice() > b.getPurchasePrice();
    }
};

template<class T>
class TickerCompare {
public:
    bool operator()(const T &a,
                    const T &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        if (a.getTicker() == b.getTicker())
            return compareDates(a.getDate(), b.getDate());
        return a.getTicker() < b.getTicker();
    }
};

template<class T>
class DateCompare {
public:
    bool operator()(const T &a,
                    const T &b) const { // retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        if (a.getDate() == b.getDate())
            return a.getTicker() < b.getTicker();
        return compareDates(a.getDate(), b.getDate());
    }
};

template<class FuncType, class T>
void insertionSort(T *v, int n, FuncType func) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado
        T elemInserir = v[i];
        int j = i - 1;
        while (j >= 0 && func(elemInserir, v[j])) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = elemInserir;
    }
}

// particiona o subvetor v[beg, ..., end - 1]
// retorna a posição onde o pivo foi armazenado
template<class FuncType, class T>
int particiona(T *v, int beg, int end, int pivo, FuncType func) {
    T valorPivo = v[pivo];
    // colocamos o pivo temporariamente na ultima posição
    swap(v[pivo], v[end - 1]);
    // ao acharmos um elemento menor do que o pivo, vamos coloca-lo
    // na posicao "pos"
    int pos = beg;
    for (int i = beg; i < end - 1; i++) {
        if (func(v[i], valorPivo)) {
            swap(v[pos], v[i]);
            pos++;
        }
    }
    // coloque o pivo depois do ultimo elemento menor que ele
    swap(v[pos], v[end - 1]);
    return pos;
}

template<class FuncType, class T>
void quickSort2(T *v, int beg, int end, FuncType func) {
    if (beg == end)
        return;
    if (end - beg <= 90) {
        insertionSort(v + beg, end - beg, func);
    } else {
        int pivoAleatorio = rand() % (end - beg) + beg; // escolhe um índice aleatório entre beg e end
        int pos = particiona(v, beg, end, pivoAleatorio, func);
        quickSort2(v, beg, pos, func);
        quickSort2(v, pos + 1, end, func);
    }
}

template<class FuncType, class T>
int quickSort(T *v, int n, FuncType func) {
    quickSort2(v, 0, n, func);
    return 0;
}

string formatFloat(int n) {
    ostringstream stream;
    stream << (n / 100) << "." << setw(2) << setfill('0') << (n % 100);
    return stream.str();
}

int convertStringToInt(const string &s) {
    return round(stod(s) * 100);
}

template<class T>
void readInitialData(T *array, int total) {
    for (int i = 0; i < total; i++) {
        string price;
        string date;
        string ticker;
//        cout << "Enter the date, ticker and totalPrice at position " << i << ": " << endl;
        cin >> date >> ticker >> price;
        array[i] = T(convertStringToInt(price), date, ticker);
    }
}

void readWalletData(Wallet *array, int total) {
    for (int i = 0; i < total; i++) {
        int quantity;
        string ticker;
        string purchasePrice;
        string totalDividends;
//        cout << "Enter the ticker, quantity, purchase totalPrice and total dividends at position " << i << ": " << endl;
        cin >> ticker >> quantity >> purchasePrice >> totalDividends;
        array[i] = Wallet(quantity, ticker, convertStringToInt(purchasePrice), convertStringToInt(totalDividends));
    }
}

template<class T>
int buscaBinByDate(T *array, const int &begin, const int &end, const string &date, int maior, bool getBiggestIndex) {
    if (begin > end)
        return maior;
    int meio = (end - begin) / 2 + begin;
    if (array[meio].getDate() == date) {
        if (getBiggestIndex) {
            if (meio < end && array[meio + 1].getDate() == date) {
                return buscaBinByDate(array, meio + 1, end, date, maior, getBiggestIndex);
            }
        } else {
            if (meio > 0 && array[meio - 1].getDate() == date) {
                return buscaBinByDate(array, begin, meio - 1, date, maior, getBiggestIndex);
            }
        }
        return meio;
    }
    if (compareDates(date, array[meio].getDate())) {
        maior = meio;
        return buscaBinByDate(array, begin, meio - 1, date, maior, getBiggestIndex);
    }
    return buscaBinByDate(array, meio + 1, end, date, maior, getBiggestIndex);
}

template<class T>
int buscaBinByTicker(T *array, const int &begin, const int &end, const string &ticker, int maior) {
    if (begin > end)
        return maior;
    int meio = (end - begin) / 2 + begin;
    if (array[meio].getTicker() == ticker) {
        return meio;
    }
    if (array[meio].getTicker() > ticker) {
        maior = meio;
        return buscaBinByTicker(array, begin, meio - 1, ticker, maior);
    }
    return buscaBinByTicker(array, meio + 1, end, ticker, maior);
}

int getStockDayPriceSequencial(HistoryPrice *prices, int totalPrices, const string &ticker, const string &date) {
    for (int i = 0; i < totalPrices; i++) {
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
            if (compareDates(prices[middle].getDate(), date)) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
    }
    return -1;
}

void printBuyStockOperator(const string &ticker, int quantity, int value) {
    cout << left << setw(6) << ticker
         << right << setw(11) << quantity
         << right << setw(14) << formatFloat(value) << endl;
}


void
buyStocks2(Wallet *stocks, int totalStock, HistoryPrice *prices, int totalPrices, const string &date, int newValue,
           int &totalnewPurchase, StockPriceQtd *stockPriceQtd) {
    TickerCompare<HistoryPrice> tickerCompare;
    quickSort(prices, totalPrices, tickerCompare);
//    OnlyTickerCompare<Wallet> onlyTickerCompare;
//    quickSort(stocks, totalStock, onlyTickerCompare);
    for (int i = 0; i < totalStock; i++) {
        stockPriceQtd[i].setStock(&stocks[i]);
        stockPriceQtd[i].setUnitPrice(
                getArrayPriceByTicker(prices, totalPrices, stocks[i].getTicker(), date));
        stockPriceQtd[i].setPrice(stockPriceQtd[i].getUnitPrice() * stocks[i].getQuantity());
        stockPriceQtd[i].setNewQuantity(0);
        if (stockPriceQtd[i].getPrice() == -1) {
            return;
        }
    }
    quickSort(stockPriceQtd, totalStock, [](StockPriceQtd a, StockPriceQtd b) {
        if (a.getPrice() == b.getPrice()) {
            return a.getStock()->getTicker() < b.getStock()->getTicker();
        }
        return a.getPrice() < b.getPrice();
    });
    while (newValue > 0) {
        int smallerStockUnitPrice = stockPriceQtd[0].getUnitPrice();
        int secondSmallerStockUnitPrice = stockPriceQtd[1].getUnitPrice();
        Wallet *smallerStock = stockPriceQtd[0].getStock();
        Wallet *secondSmallerStock = stockPriceQtd[1].getStock();
        int maxBuyValue = (secondSmallerStockUnitPrice * secondSmallerStock->getQuantity() -
                           smallerStockUnitPrice * smallerStock->getQuantity());
        int qtdToBuy;
        if (maxBuyValue > 0) {
            qtdToBuy = ceil((double) maxBuyValue / (double) smallerStockUnitPrice);
            if (maxBuyValue == smallerStockUnitPrice) {
                qtdToBuy += 1;
            }
        } else {
            qtdToBuy = 1;
        }
        if (newValue < qtdToBuy * smallerStockUnitPrice) {
            qtdToBuy = newValue / smallerStockUnitPrice;
        }
//        int qtdToBuy = newValue / smallerStockUnitPrice;
        if (qtdToBuy > newValue || qtdToBuy <= 0) {
            break;
        }
        newValue -= qtdToBuy * smallerStockUnitPrice;
        smallerStock->setQuantity(smallerStock->getQuantity() + qtdToBuy);
        smallerStock->setPurchasePrice(smallerStock->getPurchasePrice() + qtdToBuy * smallerStockUnitPrice);
        totalnewPurchase += qtdToBuy * smallerStockUnitPrice;
        stockPriceQtd[0].setPrice(stockPriceQtd[0].getPrice() + qtdToBuy * smallerStockUnitPrice);
        stockPriceQtd[0].setNewQuantity(stockPriceQtd[0].getNewQuantity() + qtdToBuy);
        if(newValue <= 0) {
            break;
        }
        quickSort(stockPriceQtd, totalStock, [](StockPriceQtd a, StockPriceQtd b) {
            if (a.getPrice() == b.getPrice()) {
                return a.getStock()->getTicker() < b.getStock()->getTicker();
            }
            return a.getPrice() < b.getPrice();
        });
//        for (int i = 0; i < totalStock - 1; i++) {
//            if (stockPriceQtd[i].getPrice() > stockPriceQtd[i + 1].setPrice()) {
//                swap(stockPriceQtd[i], stockPriceQtd[i + 1]);
//            } else {
//                break;
//            }
//        }
    }
}

void buyStocks(Wallet *stock, int totalStock, HistoryPrice *prices, int totalPrices, const string &date, int newValue,
               int &totalnewPurchase, BoughtStock *boughtStocks, int &totalBoughtStocks) {
    Wallet *lowerStock = &stock[0];
    int priceMinValorStockInDate = getArrayPriceByTicker(prices, totalPrices, lowerStock->getTicker(), date);
    for (int i = 1; i < totalStock; i++) {
        int stockUnitPriceInDate = getArrayPriceByTicker(prices, totalPrices, stock[i].getTicker(), date);
        if (stockUnitPriceInDate) {
            if (stockUnitPriceInDate * stock[i].getQuantity() < priceMinValorStockInDate * lowerStock->getQuantity()) {
                lowerStock = &stock[i];
                priceMinValorStockInDate = stockUnitPriceInDate;
            } else if (stockUnitPriceInDate * stock[i].getQuantity() ==
                       priceMinValorStockInDate * lowerStock->getQuantity()) {
                if (stock[i].getTicker() < lowerStock->getTicker()) {
                    lowerStock = &stock[i];
                    priceMinValorStockInDate = stockUnitPriceInDate;
                }
            }
        }
    }

    if (newValue < priceMinValorStockInDate) {
        return;
    }
    lowerStock->setQuantity(lowerStock->getQuantity() + 1);
    lowerStock->setPurchasePrice(lowerStock->getPurchasePrice() + priceMinValorStockInDate);
    newValue -= priceMinValorStockInDate;
    totalnewPurchase += priceMinValorStockInDate;
    if (totalBoughtStocks == 0) {
        boughtStocks[totalBoughtStocks] = BoughtStock(lowerStock->getTicker(), 1, priceMinValorStockInDate);
        totalBoughtStocks++;
    } else {
        if (totalBoughtStocks == 1 && boughtStocks[0].getTicker() == lowerStock->getTicker()) {
            boughtStocks[0].setQuantity(boughtStocks[0].getQuantity() + 1);
            boughtStocks[0].setPrice(boughtStocks[0].getPrice() + priceMinValorStockInDate);
        } else {
            int stockIndex = buscaBinByTicker(boughtStocks, 0, totalBoughtStocks - 1, lowerStock->getTicker(), -1);
            if (stockIndex != -1 && boughtStocks[stockIndex].getTicker() == lowerStock->getTicker()) {
                boughtStocks[stockIndex].setQuantity(boughtStocks[stockIndex].getQuantity() + 1);
                boughtStocks[stockIndex].setPrice(boughtStocks[stockIndex].getPrice() + priceMinValorStockInDate);
            } else {
                totalBoughtStocks++;
                if (stockIndex == -1) {
                    boughtStocks[totalBoughtStocks - 1] = BoughtStock(lowerStock->getTicker(), 1,
                                                                      priceMinValorStockInDate);
                } else {
                    for (int i = totalBoughtStocks - 1; i > stockIndex; i--) {
                        boughtStocks[i] = boughtStocks[i - 1];
                    }
                    boughtStocks[stockIndex] = BoughtStock(lowerStock->getTicker(), 1, priceMinValorStockInDate);
                }

            }
        }
    }
    if (newValue > 0) {
        buyStocks(stock, totalStock, prices, totalPrices, date, newValue, totalnewPurchase, boughtStocks,
                  totalBoughtStocks);
    }
}

int getDividendByTickerAndRangeDate(HistoryEarning *earnings, int totalEarnings, const string &ticker,
                                    const string &startDate,
                                    const string &endDate) {
    int left = 0;
    int right = totalEarnings - 1;
    int fisrtDateInRange = buscaBinByDate(earnings, left, right, startDate, -1, false);
//    int lastDateInRange = buscaBinByDate(earnings, left, right, endDate, -1, true);
    if (fisrtDateInRange == -1) {
        fisrtDateInRange = 0;
    }
    int totalDividendsInRange = 0;
    for (int i = fisrtDateInRange; i < totalEarnings; i++) {
        if (compareDates(endDate, earnings[i].getDate())) {
            break;
        }
        if (earnings[i].getTicker() == ticker) {
            totalDividendsInRange += earnings[i].getPrice();
        }
    }
    return totalDividendsInRange;
}

MinMax
getMaxMinDayPrice(HistoryPrice *prices, int totalPrices, Wallet *stocks, int totalStocks, const string &startDate,
                  const string &endDate) {

    auto *datesInRange = new string[totalPrices];
    int totalDatesInRange = 0;
    int left = 0;
    int right = totalPrices - 1;
    int fisrtDateInRange = buscaBinByDate(prices, left, right, startDate, -1, false);
//    int lastDateInRange = buscaBinByDate(prices, left, right, endDate, -1, true);
    if (fisrtDateInRange == -1) {
        fisrtDateInRange = 0;
    }
    for (int i = fisrtDateInRange; i < totalPrices; i++) {
        if (compareDates(endDate, prices[i].getDate())) {
            break;
        }
        datesInRange[totalDatesInRange] = prices[i].getDate();
        totalDatesInRange++;
    }
    totalDatesInRange = unique(datesInRange, datesInRange + totalDatesInRange) - datesInRange;
    string minDate;
    string maxDate;
    int maxPrice = 0;
    int minPrice = 0;
    TickerCompare<HistoryPrice> tickerCompare;
    quickSort(prices, totalPrices, tickerCompare);
    // sort(prices, prices + totalPrices, TickerCompare<HistoryPrice>());
    for (int i = 0; i < totalDatesInRange; i++) {
        int dateTotalprice = 0;
        for (int j = 0; j < totalStocks; j++) {
            int stockDayPrice = getArrayPriceByTicker(prices, totalPrices, stocks[j].getTicker(), datesInRange[i]);
            if (stockDayPrice == -1)
                continue;
            dateTotalprice += stockDayPrice * stocks[j].getQuantity();
        }
        if (minPrice == 0 || dateTotalprice < minPrice) {
            minPrice = dateTotalprice;
            minDate = datesInRange[i];
        }
        if (dateTotalprice > maxPrice) {
            maxPrice = dateTotalprice;
            maxDate = datesInRange[i];
        }
    }
    delete[] datesInRange;
    return {maxDate, maxPrice, minDate, minPrice};
}

void prindMinMaxOperatorHeader(const string &header, const string &startDate, const string &endDate) {
    if (header == mc) {
        cout << "Minimos e maximos no intervalo: ";
        cout << startDate << " a " << endDate << endl;
    }
}

void printDividendOperatorHeader(const string &header, const string &startDate, const string &endDate) {
    if (header == mc) {
        cout << "Dividendos no intervalo: ";
        cout << startDate << " a " << endDate << endl;
        cout << left << setw(7) << "Ticker"
             << left << setw(18) << "Quantidade"
             << left << setw(11) << "Compra"
             << left << setw(13) << "Dividendo"
             << "Div.inter." << endl;
    }
}

void printValorOperatorHeader(const string &header, const string &date) {
    if (header == mc) {
        cout << "Data: " << date << endl;
        cout << left << setw(6) << "Ticker"
             << right << setw(11) << "Quantidade"
             << right << setw(14) << "Compra"
             << right << setw(14) << "Dividendo"
             << right << setw(14) << "Valor" << endl;
    }
}

void printValorOperator(const string &ticker, int quantity, int buyPrice, int dividend, int value) {
    cout << left << setw(6) << ticker
         << right << setw(11) << quantity
         << right << setw(14) << formatFloat(buyPrice)
         << right << setw(14) << formatFloat(dividend)
         << right << setw(14) << formatFloat(value) << endl;
}

void printDividendOperator(const string &ticker, int quantity, int buyPrice, int dividend, int value) {
    cout << left << setw(6) << ticker
         << right << setw(11) << quantity
         << right << setw(14) << formatFloat(buyPrice)
         << right << setw(14) << formatFloat(dividend)
         << right << setw(14) << formatFloat(value) << endl;
}

void printBuyStockHeader(const string &header) {
    if (header == mc) {
        cout << "Dados do aporte:" << endl;
        cout << "Ticker"
             << right << setw(11) << "Quantidade"
             << right << setw(14) << "Valor" << endl;
    }
}


void
handleActions(const string &action, const string &params, const string &header, HistoryPrice *prices, int totalPrices,
              HistoryEarning *earnings, int totalEarnings, Wallet *stocks, int totalStocks) {
    // get first and last param
    auto *paramsArray = new string[2];
    int i = 0;
    stringstream ssin(params);
    while (ssin.good() && i < 2) {
        ssin >> paramsArray[i];
        i++;
    }
    if (action == "valor") {
        int totalValue = 0;
        printValorOperatorHeader(header, paramsArray[0]);
        for (int j = 0; j < totalStocks; j++) {
            int price = getStockDayPriceSequencial(prices, totalPrices, stocks[j].getTicker(), paramsArray[0]) *
                        stocks[j].getQuantity();
            if (price < 0) {
                price = 0;
            }
            totalValue += price;
            if (header != cp) {
                printValorOperator(stocks[j].getTicker(), stocks[j].getQuantity(), stocks[j].getPurchasePrice(),
                                   stocks[j].getTotalDividends(), price);
            }
        }
        if (header != cp) {
            cout << "Valor total da carteira:";
            cout << right << setw(35);
        }
        cout << formatFloat(totalValue) << endl;
    }
    if (action == "valorFast") {
        printValorOperatorHeader(header, paramsArray[0]);
        TickerCompare<HistoryPrice> tickerCompare;
        quickSort(prices, totalPrices, tickerCompare);
        int totalValue = 0;
        for (int j = 0; j < totalStocks; j++) {
            int price = getArrayPriceByTicker(prices, totalPrices, stocks[j].getTicker(), paramsArray[0]) *
                        stocks[j].getQuantity();
            if (price < 0) {
                price = 0;
            }
            totalValue += price;
            if (header != cp) {
                printValorOperator(stocks[j].getTicker(), stocks[j].getQuantity(), stocks[j].getPurchasePrice(),
                                   stocks[j].getTotalDividends(), price);
            }
        }
        if (header != cp) {
            cout << "Valor total da carteira:";
            cout << right << setw(35);
        }
        cout << formatFloat(totalValue) << endl;
    }
    if (action == "dividendo") {
        printDividendOperatorHeader(header, paramsArray[0], paramsArray[1]);
        DateCompare<HistoryEarning> dateCompare;
        quickSort(earnings, totalEarnings, dateCompare);
        int totalDividend = 0;
        for (int j = 0; j < totalStocks; j++) {
            int dividend =
                    getDividendByTickerAndRangeDate(earnings, totalEarnings, stocks[j].getTicker(), paramsArray[0],
                                                    paramsArray[1]) *
                    stocks[j].getQuantity();
            totalDividend += dividend;
            if (header != cp) {
                printDividendOperator(stocks[j].getTicker(), stocks[j].getQuantity(), stocks[j].getPurchasePrice(),
                                      stocks[j].getTotalDividends(), dividend);
            }
        }
        if (header != cp) {
            cout << "Total de dividendos: ";
            cout << right << setw(38);
        }
        cout << formatFloat(totalDividend) << endl;
    }
    if (action == "mimax") {
        prindMinMaxOperatorHeader(header, paramsArray[0], paramsArray[1]);
        DateCompare<HistoryPrice> dateCompare;
        quickSort(prices, totalPrices, dateCompare);
        MinMax minMax = getMaxMinDayPrice(prices, totalPrices, stocks, totalStocks, paramsArray[0], paramsArray[1]);
        if (header != cp) {
            cout << "Valor minimo no dia " << minMax.getMinDate() << ":";
            cout << right << setw(14);
        }
        cout << formatFloat(minMax.getMinPrice()) << endl;
        if (header != cp) {
            cout << "Valor maximo no dia " << minMax.getMaxDate() << ":";
            cout << right << setw(14);
        }
        cout << formatFloat(minMax.getMaxPrice()) << endl;
    }
    if (action == "ordenar") {
        if (paramsArray[0] == "ticker") {
            OnlyTickerCompare<Wallet> tickerCompare;
            quickSort(stocks, totalStocks, tickerCompare);
        }
        if (paramsArray[0] == "quantidade") {
            QuantityCompare quantityCompare;
            quickSort(stocks, totalStocks, quantityCompare);
        }
        if (paramsArray[0] == "preco") {
            PriceCompare priceCompare;
            quickSort(stocks, totalStocks, priceCompare);
        }
        if (paramsArray[0] == "dividendo") {
            DividendCompare dividendCompare;
            quickSort(stocks, totalStocks, dividendCompare);
        }
        if (paramsArray[0] == "dividendoticker") {
            DividendTickerCompare dividendTickerCompare;
            quickSort(stocks, totalStocks, dividendTickerCompare);
        }
    }
    if (action == "aporte") {
        printBuyStockHeader(header);
        int convertedPrice = convertStringToInt(paramsArray[1]);
        int totalNewPurchase = 0;
        auto *stockPriceQtd = new StockPriceQtd[totalStocks];
        buyStocks2(stocks, totalStocks, prices, totalPrices, paramsArray[0], convertedPrice, totalNewPurchase,
                   stockPriceQtd);
        if (header != cp) {
            for (int j = 0; j < totalStocks; j++) {
                Wallet *stock = stockPriceQtd[j].getStock();
                if (stockPriceQtd[j].getNewQuantity() == 0) {
                    break;
                }
                int price = stockPriceQtd[j].getUnitPrice() * stockPriceQtd[j].getNewQuantity();
                printBuyStockOperator(stock->getTicker(), stockPriceQtd[j].getNewQuantity(), price);
            }
        }
        delete[] stockPriceQtd;
        if (header != cp) {
            cout << "Total aportado:";
            cout << right << setw(16);
        }
        cout << formatFloat(totalNewPurchase) << endl;
    }
    delete[] paramsArray;
    if (header == mc && action != "ordenar") {
        cout << endl;
    }
}

int main() {
//    auto start_time = chrono::high_resolution_clock::now();
    // Declaring variables
    int totalPrices;
    int totalEarnings;
    int totalStocks;
    HistoryPrice *prices;
    HistoryEarning *earnings;
    Wallet *stocks;
    // Reading inputs
    try {
//        cout << "Enter the number of prices: " << endl;
        cin >> totalPrices;
        prices = new HistoryPrice[totalPrices];
        readInitialData(prices, totalPrices);

//        cout << "Enter the number of earnings: " << endl;
        cin >> totalEarnings;
        earnings = new HistoryEarning[totalEarnings];
        readInitialData(earnings, totalEarnings);

//        cout << "Enter the number of stock's stocks: " << endl;
        cin >> totalStocks;
        stocks = new Wallet[totalStocks];
        readWalletData(stocks, totalStocks);

        // Printing data
//        cout << "Printing history prices: " << endl;
//        printData(prices, totalPrices);
//        cout << "--------------------------------------------" << endl;
//        cout << "Printing history earnings: " << endl;
//        printData(earnings, totalEarnings);
//        cout << "--------------------------------------------" << endl;
//        cout << "Printing stocks: " << endl;
//        printWalletData(stocks, totalStocks);

        // Reading rest of inputs
        string line;
        string header;
        int i = 0;

        while (getline(cin, line)) {
            if (line != header && header.empty()) {
                header = line;
            } else if (!header.empty()) {
                string action = line.substr(0, line.find(' '));
                string params = line.substr(line.find(' ') + 1, line.length());
                handleActions(action, params, header, prices, totalPrices, earnings, totalEarnings, stocks,
                              totalStocks);
                i++;
            }
        }
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    delete[] prices;
    delete[] earnings;
    delete[] stocks;
//    auto end_time = chrono::high_resolution_clock::now();
//    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
//    cout << "O programa levou " << duration.count() << " microssegundos para ser executado\n";
    return 0;
}