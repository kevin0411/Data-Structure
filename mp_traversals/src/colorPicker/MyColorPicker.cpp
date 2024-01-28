#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(int color){
  this->color = color;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned hue;
  if(color==1){
    hue = 270+(x/10)%40; 
  }
  else{
    hue = 190 + (x/10)%20;
  }
  
  HSLAPixel pixel(hue, 1, 0.6);
  return pixel;
}
