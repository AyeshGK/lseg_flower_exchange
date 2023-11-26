#include "../../include/CSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

std::vector<Order> CSVReader::readCSV() {
    std::ifstream file(filename);
    std::vector<Order> orders;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return orders;
    }

    std::string line;
    while (std::getline(file, line)) {
        Order order = parseCSVLine(line);
        orders.push_back(order);
    }

    file.close();
    return orders;
}

Order CSVReader::parseCSVLine(const std::string& line) {
    std::stringstream ss(line);
    std::string clientOrderId, instrument, traderId;
    int side, quantity;
    double price;

    // Assuming the CSV format: Client Order ID,Instrument,Side,Quantity,Price,Trader ID
    std::getline(ss, clientOrderId, ',');
    std::getline(ss, instrument, ',');
    ss >> side;  // Assuming Side is an integer
    ss.ignore(); // Ignore the comma
    ss >> quantity >> price;
    ss.ignore(); // Ignore the comma
    std::getline(ss, traderId);

    return Order(clientOrderId, instrument, side, quantity, price, traderId);
}
