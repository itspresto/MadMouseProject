#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>


/* I/O Setup */
USBJoystick usb1('0');  // Assign the logitech USBJoystick object to bundle 0

void setup()
{
  /* Initiate comms */
  RobotOpen.begin();
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  
  int LFINAL=0;
  int RFINAL=0;
  
  int LMID=0;
  int RMID=0;
  
  int LEFTS = usb1.makePWM(ANALOG_LEFTY, INVERT) - 127;
  int RITES = usb1.makePWM(ANALOG_RIGHTY, NORMAL) - 127;
 
  int smthL = (LEFTS >= 8 || LEFTS <= -8) ? LEFTS : 0;
  int smthR = (RITES >= 8 || RITES <= -8) ? RITES : 0;
  
  if(((usb1.getBtn(BTN6, NORMAL)) == 1)&&((usb1.getBtn(BTN5, NORMAL))==1))
  {
    LMID = smthL;
    RMID = smthR;
  }
  else if((usb1.getBtn(BTN6, NORMAL)) == 1)
  {
    LMID = smthL*.5;
    RMID = smthR*.5;
  }
  else
  {
    LMID = smthL*.25;
    RMID = smthR*.25;
  }
  
  LFINAL = (LMID >= 8 || LMID <= -8) ? LMID : 0;
  RFINAL = (RMID >= 8 || RMID <= -8) ? RMID : 0;
  
  RobotOpen.setPWM(SIDECAR_PWM1, LFINAL + 130);
  RobotOpen.setPWM(SIDECAR_PWM2, LFINAL + 130);
  RobotOpen.setPWM(SIDECAR_PWM3, RFINAL + 128);
  RobotOpen.setPWM(SIDECAR_PWM4, RFINAL + 128);
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  // PWMs are automatically disabled
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 * You can use either publishAnalog, publishDigital, publishByte, publishShort, or publishLong
 * Specify a bundle ID with a single character (a-z, A-Z, 0-9) - Just make sure not to use the same twice!
 */
void timedtasks() {
  RobotOpen.publishAnalog(ANALOG0, 'A:');   // Bundle A
  RobotOpen.publishDigital(SIDECAR_PWM1, '1');   // Bundle Sidecar 1
  RobotOpen.publishDigital(SIDECAR_PWM2, '2');   // Bundle Sidecar 2
  RobotOpen.publishDigital(SIDECAR_PWM3, '3');   // Bundle Sidecar 3
  RobotOpen.publishDigital(SIDECAR_PWM4, '4');   // Bundle Sidecar 4
  RobotOpen.publishAnalog(ANALOG1, 'B:');   // Bundle B
}


/* This is the main program loop that keeps comms operational
 * There's no need to touch anything here!!!
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
