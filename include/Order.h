#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <memory>
#include <chrono>


enum Status {
    NEW = 0,
    REJECTED = 1,
    FILL = 2,
    PFILL = 3
};

enum Side {
    BUY = 1,
    SELL = 2
};


class Order {
public:
    // constructor
    Order(const std::string& clientOrderId,
        const std::string& instrument,
        int side, int quantity, 
        double price
        // ,const std::string& traderId
        );

    Order(const std::string& clientOrderId,
        const std::string& instrument,
        const std::string& side, 
        const std::string& quantity,
        const std::string& price
        // ,const std::string& traderId
        );

    // declare getters
    std::string getClientOrderId() const;
    std::string getInstrument() const;
    int getSide() const;
    int getQuantity() const;
    double getPrice() const;
    // const std::string& getTraderId() const;
    const std::string& getReason() const;
    int getStatus() const;
    int getOrderId() const;
    std::chrono::system_clock::time_point getTransactionTime() const;


    // declare setters
    void setClientOrderId(const std::string& clientOrderId);
    void setInstrument(const std::string& instrument);
    void setSide(int side);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setOrderId(int orderId);
    void setTransactionTime(std::chrono::system_clock::time_point transactionTime);

    void resetQuantity(int quantity);
    void setStatus(Status status);


    // declare string setters 
    void setSide(const std::string& side);
    void setQuantity(const std::string& quantity);
    void setPrice(const std::string& price);

private:
    std::string clientOrderId;
    std::string instrument;
    int side;        // Assuming 1 for "Buy" and 2 for "Sell"
    int quantity;
    double price;
    int orderId = 0;

    //delare private property called reason which maximum 50 characters and is initialized to empty string
    std::string reason = "";
    Status status = Status::NEW; 

    // transaction time 
    std::chrono::system_clock::time_point transactionTime;

    static int orderCount; // static variable to keep track of number of orders
    int increamentAndGetOrderCount();
};

using OrderPtr = std::shared_ptr<Order>;

#endif  // ORDER_H
