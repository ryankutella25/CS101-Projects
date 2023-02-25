#ifndef _point_h
#define _point_h

#include <iostream>
using namespace std;

class Point{
    public: 
        int x;
        int y;
        Point(){
            x=5;
            y=1;
        }
        Point(int xVal, int yVal){
            x=xVal;
            y=yVal;
        }
        int getX(){
            return x;
        }
};

#endif