
#ifndef SRC_ORDER_H
#define SRC_ORDER_H

#include "exception/product_exception.h"
#include "exception/order_exception.h"

#include "model/person/person.h"
#include "model/product/product.h"
#include "model/product/product_manager.h"
#include "model/date/date.h"

#include <fstream>
#include <map>

/**
 * Class relative to a store order.
 */
class Order {
public:
    /**
     * Creates a new Order object.
     *
     * @param client the client
     * @param worker the worker
     * @param location the store location; defaults to Head Office
     * @param date the request date; defaults to the current date
     */
    Order(Client& client, Worker& worker, std::string location = DEFAULT_LOCATION, Date date = {});

    /**
     * Checks if the order has discount.
     *
     * @return true, if the client has 100 points and the subscription type is premium (there is a discount of 5%) or
     * if the client has 200 points and the subscription type is basic (there is a discount of 2%); false, otherwise
     */
    bool hasDiscount() const;

    /**
     * Checks if there is a certain product on the products list.
     *
     * @param product the product
     * @return true, if there is the product on the products list; false, otherwise
     */
    bool hasProduct(Product* product);

    /**
     * Checks if the order was delivered.
     *
     * @return true, if it was already delivered; false, otherwise
     */
    bool wasDelivered() const;

    /**
     * Gets the order worker.
     *
     * @return the worker
     */
    Worker* getWorker() const;

    /**
     * Gets the order client.
     *
     * @return the client
     */
    Client* getClient() const;

    /**
     * Gets the store location where the order will be delivered.
     *
     * @return the store location
     */
    std::string getDeliverLocation() const;

    /**
     * Gets the list of all products with the respective requested quantity.
     *
     * @return map of included products to their quantities
     */
    std::map<Product*, unsigned int, ProductSmaller> getProducts() const;

    /**
     * Gets the evaluation of the order, given by the client when the order is delivered.
     *
     * @return the client evaluation
     */
    int getClientEvaluation() const;

    /**
     * Gets the order final price (with the discount in case the client has it).
     *
     * @return the final price
     */
    float getFinalPrice() const;

    /**
     * Gets the order total price (without any discount).
     */
    float getTotal() const;

    /**
     * Gets the date when the order was requested.
     *
     * @return the order request date
     */
    Date getRequestDate() const;

    /**
     * Gets the date when the order was delivered.
     *
     * @return the order delivery date
     */
    Date getDeliverDate() const;

    /**
     * Two orders are equal if they share the same client, worker, delivery location and request date.
     *
     * @param rhs the order to compare with
     * @return true, if the orders are equal; false, otherwise
     */
    bool operator==(const Order& rhs) const;

    /**
     * One order loses priority over another if it has already been delivered, if the client feedback
     * is higher, or the client has benefited from more discounts.
     *
     * @param rhs the order to compare with
     * @return whether the order has lessy priority than rhs
     */
    bool operator<(const Order& rhs) const;

    /**
     * Prints all the order data: client name, request date, worker name, deliver date (if it was already delivered),
     * all the products description - category (if it is cake or bread), price per unit and requested quantity - and
     * whether there is a discount or not. If there aren't any requested products, it prints "No products added".
     *
     * @param os the output stream
     */
    void print(std::ostream& os) const;

    /**
     * The default store location.
     */
    static const char* DEFAULT_LOCATION;

    friend class OrderManager;

private:

    /**
    * Sets the store location where the order will be delivered.
    * A new worker (possibly working at the new desired location) will be assigned.
    *
    * @param location the store location
    */
    void setDeliverLocation(const std::string& location, Worker* newWorker);

    /**
    * Delivers the order and gets the client evaluation and deliver duration.
    *
    * @param clientEvaluation the client evaluation
    * @param updatePoints whether to add points to the client
    * @param deliverDuration the deliver duration
    */
    void deliver(int clientEvaluation, bool updatePoints = true, int deliverDuration = 30);

    /**
    * Adds a product with a certain quantity to the products list.
     *
    * @param product the product
    * @param quantity the quantity
    * @return the product added to the products list
    */
    Product* addProduct(Product* product, unsigned quantity = 1);

    /**
     * Removes a certain product from the products list.
     *
     * @param product the product
     */
    void removeProduct(Product* product);

    /**
     * Removes a certain product, at a certain position, from the products list.
     *
     * @param position the position
     */
    void removeProduct(unsigned long position);

    /**
    * Updates total price whenever is added products to the order.
    */
    void updateTotalPrice();

    /**
     * The products list with its relative available quantity.
     */
    std::map<Product*, unsigned int, ProductSmaller> _products;

    /**
     * The order total price (without any discount).
     */
    float _totalPrice;

    /**
     * The client who requested the order.
     */
    Client* _client;

    /**
     * The worker who is going to deliver the order.
     */
    Worker* _worker;

    /**
     * The order evaluation given by the client whe delivered.
     */
    int _clientEvaluation;

    /**
     * The order delivery status: true, if the order was already delivered; false, otherwise.
     */
    bool _delivered;

    /**
     * The order request date.
     */
    Date _requestDate;

    /**
     * The order deliver date.
     */
    Date _deliverDate;

    /**
     * The store location to deliver the order.
     */
    std::string _deliverLocation;
};

#endif //SRC_ORDER_H
