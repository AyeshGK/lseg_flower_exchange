#include <iostream>

#include "../../include/Exchanger.h"


Exchanger::Exchanger(OrderBuffer& readerBuffer,OrderBuffer& writerBuffer)
 : readerBuffer(readerBuffer),writerBuffer(writerBuffer) 
{
    // // Read orders from the CSV file and take ownership
    // CSVReader csvReader(csvFilePath);
    // orders = csvReader.readCSV();
}

void Exchanger::performExchange() {

    // Example: Performing the exchange (replace with actual exchange logic)
    // This is where you would implement the order matching and execution logic.
    std::cout << "Orders before exchange:\n";
    // Example: Performing the exchange using the FlowerBookFactory (replace with actual logic)

    std::cout << "orders size: " << readerBuffer.getSize() << "\n";

    int count = 0;
    // for (const auto& order : orders) {
    while(true){
        OrderPtr order = readerBuffer.getOrder();
        if (order==nullptr){
            std::cout << "order is null\n";
            writerBuffer.addOrder(order);// null order added to buffer
            break;
        } 
        count++;

        // rejected object
        if(order->getStatus() == 1){
            writerBuffer.addOrder(order);
            continue;
        }

        // Get or create a flower book for the instrument type
        std::shared_ptr<Book> flowerBook = flowerBookFactory.getFlowerBook(order->getInstrument());
        flowerBook->match(order,writerBuffer);

    }
    std::cout << "orders completed";
    

}
