#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    img.clear();
    x.clear();
    y.clear();
    base = picture;
    this->max = max;
}
StickerSheet::StickerSheet (const StickerSheet &other){
    img.clear();
    x.clear();
    y.clear();
    this->base = Image(other.base);
    for(int i=0;i<(int)other.img.size();i++){
        img.push_back(other.img[i]);
        x.push_back(other.x[i]);
        y.push_back(other.y[i]);
    }
    this->max = other.max;
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    img = other.img;
    this->x = other.x;
    this->y = other.y;
    base = other.base;
    this->max = other.max;
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned max){
    if(this->max>max){
        if(img.size()>max){
            for(int i=max;i<(int)img.size();i++){
                img[i] = NULL;
            }
        }
        this->img.resize(max);
        this->x.resize(max);
        this->y.resize(max);
    }
    this->max = max;
}
int StickerSheet::addSticker (Image &sticker, int x, int y){
    for(int i=0;i<(int)img.size();i++){
        if(img[i]==NULL){
            img[i] = &sticker;
            this->x[i] = x;
            this->y[i] = y;
            return i;
        }
    }
    img.push_back(&sticker);
    this->x.push_back(x);
    this->y.push_back(y);
    if(img.size()>max){
        max = img.size();
    }
    return img.size()-1;
}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(layer>=img.size() || layer<0)return -1;
    img[layer] = &sticker;
    this->x[layer] = x;
    this->y[layer] = y;
    return layer;
}
bool StickerSheet::translate (unsigned index, int x, int y){
    if(index<0 || index>=img.size() || img[index]==NULL)return false;
    this->x[index] = x;
    this->y[index] = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index){
    if(index<0 || index>=img.size()){

    }
    else{
        img[index] = NULL;
        x[index] = 0;
        y[index] =0;
    }
}
Image * StickerSheet::getSticker (unsigned index){
    if(index<0 || index>=img.size()){
        return NULL;
    }
    return img[index];
}
int StickerSheet::layers () const{
    return max;
}
Image StickerSheet::render () const{
    int right = base.width(), bottom = base.height();
    int left = 0, up = 0;
    for(int i= 0;i<(int)img.size();i++){
        if(img[i]!=NULL){
            int r = x[i]+img[i]->width();
            int b = y[i]+img[i]->height();
            if(r>right)right = r;
            if(b>bottom) bottom= b;
            if(x[i]<left)left = x[i];
            if(y[i]<up)up=y[i];
        }
    }
    int new_w = right-left, new_h = bottom-up;
    Image output = Image();
    output.resize(new_w,new_h);
    for(int w=0;w<(int)base.width();w++){
        for(int h=0;h<(int)base.height();h++){
            output.getPixel(w-left,h-up) = base.getPixel(w,h);
        }
    }
    for(int i= 0;i<(int)img.size();i++){
        if(img[i]!=NULL){
            for(int w = x[i];w<x[i]+(int)img[i]->width();w++){
                for(int h = y[i];h<y[i]+(int)img[i]->height();h++){
                    if(img[i]->getPixel(w-x[i],h-y[i]).a!=0){
                        output.getPixel((unsigned int)(w-left),(unsigned int)(h-up)) = img[i]->getPixel(w-x[i],h-y[i]);
                    }
                }
            }
        }
    }
    return output;
}