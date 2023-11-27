#include <iostream>

#include "../../include/Exchanger.h"


Exchanger::Exchanger(const std::string& csvFilePath) {
    // Read orders from the CSV file and take ownership
    CSVReader csvReader(csvFilePath);
    orders = csvReader.readCSV();
}

void Exchanger::performExchange() {
    // Example: Displaying the orders (replace with actual exchange logic)
    for (const auto& order : orders) {
        std::cout << "Client Order ID: " << order->getClientOrderId() << "\n";
        std::cout << "Instrument: " << order->getInstrument() << "\n";
        std::cout << "Side: " << order->getSide() << "\n";
        std::cout << "Quantity: " << order->getQuantity() << "\n";
        std::cout << "Price: " << order->getPrice() << "\n";
        std::cout << "Trader ID: " << order->getTraderId() << "\n\n";
    }

    // Example: Performing the exchange (replace with actual exchange logic)
    // This is where you would implement the order matching and execution logic.
    std::cout << "Performing order exchange...\n";
    std::cout << "Orders before exchange:\n";

    // Example: Performing the exchange using the FlowerBookFactory (replace with actual logic)
    for (const auto& order : orders) {
        // Get or create a flower book for the instrument type
        std::shared_ptr<Book> flowerBook = flowerBookFactory.getFlowerBook(order->getInstrument());
        flowerBook->addOrder(order);
    }

    // Display the orders after exchange
    std::cout << "Orders after exchange:\n";
    

}
