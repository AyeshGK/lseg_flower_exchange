#ifndef NEWMATCHINGENGINE_H
#define NEWMATCHINGENGINE_H

#include <vector>
#include <queue>

#include "MachineEngineBase.h"
#include "Comparator.h"


class NewMatchingEngine : public MachineEngineBase {
public:
    // Constructor
    NewMatchingEngine();

    // override the match function
    void match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer)  override;


private:
    // Add any private member functions or variables here
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> buyers = std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator>(); // For sell side (ascending)
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> sellers = std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator>(); // For buy side (descending)

    bool isPossibleOrder(int side, int quantity);
    bool isPossiblePrice(int side,const OrderPtr& orderPtr,const OrderPtr& availableOrderPtr);
    void equalQuantityMatch(
        const OrderPtr& orderPtr,
        const OrderPtr& availableOrderPtr,
        int& quantity,
        OrderBuffer& writerBuffer);
    void lessQuantityMatch(    
        const OrderPtr& orderPtr,
        const OrderPtr& availableOrderPtr,
        int& quantity,
        OrderBuffer& writerBuffer);

    void greaterQuantityMatch(   
        const OrderPtr& orderPtr,
        const OrderPtr& availableOrderPtr,
        int& quantity,
        OrderBuffer& writerBuffer);


};

#endif // NEWMATCHINGENGINE_H
