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
    std::cout << "Orders before exchange:\n";
    // Example: Performing the exchange using the FlowerBookFactory (replace with actual logic)
    int count = 0;

    std::cout << "orders size: " << orders.size() << "\n";

    for (const auto& order : orders) {
        count++; 
        std::cout << "Order " << count << ":\n";
        if(order->getStatus() == 1){
            std::cout <<"Rejected order: \n";
            std::cout << "Client Order ID: " << order->getClientOrderId() << "\n";
            std::cout << "Instrument: " << order->getInstrument() << "\n";
            std::cout << "Side: " << order->getSide() << "\n";
            std::cout << "Quantity: " << order->getQuantity() << "\n";
            std::cout << "Price: " << order->getPrice() << "\n";
            std::cout << "Trader ID: " << order->getTraderId() << "\n\n";

            continue;
        }

        // Get or create a flower book for the instrument type
        std::shared_ptr<Book> flowerBook = flowerBookFactory.getFlowerBook(order->getInstrument());
        std::vector<OrderPtr> execution = flowerBook->match(order);
        if(execution.empty()) {
            // No execution, continue with the next iteration
            continue;
        }

        std::cout << "report working:=================================>\n";
        for(const auto& orderPtr : execution){
            std::cout <<"Executed order: \n";
            std::cout << "Client Order ID: " << orderPtr->getClientOrderId() << "\n";
            std::cout << "Instrument: " << orderPtr->getInstrument() << "\n";
            std::cout << "Side: " << orderPtr->getSide() << "\n";
            std::cout << "Quantity: " << orderPtr->getQuantity() << "\n";
            std::cout << "Price: " << orderPtr->getPrice() << "\n";
            std::cout << "Trader ID: " << orderPtr->getTraderId() << "\n\n";
        }

        std::cout << "Orders after exchange:\n";
        std::cout << "==============="<< std::endl;

    }
    std::cout << "orders completed";
    

}
