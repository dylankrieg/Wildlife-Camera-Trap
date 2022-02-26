/*
 * 
 * PIR Sensor Output is 3.3V TTL output
 * PIR VCC -> Arduino 5V
 * PIR GND -> Arduino GND
 * PIR OUT -> Arduino D4
 * SET PIR TO RETRIGGERING MODE (H) USING JUMPERS
 * BATTERY VCC -> Arduino VIN
 * BATTERY GND -> Arduino GND
 * TOGGLE SWITCH BETWEEN BATTERY VCC AND ARDUINO VIN
 * CAMERA PLUG -> TERMINAL BLOCK JACK VIA DC2 CABLE
 * TERMINAL BLOCK GND -> DC2 GND
 * TERMINAL BLOCK R -> DC2 FOCUS
 * TERMINAL BLOCK L -> DC2 SHUTTER
 * CHECK CONNECTIVITY BETWEEN TERMINAL BLOCK AND PLUG AND USE SCHEMATIC TO LABEL BLOCKS AS GND,SHUTTER,FOCUS
 * SHUTTER BLOCK-> OPTOISOLATOR OUTPUT
 * FOCUS BLOCK -> OPTOISOLATOR OUTPUT
 * GND BLOCK -> Arduino GND
 * SENSOR MUST ACCLIMATE TO IR ENERGY FOR 30 - 60 SEC ON STARTUP
 * PIR SENSOR IS SET TO RETRIGGERING MODE
 * ARDUINO NANO, BREADBOARD, ENCLOSURE
 * PIR SENSOR DOCUMENTATION: https://lastminuteengineers.com/pir-sensor-arduino-tutorial/
 */


int focusPin=2;
int shutterPin=3;
int pirPin=4;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin,INPUT);
  pinMode(focusPin,OUTPUT);
  pinMode(shutterPin,OUTPUT);
  runCalibration(15000);
}

//delays program for p ms as sensor acclimates to IR energy
void runCalibration(int p) {
  Serial.println("Running Calibration");
  delay(p);
  Serial.println("Calibration Complete");
  delay(20);
}


//runs focus for p ms, then takes a photo and stalls for 20 ms
void takePhoto(int p) {
  digitalWrite(focusPin,HIGH);
  delay(p);
  digitalWrite(shutterPin,HIGH);
  delay(10);
  digitalWrite(focusPin,LOW);
  digitalWrite(focusPin,LOW);
  delay(10);
}

//takes a sequence of n photos spaced apart with 
//delay p seconds
//assumes camera is already in focus
//camera is intially focused and then photos are taken
// 1<4 is guess, not sure what shutter mode and 
//f photos/sec 
void photoSequence(int n,float p) {
  //assume camera is already focused - takePhoto(0)
  for(int i=0;i<n;i++) {
    takePhoto(0);
    delay(int(p*1000));
  }
}

bool motionDetected() {
  if(digitalRead(pirPin)==HIGH) {
    Serial.println("Motion Detected");
    return true;
  }
  Serial.println("No Motion");
  return false;
}

void loop() {
  if(motionDetected()) {
    takePhoto(250);
  }
 
}
