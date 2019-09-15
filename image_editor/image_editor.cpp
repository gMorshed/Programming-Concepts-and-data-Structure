/*
        image_editor.cpp
        
        Method implementations for the image_editor class.

        author: C. Painter-Wakefield

        last modified: 1/15/2018
*/

#include <utility>
#include "image_editor.h"
#include "pixel.h"

using namespace std;

bool image_editor::load(istream& in) {
    imageData.clear();
    // test magic string
    string magic;
    in >> magic;
    if (magic != "P3") {
        return false;
    }
    else {
    // TODO: get columns, rows, ensure valid
    in>>columns;
    in>>rows;
    if( columns< 0 || rows < 0) {
        return false;
    }
    // TODO: get and discard color depth
    int c; 
    in>>c;//read in the color depth
    // TODO: initialize your image storage data structure
    // TODO: get image data from input stream into your data structure
    for(int i=0; i<rows; i++) {
        vector<Pixel>row; //a vector for the rows containing the pixels
        for(int j=0; j<columns; j++) {
            int r,g,b;
            in>>r>>g>>b; //reading in the pixels
            Pixel pixel(r,g,b);
            row.push_back(pixel);//getting the pixels in the rows
            }
        imageData.push_back(row); //getting the rows in the data
        
        }
    }
    return true;
}

void image_editor::save(ostream& out) {
    // TODO: output valid PPM file format data to the
    // output stream out
    out<<"P3"<<endl;
    out<<columns<<" "<<rows<<endl;
    out<<"255"<<endl;
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            out<<imageData[i][j].red<<" "<<imageData[i][j].green<<" "<<imageData[i][j].blue<<"  "; //writing out the pixel values 
        }
        out<<endl;
    }
}

int image_editor::get_rows() {
    // TODO: return the correct # of rows
    return rows;
}

int image_editor::get_columns() {
    // TODO: return the correct # of columns
    return columns;
}

int image_editor::get_red(int row, int col) {
    // TODO: return the actual pixel red value
    return imageData[row][col].red;
}

int image_editor::get_green(int row, int col) {
    // TODO: return the actual pixel green value
    return imageData[row][col].green;
}

int image_editor::get_blue(int row, int col) {
    // TODO: return the actual pixel blue value
    return imageData[row][col].blue;
}

void image_editor::apply_effect(int action_index) {
    enum action a = (enum action)action_index;

    // TODO: fill out this method
    if (a == GRAYSCALE) {
        // call a method that applies the grayscale
        // effect to the image in your data structure
        grayScale();
    }
    //appropiate methods call for all the effects 
    else if (a == NEGATE_RED) {
        negativeRed();
    }
    else if( a == NEGATE_GREEN) {
        negativeGreen();
    }
    else if ( a== NEGATE_BLUE) {
        negativeBlue();
    }
    else if( a == FLIP_HORIZONTAL) {
        flipHorizon();
    }
    else if(a == FLIP_VERTICAL) {
        verticalFlip();
    }
    else if ( a== FLATTEN_RED) {
        flattenRed();
    }
    else if(a== FLATTEN_GREEN) {
        flattenGreen();
    }
    else if(a == FLATTEN_BLUE) {
        flattenBlue();
    }
    else if( a== EXTREME_CONTRAST) {
        extremeCon();
    }
}

// TODO: add effect methods below here
void image_editor::grayScale() { 
    for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            int temp = (imageData[i][j].red + imageData[i][j].green + imageData[i][j].blue) /3; //averaging all the values of a pixel and set it to all the values of the pixel
            imageData[i][j].red = temp;
            imageData[i][j].green = temp;
            imageData[i][j].blue = temp;
        }
    }
}
void image_editor::negativeRed() {
    for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].red = 255- imageData[i][j].red; // as instructed getting the negative red values by subtracting from the color depth max 
            //which for this assignment has been told 255
        }
    }
}

void image_editor::negativeGreen() {
    for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].green = 255- imageData[i][j].green;
        }
    }
}

void image_editor::negativeBlue() {
    for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].blue = 255- imageData[i][j].blue;
        }
    }
}
void image_editor::flipHorizon() {
    Pixel temp;
    for(int i=0; i<rows; i++) {
        for (int j=0; j<columns/2; j++) { //need to go only half way through the columns for the horizontal flip, because going half way through the columns swappes all the columns
            //swapping the pixels of the image, just like a variable swap
            temp = imageData[i][j];
            imageData[i][j] = imageData[i][columns-1-j]; //-1 because index start from 0
            imageData[i][columns-1-j] = temp;
        }
    }
}
void image_editor::verticalFlip() {
    Pixel temp;
    for(int i=0; i<rows/2; i++) { //just like horizon flip, but for rows as it is verticle flip
        for (int j=0; j<columns; j++) {
            temp = imageData[i][j];
            imageData[i][j] = imageData[rows-1-i][j]; // index start from 0, thats why -1
            imageData[rows-1-i][j] = temp;
        }
    }
}
void image_editor::flattenRed() {
     for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].red =0; //assigning all the red values to 0
        }
     }
 }
 
void image_editor::flattenGreen() {
     for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].green =0; //assigning all the green values to 0
        }
     }
 }
 
void image_editor::flattenBlue() {
     for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            imageData[i][j].blue =0; //assigning all the blue values to 0
        }
     }
 }
  void image_editor::extremeCon() {
      int midPoint = 255/2;
      for(int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            //if the pixel value for the color more than the midpoint of the color depth, reassign color depth to max color depth, otherwise to 0, for all the color
            if(imageData[i][j].red > midPoint) {
                imageData[i][j].red = 255;
            }
            else {
                imageData[i][j].red =0;
            }
            if(imageData[i][j].green > midPoint) {
                imageData[i][j].green = 255;
            }
            else {
                imageData[i][j].green =0;
            }
            if(imageData[i][j].blue > midPoint) {
                imageData[i][j].blue = 255;
            }
            else {
                imageData[i][j].blue =0;
            }
        }
    }
  }