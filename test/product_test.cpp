//
// Created by laimi on 22/10/2020.
//

#include <gtest/gtest.h>
#include "model/product/product.h"
#include "model/product/product_manager.h"

#include <algorithm>
#include <iostream>

using testing::Eq;

TEST(Bread, create_bread){
    Bread b1("Pao de cereais", 0.7);

    EXPECT_EQ("Pao de cereais", b1.getName());
    EXPECT_FLOAT_EQ(0.7, b1.getPrice());
    EXPECT_TRUE(b1.isSmall());

    Bread b2("Pao da avo", 0.9, false);

    EXPECT_EQ("Pao da avo", b2.getName());
    EXPECT_FLOAT_EQ( 0.9, b2.getPrice());
    EXPECT_FALSE(b2.isSmall());
}

TEST(Bread, equal_breads){
    Bread b1("Pao de sementes", 0.8);
    Bread b2("Pao de sementes", 0.8);
    Bread b3("Pao de sementes", 0.8, false);
    Bread b4("Pao de sementes", 1);

    EXPECT_TRUE(b1==b2);
    EXPECT_FALSE(b1==b3);
    EXPECT_FALSE(b1==b4);
    EXPECT_FALSE(b2==b3);
    EXPECT_FALSE(b2==b4);
}

TEST(Bread, sort_breads) {
    Bread b1("Pão de alfarroba", 0.6);
    Bread b2("Pão de água", 0.45);
    Bread b3("Pão normal", 0.1);

    EXPECT_TRUE(b1 < b2);
    EXPECT_TRUE(b1 < b3);
    EXPECT_TRUE(b2 < b3);
}

TEST(Cake, create_cake){
    Cake c1("Pao de lo", 17.30);

    EXPECT_EQ("Pao de lo", c1.getName());
    EXPECT_FLOAT_EQ(17.30, c1.getPrice());
    EXPECT_EQ(CakeCategory::GENERAL, c1.getCategory());

    Cake c2("Bolinho fofinho", 22.30, CakeCategory::PIE);

    EXPECT_EQ("Bolinho fofinho", c2.getName());
    EXPECT_FLOAT_EQ(22.30,c2.getPrice());
    EXPECT_EQ(CakeCategory::PIE,c2.getCategory());
}

TEST(Cake, equal_cakes){
    Cake c1("Tarte de bolacha", 13.2);
    Cake c2("Tarte de bolacha", 13.2);
    Cake c3("Tarte de bolacha", 14.5);
    Cake c4("Tarte de bolacha", 13.2, CakeCategory::PIE);

    EXPECT_TRUE(c1==c2);
    EXPECT_FALSE(c1==c3);
    EXPECT_FALSE(c1==c4);
    EXPECT_FALSE(c2==c3);
    EXPECT_FALSE(c2==c4);
}

TEST(Cake, sort_cakes){
    Cake c1("Bolo de amêndoa", 1.2);
    Cake c2("Bolo de arroz", 1);
    Cake c3("Bolo de chocolate", 0.9);

    EXPECT_TRUE(c1 < c2);
    EXPECT_TRUE(c1 < c3);
    EXPECT_TRUE(c2 < c3);
}

TEST(Product, sort_products){
    Bread b1("Pão de alfarroba", 0.6);
    Bread b2("Pão de água", 0.45);

    Cake c1("Bolo de amêndoa", 1.2);
    Cake c2("Bolo de arroz", 1);

    EXPECT_TRUE(c1 < b1);
    EXPECT_TRUE(c1 < b2);
    EXPECT_TRUE(c2 < b1);
    EXPECT_TRUE(c2 < b2);
}

TEST(ProductManager, create_product_manager){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    EXPECT_EQ(stock, pm.getAll());
}

TEST(ProductManager, has_product){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);
    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    ProductManager pm(stock);

    EXPECT_TRUE(pm.has(&meatCake));
    EXPECT_FALSE(pm.has(&hugeBread));
}

TEST(ProductManager, get_product_by_position){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);

    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    unsigned position = 0;
    EXPECT_EQ(&meatCake, pm.get(position));
    EXPECT_EQ(&hugeBread, pm.get(++position));

    EXPECT_THROW(pm.get(++position), InvalidProductPosition);
    try{ pm.get(++position); }
    catch (InvalidProductPosition &e) { std::cout << e.what(); }
}

TEST(ProductManager, add_bread) {
    ProductManager pm;

    EXPECT_EQ(0, pm.getAll().size());

    Bread hugeBread("Pao de sementes", 0.2, false);
    pm.addBread("Pao de sementes", 0.2, false);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Pao de sementes", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(0.2, (*pm.getAll().begin())->getPrice());
}

TEST(ProductManager, add_cake){
    ProductManager pm;

    EXPECT_EQ(0, pm.getAll().size());

    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    pm.addCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Bolo com molho de carne", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(1, (*pm.getAll().begin())->getPrice());
}

TEST(ProductManager, remove_product){
    Cake meatCake("Bolo com molho de carne", 1, CakeCategory::CRUNCHY);
    Bread hugeBread("Pao de sementes",0.2,false);

    std::set<Product*, ProductSmaller> stock;
    stock.insert(&meatCake);
    stock.insert(&hugeBread);
    ProductManager pm(stock);

    EXPECT_EQ(2, pm.getAll().size());

    pm.remove(&hugeBread);

    EXPECT_EQ(1, pm.getAll().size());
    EXPECT_EQ("Bolo com molho de carne", (*pm.getAll().begin())->getName());
    EXPECT_FLOAT_EQ(1, (*pm.getAll().begin())->getPrice());

    pm.remove(&meatCake);

    EXPECT_EQ(0, pm.getAll().size());

    EXPECT_THROW(pm.remove(&meatCake), ProductDoesNotExist);
    try{ pm.remove(&meatCake); }
    catch (ProductDoesNotExist &e) { std::cout << e.what(); }
}
