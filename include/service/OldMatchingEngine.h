#ifndef OLDMATCHINGENGINE_H
#define OLDMATCHINGENGINE_H

#include <vector>
#include <queue>

#include "MatchingEngineBase.h"
#include "../common/Comparator.h"


class OldMatchingEngine : public MatchingEngineBase {
public:
    // Constructor
    OldMatchingEngine();

    // override the match function
    void match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer)  override;


private:
    // Add any private member functions or variables here
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> buyers = std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator>(); // For sell side (ascending)
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> sellers = std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator>(); // For buy side (descending)


    void sellersMatch(const OrderPtr & orderPtr, OrderBuffer & writerBuffer);
    void buyersMatch(const OrderPtr & orderPtr, OrderBuffer & writerBuffer);

};

#endif // OLDMATCHINGENGINE_H
