using namespace std;

class HistoryPrice {
    int price;
    string date;
    string ticker;

public:
    HistoryPrice();

    HistoryPrice(int price, string date, string ticker);

    int getPrice() const;

    void setPrice(int price);

    const string getDate() const;

    void setDate(const string date);

    const string getTicker() const;

    void setTicker(const string ticker);
};
