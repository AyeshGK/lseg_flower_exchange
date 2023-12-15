#include "../../include/factory/FlowerBookFactory.h"

#include "../../include/model/RoseBook.h"
#include "../../include/model/LotusBook.h"
#include "../../include/model/LavenderBook.h"
#include "../../include/model/TulipBook.h"
#include "../../include/model/OrchidBook.h"

#include "../../include/service/MatchingEngineBase.h"
#include "../../include/service/NewMatchingEngine.h"
#include "../../include/service/OldMatchingEngine.h"


std::shared_ptr<Book> FlowerBookFactory::getFlowerBook(const std::string& instrument) {
    // Check if a flower book for the instrument type already exists
    auto it = flowerBooks.find(instrument);

    // If it doesn't exist, create it
    if (it == flowerBooks.end()) {

        if(instrument == "Rose")
        {   
            flowerBooks[instrument] = std::make_shared<RoseBook>(std::make_shared<NewMatchingEngine>());
        }
        else if(instrument == "Lavender")
        {
            flowerBooks[instrument] = std::make_shared<LavenderBook>(std::make_shared<NewMatchingEngine>());
        }else if(instrument == "Lotus"){
            flowerBooks[instrument] = std::make_shared<LotusBook>(std::make_shared<NewMatchingEngine>());
        }else if(instrument == "Tulip"){
            flowerBooks[instrument] = std::make_shared<TulipBook>(std::make_shared<NewMatchingEngine>());
        }else if(instrument == "Orchid"){
            flowerBooks[instrument] = std::make_shared<OrchidBook>(std::make_shared<NewMatchingEngine>());
        }
    }  
    return flowerBooks[instrument];
}



// std::shared_ptr<Book> FlowerBookFactory::getFlowerBook(const std::string& instrument) {
//     // Check if a flower book for the instrument type already exists
//     auto it = flowerBooks.find(instrument);

//     // If it doesn't exist, create it
//     if (it == flowerBooks.end()) {
//         std::shared_ptr<MatchingEngine> matchingEngine = std::make_shared<NewMatchingEngine>();

//         if (instrument == "Rose") {
//             flowerBooks[instrument] = std::make_shared<RoseBook>(matchingEngine);
//         } else if (instrument == "Lavender") {
//             flowerBooks[instrument] = std::make_shared<LavenderBook>(matchingEngine);
//         } else if (instrument == "Lotus") {
//             flowerBooks[instrument] = std::make_shared<LotusBook>(matchingEngine);
//         } else if (instrument == "Tulip") {
//             flowerBooks[instrument] = std::make_shared<TulipBook>(matchingEngine);
//         } else if (instrument == "Orchid") {
//             flowerBooks[instrument] = std::make_shared<OrchidBook>(matchingEngine);
//         }
//     }

//     return flowerBooks[instrument];
// }

// path : src/factory/FlowerBookFactory.h