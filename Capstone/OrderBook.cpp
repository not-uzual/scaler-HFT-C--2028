#include <iostream>
#include "OrderBook.h"

using namespace std;

void OrderBook::addOrder(Order newOrder) {
    if (newOrder.side == Side::BUY) {
        bids[newOrder.price].push_back(newOrder);
    } else {
        asks[newOrder.price].push_back(newOrder);
    }

    matchOrders();
}

void OrderBook::matchOrders() {
    while (!bids.empty() && !asks.empty()) {
        auto bestBidIt = bids.begin();
        auto bestAskIt = asks.begin();

        Price bestBidPrice = bestBidIt->first;
        Price bestAskPrice = bestAskIt->first;

        if (bestBidPrice < bestAskPrice) {
            break;
        }

        vector<Order>& bidOrders = bestBidIt->second;
        vector<Order>& askOrders = bestAskIt->second;

        Order& bidOrder = bidOrders.front();
        Order& askOrder = askOrders.front();

        Quantity matchedQty = min(bidOrder.qty, askOrder.qty);

        cout << "MATCH: " << matchedQty << " qty | buy order id "
             << bidOrder.id << " with sell order id " << askOrder.id
             << " at price " << askOrder.price << endl;

        bidOrder.qty -= matchedQty;
        askOrder.qty -= matchedQty;

        if (bidOrder.qty == 0) {
            bidOrders.erase(bidOrders.begin());
        }

        if (askOrder.qty == 0) {
            askOrders.erase(askOrders.begin());
        }

        if (bidOrders.empty()) {
            bids.erase(bestBidIt);
        }

        if (askOrders.empty()) {
            asks.erase(bestAskIt);
        }
    }
}

void OrderBook::removeOrder(unsigned int id) {
    for (auto it = bids.begin(); it != bids.end(); it++) {
        vector<Order>& orders = it->second;

        for (auto orderIt = orders.begin(); orderIt != orders.end(); orderIt++) {
            if (orderIt->id == id) {
                orders.erase(orderIt);

                if (orders.empty()) {
                    bids.erase(it);
                }

                cout << "order " << id << " removed from bids" << endl;
                return;
            }
        }
    }

    for (auto it = asks.begin(); it != asks.end(); it++) {
        vector<Order>& orders = it->second;

        for (auto orderIt = orders.begin(); orderIt != orders.end(); orderIt++) {
            if (orderIt->id == id) {
                orders.erase(orderIt);

                if (orders.empty()) {
                    asks.erase(it);
                }

                cout << "order " << id << " removed from asks" << endl;
                return;
            }
        }
    }

    cout << "order " << id << " not found" << endl;
}

map<Price, vector<Order>, greater<Price>> OrderBook::getBids() {
    return bids;
}

map<Price, vector<Order>> OrderBook::getAsks() {
    return asks;
}

BBO OrderBook::getBBO() {
    BBO bbo;
    bbo.topMostBid = bids.empty() ? 0 : bids.begin()->first;
    bbo.topMostAsk = asks.empty() ? 0 : asks.begin()->first;
    return bbo;
}

void OrderBook::printOrderBook() {
    cout << "----- ORDER BOOK -----" << endl;

    cout << "BIDS:" << endl;
    for (auto it = bids.begin(); it != bids.end(); it++) {
        cout << "price " << it->first << " -> ";
        for (Order o : it->second) {
            cout << "[id:" << o.id << " qty:" << o.qty << "] ";
        }
        cout << endl;
    }

    cout << "ASKS:" << endl;
    for (auto it = asks.begin(); it != asks.end(); it++) {
        cout << "price " << it->first << " -> ";
        for (Order o : it->second) {
            cout << "[id:" << o.id << " qty:" << o.qty << "] ";
        }
        cout << endl;
    }

    cout << "-----------------------" << endl;
}

void OrderBook::printBestPrices() {
    BBO bbo = getBBO();
    cout << "best bid: " << bbo.topMostBid << " | best ask: " << bbo.topMostAsk << endl;
}
