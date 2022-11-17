#pragma once

#include <vector>


class Point {

private:
    vector<int> coord;

public:    
    Point(const size_t);
    Point(const size_t, vector<int> );
    ~Point();
    int getCoord(int index);

    bool isEqualTo(Point other);
}