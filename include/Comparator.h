#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Order.h"

class Comparator {
public:
    // Comparison function use operator 
    bool operator() (const OrderPtr& lhs, const OrderPtr& rhs) const {
        if (lhs->getSide() == 1 && rhs->getSide() == 1) {  // Buy side
            return lhs->getPrice() < rhs->getPrice();
        } else if (lhs->getSide() == 2 && rhs->getSide() == 2) {  // Sell side
            return lhs->getPrice() > rhs->getPrice();
        } else {
            // Add logic for handling orders on different sides (optional)
            return false;
        }
    }
   
};

#endif // COMPARATOR_H
