#ifndef FLOWERBOOKFACTORY_H
#define FLOWERBOOKFACTORY_H

#include <map>
#include <string>
#include <memory>
#include "Book.h"

class FlowerBookFactory {
public:
    // Create or retrieve a flower book based on instrument type
    // std::shared_ptr<Book> getFlowerBook(const std::string& instrumentType);
    // std::shared_ptr<Book> FlowerBookFactory::getFlowerBook(const std::string& instrument) ;
        // Create or retrieve a flower book based on instrument type
    std::shared_ptr<Book> getFlowerBook(const std::string& instrument);


private:
    std::map<std::string, std::shared_ptr<Book>> flowerBooks;
    
};

#endif  // FLOWERBOOKFACTORY_H
