#include <iostream>


#include "../../include/Order.h"
 
// Initialize the static member only once
int Order::orderCount = 0;

Order::Order(
    const std::string& clientOrderId, 
    const std::string& instrument, 
    int side, 
    int quantity, 
    double price)
{
    setClientOrderId(clientOrderId);
    setInstrument(instrument);
    setSide(side);
    setQuantity(quantity);
    setPrice(price);
    setOrderId(increamentAndGetOrderCount());
}

Order::Order(
    const std::string &clientOrderId, 
    const std::string &instrument, 
    const std::string &side, 
    const std::string &quantity, 
    const std::string &price)
{
    // Use the setters to apply rules and constraints
    setClientOrderId(clientOrderId);
    setInstrument(instrument);
    setSide(side);
    setQuantity(quantity);
    setPrice(price);
    setOrderId(increamentAndGetOrderCount());

}

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

const std::string& Order::getReason() const {
    return reason;
}

int Order::getStatus() const {
    return status;
}

int Order::getOrderId() const
{
    return orderId;
}

std::chrono::system_clock::time_point Order::getTransactionTime() const
{
    return transactionTime;
}


void Order::setClientOrderId(const std::string& clientOrderId) {
    // std::cout << "clientOrderId: " << clientOrderId << std::endl;
    // Rule: Client Order ID should be an alphanumeric string with a maximum length of 7 characters.
    if (clientOrderId.empty()|| clientOrderId.length() > 7) {
        this->clientOrderId = "Invalid Client Id";
        // std:: cerr << "Error: Invalid Order ID." << std::endl;
        this->reason = "Invalid Order Id";
        this->status = Status::REJECTED;
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
            this->status = Status::REJECTED;
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
        this->status = Status::REJECTED;
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
        this->status = Status::REJECTED;
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
        this->status = Status::REJECTED;
    }
}

void Order::setPrice(double price) {
    this->price = price;
    if(price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
}


void Order::setStatus(Status status)
{
    this->status = status;
}

void Order::setOrderId(int orderId)
{
    this->orderId = orderId;
}

int Order::increamentAndGetOrderCount()
{
    return ++orderCount;
}

void Order::setTransactionTime(std::chrono::system_clock::time_point transactionTime)
{
    this->transactionTime = transactionTime;
}


// Path: src/dao/Order.cpp