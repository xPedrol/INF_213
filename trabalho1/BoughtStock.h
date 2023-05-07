
#include <string>

class BoughtStock {
    string ticker;
    int quantity;
    int price;

public:
    BoughtStock();
    BoughtStock(string name, int quantity, int price);
    string getTicker();
    int getQuantity() const;
    int getPrice() const;
    int getTotal() const;
    void setQuantity(int quantity);
    void setPrice(int price);
};


