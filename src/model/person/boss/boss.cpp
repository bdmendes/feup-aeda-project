
#include "boss.h"

#include "exception/file_exception.h"

const char* Boss::DEFAULT_USERNAME = "boss";
const char* Boss::DEFAULT_PASSWORD = "boss";

Boss::Boss(std::string name, unsigned long taxID, Credential credential) :
    Person(std::move(name), taxID, std::move(credential), PersonRole::BOSS) {
}

Credential Boss::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}

void Boss::read(const std::string &path) {
    std::ifstream file(path);
    if(!file) throw FileNotFound(path);

    std::string name, username, password;
    unsigned long taxID = Person::DEFAULT_TAX_ID;
    file >> name >> taxID >> username >> password;
    util::stripCarriageReturn(password);
    std::replace(name.begin(),name.end(),'-',' ');
    setName(name);
    setTaxID(taxID);
    setCredential({username,password});
}

void Boss::write(const std::string &path) {
    std::ofstream file(path);
    if(!file) throw FileNotFound(path);

    std::string styledName = getName();
    std::replace(styledName.begin(),styledName.end(),' ','-');
    file << styledName << " " << getTaxId() << " " << getCredential().username
    << " " << getCredential().password;
}
