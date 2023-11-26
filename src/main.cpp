#include <iostream>
#include "../include/CSVReader.h"
#include "../include/Order.h"

int main() {
    // Example usage
    CSVReader csvReader("/Users/ayesh/workspace/c++ workshop/flower_exchange/data/orders/orders.csv");
    std::vector<Order> orders = csvReader.readCSV();

    // Display the read data
    for (const auto& order : orders) {
        std::cout << "Client Order ID: " << order.getClientOrderId() << "\n";
        std::cout << "Instrument: " << order.getInstrument() << "\n";
        std::cout << "Side: " << order.getSide() << "\n";
        std::cout << "Quantity: " << order.getQuantity() << "\n";
        std::cout << "Price: " << order.getPrice() << "\n";
        std::cout << "Trader ID: " << order.getTraderId() << "\n\n";
    }

    return 0;
}
