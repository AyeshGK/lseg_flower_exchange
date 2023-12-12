#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <memory>



class Order {
public:
    // constructor
    Order(const std::string& clientOrderId, const std::string& instrument, int side, int quantity, double price, const std::string& traderId);

    Order(
        const std::string& clientOrderId,
        const std::string& instrument,
        const std::string& side, 
        const std::string& quantity,
        const std::string& price,
        const std::string& traderId);



    // declare getters
    std::string getClientOrderId() const;
    std::string getInstrument() const;
    int getSide() const;
    int getQuantity() const;
    double getPrice() const;
    const std::string& getTraderId() const;
    const std::string& getReason() const;
    int getStatus() const;

    // declare setters
    void setClientOrderId(const std::string& clientOrderId);
    void setInstrument(const std::string& instrument);
    void setSide(int side);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setTraderId(const std::string& traderId);

    void resetQuantity(int quantity);
    void setStatus(int status);


    // declare string setters 
    void setSide(const std::string& side);
    void setQuantity(const std::string& quantity);
    void setPrice(const std::string& price);

    // operator overloading for priority queue 
     // Comparison operators for sorting
    // bool operator>(const Order& rhs) const; // For descending order (buy side)
    // bool operator<(const Order& rhs) const; // For ascending order (sell side)


private:
    std::string clientOrderId;
    std::string instrument;
    int side;        // Assuming 1 for "Buy" and 2 for "Sell"
    int quantity;
    double price;
    std::string traderId;

    //delare private property called reason which maximum 50 characters and is initialized to empty string
    std::string reason = "";
    int status = 0; 

        // Static member variable for valid instruments
    // static const std::vector<std::string> validInstruments;
};

using OrderPtr = std::shared_ptr<Order>;

#endif  // ORDER_H
