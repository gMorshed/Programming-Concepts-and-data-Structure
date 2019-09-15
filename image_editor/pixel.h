/*File Name: pixel.h
Author: Gazi Morshed
 Course and Assignment: CSCI 262 (project 1 image editor)
Description: declaring a pixel class which will help dealing with the pixels.
*/



#pragma once

class Pixel {
  public:
    int red;
    int green;
    int blue;
    Pixel(int,int,int);
    Pixel();
};