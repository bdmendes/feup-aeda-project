//
// Created by up201906166 on 23/10/2020.
//

#include "person_exception.h"

PersonDoesNotExist::PersonDoesNotExist(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", does not exist!"){
}

PersonDoesNotExist::PersonDoesNotExist(const std::string& name):
    std::logic_error(name + " does not exist!\n"){
}

PersonDoesNotExist::PersonDoesNotExist(int taxID) :
    std::logic_error("Person with number " + std::to_string(taxID) + " does not exist!"){
}

InvalidPersonPosition::InvalidPersonPosition(unsigned int position, unsigned long size) :
    std::invalid_argument(std::to_string(++position) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){
}

InvalidCredential::InvalidCredential(const std::string &arg) :
    invalid_argument("You cannot use '" + arg + "' in your credential since it's a reserved word!") {
}
