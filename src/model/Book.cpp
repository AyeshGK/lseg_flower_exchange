
#include "../../include/Book.h"

#include <iostream>
#include <chrono>      // std::chrono::system_clock


Book::Book(std::shared_ptr<MachineEngineBase> machineEngineBase){
    this->machineEngineBase = machineEngineBase;
}

void Book::orderBook(const OrderPtr& orderPtr,OrderBuffer& writerBuffer){
    machineEngineBase->match(orderPtr,writerBuffer);
}

// Path: src/model/Order.cpp