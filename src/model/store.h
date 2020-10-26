//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_STORE_H
#define SRC_STORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "person.h"
#include "order.h"
#include <exception/person_exception.h>
#include <exception/store_exception.h>

#include "product.h"

class Person;
class Client;
class Worker;

class Boss;
class ClientDoesNotExist;
class WorkerDoesNotExist;
class StoreHasNoWorkers;
class Order;

class Store {
public:
    Store(std::string name);
    std::string getName() const;
    float getMeanEvaluation() const;
    std::vector<Order> getClientHistory(const Client* client);
    std::vector<Order> getWorkerHistory(const Worker* worker);
    int searchWorkerByName(std::string name);
    int searchWorkerByTributaryNumber(int tributaryNumber);
    int findWorker(const Worker* worker);
    void hireWorker(Worker* worker);
    void fireWorker(const Worker* worker);
    void addOrder(const std::map<Product, unsigned>& _products, Client& client);
    Worker* getAvailableWorker();
    void changeWorkerSalary(Worker *worker, float salary);

    bool operator== (const std::string& name){
        return getName() == name;
    }
private:
    const std::string _name;
    std::vector<const Client*> _clients;
    std::vector<Worker*> _workers; //Workers are not const because the number of orders is going to change
    std::vector<Order> _orders;
    std::vector<float> _clientEvaluations;
};

#endif //SRC_STORE_H