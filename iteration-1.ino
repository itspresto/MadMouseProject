#include <Adafruit_NeoPixel.h>

#define PIN 5

#define PIN 6

//Setup for LED strips
Adafruit_NeoPixel R = Adafruit_NeoPixel(72, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel L = Adafruit_NeoPixel(72, 6, NEO_GRB + NEO_KHZ800);

//Setup for Analog communications and Lighting Mode
uint16_t LightingMode = 0;
int analogInPin = 8;

void setup() 
{
  //initializes both strips to blank
  R.begin();
  L.begin();
  R.show();
  L.show();
  
  //Initialize analog comms
  pinMode(analogInPin, INPUT);
}

void loop() 
{
  //Get lighting mode from analog pin
  LightingMode = analogRead(analogInPin);
  
  switch(LightingMode){
  case(250):
  {
    //Full turbo
    
    break;
  }
  case(200):
  {
    //half turbo
    
    break;
  }
  case(150):
  {
    //normal enabled
    
    break;
  }
  case(100):
  {
    //disabled with comms
    theaterChase(R.Color(60,   0,   0), 20); // Red
    theaterChase(L.Color(60,   0,   0), 20); // Red        
    break;
  }
  default:
  {
    //disabled
    theaterChase(R.Color(60,   0,   0), 100); // Red
    theaterChase(L.Color(60,   0,   0), 100); // Red    
    break;
  }


/*  
  // Some example procedures showing how to display to the pixels:
  
  colorWipe(R.Color(255, 0, 0), 50); // Red
  colorWipe(L.Color(255, 0, 0), 50); // Red
  colorWipe(R.Color(0, 255, 0), 50); // Green
  colorWipe(L.Color(0, 255, 0), 50); // Green
  colorWipe(R.Color(0, 0, 255), 50); // Blue
  colorWipe(L.Color(0, 0, 255), 50); // Blue
  
  // Send a theater pixel chase in...
  
  theaterChase(R.Color(127, 127, 127), 50); // White
  theaterChase(L.Color(127, 127, 127), 50); // White
  theaterChase(R.Color(127,   0,   0), 50); // Red
  theaterChase(L.Color(127,   0,   0), 50); // Red
  theaterChase(R.Color(  0,   0, 127), 50); // Blue
  theaterChase(L.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
*/  

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<72; i++) 
  {
      R.setPixelColor(i, c);
      L.setPixelColor(i, c);
      R.show();
      L.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<72; i++) 
    {
      R.setPixelColor(i, Wheel((i+j) & 255));
      L.setPixelColor(i, Wheel((i+j) & 255));
    }
    R.show();
    L.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) 
  { // 5 cycles of all colors on wheel
    for(i=0; i<72; i++) 
    {
      R.setPixelColor(i, Wheel(((i * 256 / 72) + j) & 255));
      L.setPixelColor(i, Wheel(((i * 256 / 72) + j) & 255));
    }
    R.show();
    L.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<10; j++) 
  {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i<72; i=i+3) 
      {
        R.setPixelColor(i+q, c);    //turn every third pixel on
        L.setPixelColor(i+q, c);    //turn every third pixel on
      }
      R.show();
      L.show();
     
      delay(wait);
     
      for (int i=0; i<72; i=i+3) 
      {
        R.setPixelColor(i+q, 0);        //turn every third pixel off
        L.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i<72; i=i+3) 
      {
        R.setPixelColor(i+q, Wheel( (i+j) % 255));  
        //turn every third pixel on  
        L.setPixelColor(i+q, Wheel( (i+j) % 255));  
        //turn every third pixel on 
      }
      R.show();
      L.show();
       
      delay(wait);
       
      for (int i=0; i<72; i=i+3) 
      {
        R.setPixelColor(i+q, 0);
        //turn every third pixel off        
        L.setPixelColor(i+q, 0);
        //turn every third pixel off  
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) 
{
  if(WheelPos < 85) 
  {
    return R.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return R.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else 
  {
    WheelPos -= 170;
    return R.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
