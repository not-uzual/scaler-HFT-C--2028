#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <vector>
#include "Order.h"

using namespace std;

struct BBO {
    Price topMostBid;
    Price topMostAsk;
};

class OrderBook {
private:
    map<Price, vector<Order>, greater<Price>> bids;
    map<Price, vector<Order>> asks;

    void matchOrders();

public:
    void addOrder(Order newOrder);
    void removeOrder(unsigned int id);

    map<Price, vector<Order>, greater<Price>> getBids();
    map<Price, vector<Order>> getAsks();
    BBO getBBO();

    void printOrderBook();
    void printBestPrices();
};

#endif
