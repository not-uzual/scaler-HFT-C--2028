#include <iostream>
#include "Order.h"
#include "OrderBook.h"

using namespace std;

int main() {
    OrderBook orderBook;

    unsigned int nextId = 1;
    unsigned int timestampNs = 1;

    cout << "Ujjwal wants to BUY 10 qty at price 100" << endl;
    orderBook.addOrder({nextId++, Side::BUY, 100, 10, timestampNs++});
    orderBook.printOrderBook();

    cout << "Shyam wants to SELL 5 qty at price 101" << endl;
    orderBook.addOrder({nextId++, Side::SELL, 101, 5, timestampNs++});
    orderBook.printOrderBook();

    cout << "Ujjwal wants to BUY 5 qty at price 100.5" << endl;
    orderBook.addOrder({nextId++, Side::BUY, 100.5, 5, timestampNs++});
    orderBook.printOrderBook();

    cout << "Paras wants to SELL 10 qty at price 100 (this should match)" << endl;
    orderBook.addOrder({nextId++, Side::SELL, 100, 10, timestampNs++});
    orderBook.printOrderBook();

    orderBook.printBestPrices();

    BBO bbo = orderBook.getBBO();
    cout << "getBBO() -> topMostBid: " << bbo.topMostBid
         << " topMostAsk: " << bbo.topMostAsk << endl;

    cout << "getBids() has " << orderBook.getBids().size() << " price level(s)" << endl;
    cout << "getAsks() has " << orderBook.getAsks().size() << " price level(s)" << endl;

    cout << "removing order id 1" << endl;
    orderBook.removeOrder(1);
    orderBook.printOrderBook();

    return 0;
}
