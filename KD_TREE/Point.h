#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Point {

private:
    vector<int> coord;

public:
    Point(const size_t);
    Point(const size_t, vector<int>);
    ~Point();
    int getCoord(int index);

    bool isEqualTo(Point other);
};