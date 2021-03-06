
#include "client.h"

#include "util/util.h"
#include <numeric>

const char* Client::DEFAULT_USERNAME = "client";
const char* Client::DEFAULT_PASSWORD = "client";

Client::Client(std::string name, unsigned long taxID, bool premium, Credential credential):
        Person(std::move(name), taxID, std::move(credential), PersonRole::CLIENT), _points{0}, _premium(premium), _evaluations(), _numDiscounts(0){
}

bool Client::isPremium() const {
    return _premium;
}

void Client::addDiscount(){
    _numDiscounts++;
}

void Client::removeDiscount(){
    if (_numDiscounts != 0) _numDiscounts--;
}

unsigned Client::getNumDiscounts() const {
    return _numDiscounts;
}

unsigned Client::getPoints() const {
    return _points;
}

void Client::setPremium(bool premium) {
    _premium = premium;
}

void Client::resetPoints() {
    _points = 0;
}

void Client::addPoints(unsigned points) {
    _points += points;
}

void Client::removePoints(unsigned int points) {
    _points -= points;
}

void Client::print(std::ostream &os, bool showData) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == Person::DEFAULT_TAX_ID ? "Not provided" : std::to_string(getTaxId()));
    if (showData){
        os << util::column(isPremium() ? "Premium" : "Basic")
        << util::column(std::to_string(getPoints()) + " points")
        << util::column(getMeanEvaluation() != 0 ? util::to_string(getMeanEvaluation()) + " points": "None yet")
        << util::column(std::to_string(getNumDiscounts()) + " discounts");
    }
    else os << util::column(isLogged() ? "Yes" : "No");
}

Credential Client::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}

void Client::setPoints(unsigned int points) {
    _points = points;
}

void Client::addEvaluation(int evaluation) {
    _evaluations.push_back(evaluation);
}

float Client::getMeanEvaluation() const {
    return _evaluations.empty()? 0 :
    std::accumulate(_evaluations.begin(),_evaluations.end(),0.0f) / _evaluations.size();
}


