#include "../../include/FlowerBookFactory.h"
#include "../../include/RoseBook.h"  // Include other flower book headers
#include "../../include/LavenderBook.h"

#include <iostream>

std::shared_ptr<Book> FlowerBookFactory::getFlowerBook(const std::string& instrument) {

    // Get the instrument type from the instrument name

    // Check if a flower book for the instrument type already exists
    auto it = flowerBooks.find(instrument);

    // If it doesn't exist, create it
    if (it == flowerBooks.end()) {
        if(instrument == "Rose")
        {
            flowerBooks[instrument] = std::make_shared<RoseBook>();
        }
        else if(instrument == "Lavender")
        {
            flowerBooks[instrument] = std::make_shared<LavenderBook>();
        }
        // else if(instrument == "Tulip")
        // {
        //     flowerBooks[instrument] = std::make_shared<TulipBook>();
        // }
    }  
    return flowerBooks[instrument];
}
