#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>

/* I/O Setup */
USBJoystick usb1('0');  // Assign the logitech USBJoystick object to bundle 0

/* Global Variables */
uint16_t LightingMode = 0;
const int analogPinOut = 8;
const int analogJoyOut1 = 9;
const int analogJoyOut2 = 10;
int JoyY = 0;
int JoyX = 0;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin();
  
  /* Initiate lighting comms */
  pinMode(analogPinOut, OUTPUT);
  pinMode(analogJoyOut1, OUTPUT);
  pinMode(analogJoyOut2, OUTPUT);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  
  /* Lighting exception */ 
  if(usb1.getBtn(BTN1000000, NORMAL)) == 1) //find and change btn to A button!!!!
  {
    int left-y-to-send = usb1.makePWM(ANALOG_LEFTY, NORMAL);
    int left-x-to-send = usb1.makePWM(ANALOG_LEFTX, NORMAL);
    
    JoyY = left-y-to-send;
    JoyX = left-x-to-send;
    
    analogWrite(analogJoyOut1, JoyY);
    analogWrite(analogJoyOut2, JoyX);
  }
  
  else{
  /* Variable Library */
  int LFINAL=0;
  int RFINAL=0;
  int LMID=0;
  int RMID=0;
  
  // Initial reading of Joysticks
  int LEFTS = usb1.makePWM(ANALOG_LEFTY, INVERT) - 127;
  int RITES = usb1.makePWM(ANALOG_RIGHTY, NORMAL) - 127;
 
  // Ternarys disregard slight bumps or deadzone interference
  int smthL = (LEFTS >= 8 || LEFTS <= -8) ? LEFTS : 0;
  int smthR = (RITES >= 8 || RITES <= -8) ? RITES : 0;
  
  // Turbo Button Logic
  // Checks for button presses
  // Case for both buttons  
  if(((usb1.getBtn(BTN6, NORMAL)) == 1)&&((usb1.getBtn(BTN5, NORMAL))==1))
  {
    // Sets full values for maximum possible power
    LMID = smthL;
    RMID = smthR;
    LightingMode = 250;
  }
  
  // Case for right button
  else if((usb1.getBtn(BTN6, NORMAL)) == 1)
  {
    // Sets values for midspeed power
    LMID = smthL*.7;
    RMID = smthR*.7;
    LightingMode = 200;
  }
  else
  {
    // Sets values for Low power slower movement
    LMID = smthL*.35;
    RMID = smthR*.35;
    LightingMode = 150;
  }
  
  // Secondary smoothing for redundancy reasons
  LFINAL = (LMID >= 8 || LMID <= -8) ? LMID : 0;
  RFINAL = (RMID >= 8 || RMID <= -8) ? RMID : 0;
  
  // Pushing final values to sidecar PWM Digital IOs
  RobotOpen.setPWM(SIDECAR_PWM1, LFINAL + 130);
  RobotOpen.setPWM(SIDECAR_PWM2, LFINAL + 130);
  RobotOpen.setPWM(SIDECAR_PWM3, RFINAL + 128);
  RobotOpen.setPWM(SIDECAR_PWM4, RFINAL + 128);
  }
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  // PWMs are automatically disabled
  
  /*Set Lighting*/
  LightingMode = 100;
}

/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 * You can use either publishAnalog, publishDigital, publishByte, publishShort, or publishLong
 * Specify a bundle ID with a single character (a-z, A-Z, 0-9) - Just make sure not to use the same twice!
 */
void timedtasks() {
  
  //Publish DS Information
  RobotOpen.publishAnalog(ANALOG0, 'A:');        // Bundle A
  RobotOpen.publishDigital(SIDECAR_PWM1, '1');   // Bundle Sidecar 1
  RobotOpen.publishDigital(SIDECAR_PWM2, '2');   // Bundle Sidecar 2
  RobotOpen.publishDigital(SIDECAR_PWM3, '3');   // Bundle Sidecar 3
  RobotOpen.publishDigital(SIDECAR_PWM4, '4');   // Bundle Sidecar 4
  RobotOpen.publishAnalog(analogPinOut, 'L');    // LighingMode being sent by Driver arduino
  
  
  if(usb1.getBtn(BTN1000000, INVERT)) == 1) //find and change btn to A button!!!!
  {
    /*Write Lighting Mode*/
    analogWrite(analogPinOut, LightingMode);
  }
}


/* This is the main program loop that keeps comms operational
 * DO NOT TOUCH UNDER ANY CIRCUMSTANCES
 */
void loop() {
  RobotOpen.pollDS();
  if (RobotOpen.enabled())
    enabled();
  else
    disabled();
  timedtasks();
  RobotOpen.outgoingDS();
}
