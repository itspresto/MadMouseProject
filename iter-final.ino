#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, PIN, NEO_GRB + NEO_KHZ800);

//global variables
int inPin8 = 8;
int inPin9 = 9;
int inPin10 = 10;

void setup() {
  //sets communication standard
  pinMode(inPin8, INPUT);
  pinMode(inPin9, INPUT);
  pinMode(inPin10, INPUT);
  
  //neopixel initiation
  strip.begin();
  strip.show(); //all pixels to 'off'
}

void loop(){
  //communication variable association
  int pn1;//digitalRead(inPin8);
  int pn2;//digitalRead(inPin9);
  //int turbo_pin = digitalRead(inPin10);
  int state = 0;
  
  pn1 = 0;
  pn2 = 1;
  
  //parse for state determination
  if(pn1 = 0)
  {
    if(pn2 = 0){
      state = 1;}
    if(pn2 = 1){
      state = 2;}
  }
  else if(pn1 = 1)
  {
    if(pn2 = 0){
      state = 3;}
    if(pn2 = 1){
      state = 4;}
  }
  
  //finding turbo pin
  //if(turbo_pin = HIGH)
  //{
    //state = 5;
  //}
  
  //throwing to functions  
  switch(state)
  {
    case 1:
      Disabled(10);
      break;
    case 2:
      Comms_but_disabled(5);
      break;
    case 3:
      //Enabled(10);
      break;
    case 4:
      //Enabled_tricks(5);
      break;
    case 5:
      //Turbo(5);
      break;
  }
  
  
  
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue


//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127,   0,   0), 50); // Red
//  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

void Disabled(uint8_t wait) {
  for(uint16_t i=0; i<60; i++) {
    theaterChase(strip.Color(i, 0, 0), wait);
  }  
}

void Comms_but_disabled(uint8_t wait) {
  for(uint16_t i=0; i<60; i++) {
    theaterChase(strip.Color(i, i, i), wait);
  }  
}

//void Enabled










// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
