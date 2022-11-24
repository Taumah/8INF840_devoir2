#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Point {

public:
    vector<int>* coord;
    Point(const size_t);
    Point(vector<int> *);
    Point(int* vals,int);
    ~Point();
    int getCoord(int index);
    friend ostream& operator<<(ostream& os, const Point *p);
    bool isEqualTo(Point* other);
};