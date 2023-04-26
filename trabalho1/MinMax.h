//
// Created by pedro on 26/04/2023.
//

using namespace std;


class MinMax {
    string maxDate;
    int maxPrice;
    string minDate;
    int minPrice;
public:
    MinMax();

    MinMax(string maxDate, int maxPrice, string minDate, int minPrice);

    const string getMaxDate() const;

    void setMaxDate(const string maxDate);

    int getMaxPrice() const;

    void setMaxPrice(int maxPrice);

    const string getMinDate() const;

    void setMinDate(const string minDate);

    int getMinPrice() const;

    void setMinPrice(int minPrice);
};


