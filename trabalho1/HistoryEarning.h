//
// Created by pedro on 20/04/2023.
//
using namespace std;

class HistoryEarning {
    int price;
    string date;
    string ticker;

public:
    HistoryEarning();

    HistoryEarning(int price, string date, string ticker);

    int getPrice() const;

    void setPrice(int price);

    const string getDate() const;

    void setDate(const string date);

    const string getTicker() const;

    void setTicker(const string ticker);
};