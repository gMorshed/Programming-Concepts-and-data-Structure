/*File Name: pixel.cpp
Author: Gazi Morshed
 Course and Assignment: CSCI 262 (project 1 image editor)
Description: implimentation of pixel class
*/



#include "pixel.h"
using namespace std;

Pixel:: Pixel(int r, int g, int b ) { //parameterized constructor
    red =r;
    green = g;
    blue = b;
}
Pixel::Pixel() { //default constructor
    red =0;
    green=0;
    blue = 0;
}