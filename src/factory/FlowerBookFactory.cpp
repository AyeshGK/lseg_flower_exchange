#include <iostream>


#include "../../include/FlowerBookFactory.h"
#include "../../include/RoseBook.h"  // Include other flower book headers
#include "../../include/LavenderBook.h"
#include "../../include/MachineEngineBase.h"
#include "../../include/NewMatchingEngine.h"
#include "../../include/OldMatchingEngine.h"


std::shared_ptr<Book> FlowerBookFactory::getFlowerBook(const std::string& instrument) {
    // Check if a flower book for the instrument type already exists
    auto it = flowerBooks.find(instrument);

    // If it doesn't exist, create it
    if (it == flowerBooks.end()) {

        if(instrument == "Rose")
        {   
            flowerBooks[instrument] = std::make_shared<RoseBook>(std::make_shared<OldMatchingEngine>());
        }
        else if(instrument == "Lavender")
        {
            flowerBooks[instrument] = std::make_shared<LavenderBook>(std::make_shared<OldMatchingEngine>());
        }
    }  
    return flowerBooks[instrument];
}
