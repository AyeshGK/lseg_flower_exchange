#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
public:
    Order(const std::string& clientOrderId, const std::string& instrument, int side, int quantity, double price, const std::string& traderId);

    // declare getters
    const std::string& getClientOrderId() const;
    const std::string& getInstrument() const;
    int getSide() const;
    int getQuantity() const;
    double getPrice() const;
    const std::string& getTraderId() const;


private:
    std::string clientOrderId;
    std::string instrument;
    int side;        // Assuming 1 for "Buy" and 2 for "Sell"
    int quantity;
    double price;
    std::string traderId;
};

#endif  // ORDER_H
