#ifndef ORDER_H
#define ORDER_H

using Price = double;
using Quantity = int;

enum class Side {
    BUY,
    SELL
};

struct Order {
    unsigned int id;
    Side side;
    Price price;
    Quantity qty;
    unsigned int timestampNs;
};

#endif
