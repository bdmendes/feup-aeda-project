
#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <string>
#include <set>

#include <iostream>

/**
 * The enum with the possible person roles.
 */
enum class PersonRole {
    WORKER,
    CLIENT,
    BOSS
};

/**
 * Struct relative to the login credentials.
 */
struct Credential {
    /**
     * The login username.
     */
    std::string username;

    /**
     * The login password.
     */
    std::string password;

    /**
     * Equality operator.
     *
     * @param c2 the credentials to compare with
     * @return true, if credentials are equal; false, otherwise
     */
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }

    /**
     * Checks if the login credentials are UI reserved keywords
     *
     * @return true, if the login credentials are reserved; false, otherwise
     */
    bool isReserved() const {
        return username == "back" || username == "exit"
        || password == "back" || password == "exit";
    }
};

/**
 * Class relative to a store user.
 */
class Person {
public:
    /**
     * Creates a new Person object.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param credential the login credentials (username and password)
     */
    Person(std::string name, unsigned long taxID, Credential credential, PersonRole role);

    /**
     * Destructs the person object.
     */
    virtual ~Person() = default;

    /**
     * Gets the person name.
     *
     * @return the name
     */
    std::string getName() const;

    /**
     * Gets the person taxpayer identification number.
     *
     * @return the taxpayer identification number
     */
    unsigned long getTaxId() const;

    /**
     * Gets the person login credentials.
     *
     * @return the login credentials
     */
    Credential getCredential() const;

    /**
     * Checks if the person is logged in.
     *
     * @return true, if the person is logged in; false, otherwise
     */
    bool isLogged() const;

    /**
     * Sets the person log status.
     *
     * @param logged the log status (true, if it is logged int; false, otherwise)
     */
    void setLogged(bool logged);

    /**
     * Sets the person name.
     *
     * @param name the name
     */
    void setName(const std::string& name);

    /**
     * Sets the person taxpayer identification number.
     *
     * @param taxID the taxpayer identification number
     */
    void setTaxID(unsigned long taxID);

    /**
     * Sets the person login credentials.
     *
     * @param credential the login credentials
     */
    void setCredential(const Credential& credential);

    /**
     * One person is less than the other according to the comparison of their names by alphabetical order, in case both
     * of their taxpayer identification number are equal to the default one. Otherwise, if one person taxpayer
     * identification number is different from the default, one person is less than the other if their taxpayer
     * identification number is lass than the other's.
     *
     * @param p2 the person to compare with
     * @return true, if person is less than p2; false, otherwise
     * order; false, otherwise.
     */
    bool operator<(const Person& p2) const;

    /**
     * Two persons are equal if their name are equal, in case both of their taxpayer identification number are equal to
     * the default one. Otherwise, if one person taxpayer identification number is different from the default, two
     * persons are equal if their taxpayer identification numbers are equal.
     *
     * @param p2 the person to compare with
     * @return true, if persons are equal; false, otherwise.
     */
    bool operator==(const Person& p2) const;

    /**
     * Gets the default login credentials.
     *
     * @return the default login credentials
     */
    virtual Credential getDefaultCredential() = 0;

    /**
     * Gets the person role.
     *
     * @return the person role
     */
    PersonRole getRole();

    /**
     * The default taxpayer identification number.
     */
    static const unsigned long DEFAULT_TAX_ID;

private:
    /**
     * The person name.
     */
    std::string _name;

    /**
     * The person taxpayer identification number.
     */
    unsigned long _taxID;

    /**
     * The person login credentials.
     */
    Credential _credential;

    /**
     * The person log status.
     */
    bool _logged;

protected:
    /**
     * The person role.
     */
    PersonRole _role;
};

/**
 * Struct to compare two persons pointers.
 */
struct PersonSmaller{
    /**
     * Checks if a person should be shown before another.
     *
     * @param p1 the first person to compare with
     * @param p2 the second person to compare with
     * @return true, if p1 is less than p2, according to defined equality operator
     */
    bool operator()(const Person* p1, const Person* p2) const{
        return *p1 < *p2;
    }
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
