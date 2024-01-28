#include "Image.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

Image::Image(){
    PNG();
}
Image::Image(unsigned int w, unsigned int h){
    PNG(w,h);
}
void Image::lighten(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.l += 0.1;
                if(currOutPixel.l>1){
                    currOutPixel.l=1;
                }
        }
    }
}
void Image::lighten(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.l += amount;
                if(currOutPixel.l>1){
                    currOutPixel.l=1;
                }
        }
    }
}
void Image::darken(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.l -= 0.1;
                if(currOutPixel.l<0){
                    currOutPixel.l=0;
                }
        }
    }
}
void Image::darken(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.l -= amount;
                if(currOutPixel.l<0){
                    currOutPixel.l=0;
                }
        }
    }
}
void Image::saturate(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.s += 0.1;
                if(currOutPixel.s>1){
                    currOutPixel.s=1;
                }
        }
    }
}
void Image::saturate(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.s += amount;
                if(currOutPixel.s>1){
                    currOutPixel.s=1;
                }
        }
    }
}
void Image::desaturate(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.s -= 0.1;
                if(currOutPixel.s<0){
                    currOutPixel.s=0;
                }
        }
    }
}
void Image::desaturate(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.s -= amount;
                if(currOutPixel.s<0){
                    currOutPixel.s=0;
                }
        }
    }
}
void Image::grayscale(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel & currOutPixel = getPixel(x, y);
                currOutPixel.s =0;
        }
    }
}
void Image::rotateColor(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                currOutPixel.h += amount;
                while(currOutPixel.h<0){
                    currOutPixel.h+=360;
                }
                while(currOutPixel.h >=360){
                    currOutPixel.h -=360;
                }
        }
    }
}
void Image::illinify(){
    double diff = (11+216)/2.0;
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                if(currOutPixel.h >diff && currOutPixel.h < (diff+180)){
                    currOutPixel.h = 216;
                }
                else{
                    currOutPixel.h = 11;
                }
        }
    }
}
void Image::scale(double amount){
    PNG p = PNG(width()*amount, height()*amount);
    for(unsigned x = 0; x<width()*amount;x++){
        for(unsigned y=0;y<height()*amount;y++){
            HSLAPixel& currOutPixel = getPixel(x/amount, y/amount);
            HSLAPixel& output = p.getPixel(x, y);
            output = currOutPixel;
        }
    }
    resize(width()*amount, height()*amount);
    for(unsigned x = 0; x<width();x++){
        for(unsigned y=0;y<height();y++){
            HSLAPixel& currOutPixel = getPixel(x, y);
            HSLAPixel& output = p.getPixel(x, y);
            currOutPixel = output;
        }
    }
}
void Image::scale(unsigned w,unsigned h){
        double w_portion = (double)w/width();
        double h_portion = (double)h/height();
        double amount;
        if(w_portion>h_portion){
            amount = h_portion;
        }
        else{
            amount = w_portion;
        }
        PNG p = PNG(width()*amount, height()*amount);
        for(unsigned x = 0; x<width()*amount;x++){
            for(unsigned y=0;y<height()*amount;y++){
                HSLAPixel& currOutPixel = getPixel(x/amount, y/amount);
                HSLAPixel& output = p.getPixel(x, y);
                output = currOutPixel;
            }
        }
        resize(width()*amount, height()*amount);
        for(unsigned x = 0; x<width();x++){
            for(unsigned y=0;y<height();y++){
                HSLAPixel& currOutPixel = getPixel(x, y);
                HSLAPixel& output = p.getPixel(x, y);
                currOutPixel = output;
            }
        }
}