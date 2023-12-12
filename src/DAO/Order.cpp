#include <iostream>


#include "../../include/Order.h"
#include "Order.h"

 
Order::Order(
    const std::string& clientOrderId, 
    const std::string& instrument, 
    int side, 
    int quantity, 
    double price, 
    const std::string& traderId
    )
{
    // Use the setters to apply rules and constraints
    setClientOrderId(clientOrderId);
    setInstrument(instrument);
    setSide(side);
    setQuantity(quantity);
    setPrice(price);
    setTraderId(traderId);
}

Order::Order(
    const std::string &clientOrderId, 
    const std::string &instrument, 
    const std::string &side, 
    const std::string &quantity, 
    const std::string &price, 
    const std::string &traderId)
{
    // Use the setters to apply rules and constraints
    setClientOrderId(clientOrderId);
    setInstrument(instrument);
    setSide(side);
    setQuantity(quantity);
    setPrice(price);
    setTraderId(traderId);

}
// Order::Order()
// {
//     setFinal();
// }

// getters
std::string Order::getClientOrderId() const {
    return clientOrderId;
}

std::string Order::getInstrument() const {
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

const std::string& Order::getReason() const {
    return reason;
}

int Order::getStatus() const {
    return status;
}

// bool Order::getFinal() const
// {
//     return isFinal;
// }

// setters

// std::string clientOrderId;

void Order::setClientOrderId(const std::string& clientOrderId) {
    // std::cout << "clientOrderId: " << clientOrderId << std::endl;
    // Rule: Client Order ID should be an alphanumeric string with a maximum length of 7 characters.
    if (clientOrderId.empty()|| clientOrderId.length() > 7) {
        this->clientOrderId = "INVALID";
        // std:: cerr << "Error: Invalid Order ID." << std::endl;
        this->reason = "Invalid Order ID";
        this->status = 1;
    } else {
        // If all rules are satisfied, set the clientOrderId
        this->clientOrderId = clientOrderId;
    }
}


void Order::setInstrument(const std::string& instrument) {
    // std:: cout << "instrument: " << instrument << std::endl;
    // Rule: Instrument should be one of {Rose, Lavender, Lotus, Tulip, Orchid}
    this->instrument = instrument;
    // Check if the provided instrument is not empty
    if (instrument.empty()) {
        // std::cerr << "Error: Empty Instrument." << std::endl;
        this->reason = "Empty Instrument";
    } else {
        // Convert the provided instrument to lowercase for case-insensitive comparison
        std::string lowercaseInstrument = instrument;
        std::transform(lowercaseInstrument.begin(), lowercaseInstrument.end(), lowercaseInstrument.begin(), ::tolower);

         // List of valid instrument types
        const std::vector<std::string> validInstruments = {"rose", "lavender", "lotus", "tulip", "orchid"};


        // Check if the provided instrument is in the list of valid instruments
        if (std::find(validInstruments.begin(), validInstruments.end(), lowercaseInstrument) == validInstruments.end()) {
            this->reason = "Invalid Instrument";
            this->status = 1;
        }
    }
    // std::cout << "instrument finished" << std::endl;
}

void Order::setSide(const std::string& side) {
    try {
        int sideInt = std::stoi(side);
        setSide(sideInt);
    } catch (const std::exception& e) {
        // std::cerr << "Error: Invalid Side." << std::endl;
        this->reason = "Invalid Side";
        this->status = 1;
    }
}

void Order::setSide(int side) {

    // Rule: Side should be 1 for "Buy" and 2 for "Sell"
    this->side = side;
    if(side != 1 && side != 2) {
        // std::cerr << "Error: Invalid Side." << std::endl;
        throw std::invalid_argument("Invalid Side");
    }
    // std:: cout << "side: " << side << std::endl;
}

void Order::setQuantity(const std::string& quantity) {
    try {
        int quantityInt = std::stoi(quantity);
        setQuantity(quantityInt);
    } catch (const std::exception& e) {
        // std::cerr << "Error: Invalid Quantity." << std::endl;
        this->reason = "Invalid Quantity";
        this->status = 1;
    }
}

void Order::setQuantity(int quantity) {
    // Rule: Quantity should be a min 10 max 1000 shoud be multiple of 10
    this->quantity = quantity;
    if(quantity < 10 || quantity > 1000 || quantity % 10 != 0) {
        // std::cerr << "Error: Invalid Quantity." << std::endl;
        throw std::invalid_argument("Invalid Quantity");
    }
    // std:: cout << "quantity: " << quantity << std::endl;
}

void Order::resetQuantity(int quantity){
    this->quantity = quantity;
}

void Order::setPrice(const std::string& price) {
    try {
        double priceDouble = std::stod(price);
        setPrice(priceDouble);
    } catch (const std::exception& e) {
        // std::cerr << "Error: Invalid Price." << std::endl;
        this->reason = "Invalid Price";
        this->status = 1;
    }
}

void Order::setPrice(double price) {
    // std:: cout << "price: " << price << std::endl;
    // Rule: Price should be a positive double
    this->price = price;
    if(price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
    // std:: cout << "price: " << price << std::endl;
}

void Order::setTraderId(const std::string& traderId) {
    this->traderId = traderId;
}

void Order::setStatus(int status)
{
    this->status = status;
}

// Implementation of the greater-than operator (for descending order)
// bool Order::operator>(const Order& rhs) const {
//     // For the buy side, higher price is more attractive
//     std::cout << "> side" << std::endl;
//     std::cout << "current price :"<<getPrice()<<" , rsh price: "<<rhs.getPrice()<< std::endl;
//     return rhs.getPrice() > getPrice() ;
// }

// // Implementation of the less-than operator (for ascending order)
// bool Order::operator<(const Order& rhs) const {
//     // For the sell side, lower price is more attractive
//     std::cout << "< side" << std::endl;
//     return rhs.getPrice() < getPrice();
// }


// void Order::setFinal()
// {
//     this->isFinal = true;
// }

// Path: src/DAO/Order.h