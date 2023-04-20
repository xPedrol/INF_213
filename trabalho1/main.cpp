#include <iostream>
#include <string>
#include "HistoryPrice.h"
using namespace std;

int main()
{
    // Declaring variables
    int totalPrices;
    HistoryPrice *prices;
    // Reading inputs
    cin >> totalPrices;
    try
    {
        prices = new HistoryPrice[totalPrices];
        for (int i = 0; i < totalPrices; ++i)
        {
            int price;
            string date;
            string ticker;
            cin >> date >> ticker >> price;
            prices[i] = HistoryPrice(price, date, ticker);
            cout << prices[i].getPrice() << " " << prices[i].getDate() << endl;
        }
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}