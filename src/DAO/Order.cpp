#include "../../include/Order.h"

Order::Order(
    const std::string& clientOrderId, 
    const std::string& instrument, 
    int side, int quantity, 
    double price, 
    const std::string& traderId
    )
    : 
    clientOrderId(clientOrderId), 
    instrument(instrument), 
    side(side), 
    quantity(quantity),
    price(price), 
    traderId(traderId) 
{
    // Constructor implementation, if needed
}

// getters
const std::string& Order::getClientOrderId() const {
    return clientOrderId;
}

const std::string& Order::getInstrument() const {
    return instrument;
}

int Order::getSide() const {
    return side;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getPrice() const {
    return price;
}

const std::string& Order::getTraderId() const {
    return traderId;
}

// Path: src/DAO/Order.h