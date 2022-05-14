#include "LEDInterface.h"
#include "stdio.h"
#include "stdlib.h"
LEDInterface::LEDInterface(){
    rgb_t off = {0, 0, 0};
    for(int i = 0; i < NUM_LEDS; i++){
        changesArray[i] = new LEDChange(i, off);
        ledsArray[i*3] = 0;
        ledsArray[i*3+1] = 0;
        ledsArray[i*3+2] = 0;
    }
}


void LEDInterface::setRGB(int index, rgb_t rgb){
    rgb.r = ColorUtil::sanitizeH(rgb.r);
    rgb.g = ColorUtil::sanitizeH(rgb.g);
    rgb.b = ColorUtil::sanitizeH(rgb.b);
    changesArray[index]->combine(rgb);
}

void LEDInterface::setHSV(int index, hsv_t hsv){
    hsv.h = ColorUtil::sanitizeH(hsv.h);
    hsv.s = ColorUtil::sanitizeSV(hsv.s);
    hsv.v = ColorUtil::sanitizeSV(hsv.v);
    rgb_t rgb = ColorUtil::hsv2rgb(hsv); 
    changesArray[index]->combine(rgb);
}

void LEDInterface::apply(){
    uint8_t r, g, b;
    rgb_t rgb;
    for (int i = 0; i < NUM_LEDS; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            rgb = change->getRGB();
            r = (uint8_t) (rgb.r*255.0);
            g = (uint8_t) (rgb.g*255.0);
            b = (uint8_t) (rgb.b*255.0);
            ledsArray[3*i] = r;
            ledsArray[3*i+1] = g;
            ledsArray[3*i+2] = b;
            change->count = 0;
        }
    }
}

void LEDInterface::output(){
    ledController->outputLEDs(ledsArray, NUM_LEDS);
}

void LEDInterface::giveController(Controller * ledController){
    this->ledController = ledController;
}