#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}

    interval(double _min, double _max) : min(_min), max(_max) {};

    static const interval empty, universe;
};

const static interval empty();
const static interval universe();

#endif