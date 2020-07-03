/*
See README.rd of hithubproject to more detais:
https://github.com/maxback/arduino-i2cslave-joystickreader

sketchs of refderence:

https://www.arduino.cc/en/Tutorial/JoyStick
http://www.arduino.cc/en/Tutorial/Debounce
https://dronebotworkshop.com/i2c-arduino-raspberry-pi/
*/
// Include the Wire library for I2C
#include <Wire.h>

typedef struct {
  unsigned int pin;
  unsigned int value;
} Pin;

typedef struct {
  unsigned int pin;
  unsigned int value;
  unsigned int lastValue;
  unsigned int reading;
} DebouncedPin;

typedef struct {
  Pin x;
  Pin y;
  DebouncedPin sw;

} Joystick;

 int ledPin = 13;
 Joystick joy = { 
   {A0, 0}, //x axis
   {A1, 0}, //y axis
   {2, HIGH, HIGH, HIGH}  //sw (z axis button)
 };
 
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
 
 
 void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  
  pinMode(ledPin, OUTPUT);
  pinMode(joy.sw.pin, INPUT);
  
  Serial.begin(9600);
 }


// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print('[');
    Serial.print(c);
    Serial.print(']');
  }
}

 int treatValuePercent(unsigned int data) {
   
   if(data == 0) return 0;
   if(data == 1024) return 100;
   
   float x = data * 1.0;
   x = (x * 100.0) / 1024.0;
  return x;
 }
 

 void loop() {
  // reads the value of the variable resistor
  joy.x.value = analogRead(joy.x.pin);
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);            
  // reads the value of the variable resistor
  joy.y.value = analogRead(joy.y.pin);
  
  // read the state of the switch into a local variable:
  joy.sw.reading = digitalRead(joy.sw.pin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (joy.sw.reading != joy.sw.lastValue) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (joy.sw.reading != joy.sw.value) {
      joy.sw.value = joy.sw.reading;
    }
  }

  digitalWrite(ledPin, joy.sw.value ? HIGH : LOW);
  
  joy.sw.lastValue = joy.sw.reading;

/*
//feedback from x and y value (debounce will dont work fine!
  digitalWrite(ledPin, HIGH);          
  delay(joy.x.value);
  digitalWrite(ledPin, LOW);
  delay(joy.y.value);
*/  
/*
  Serial.print("Test: Espected 0%, 50%, 100%. Obtained:");
  Serial.print(treatValuePercent(0));
  Serial.print("%, ");
  Serial.print(treatValuePercent(512));
  Serial.print("%, ");
  Serial.print(treatValuePercent(1024));
  Serial.println("%.");
*/

  Serial.print("Joystick:{ x: ");
  Serial.print(joy.x.value);
  Serial.print(" (");
  Serial.print(treatValuePercent(joy.x.value));
  Serial.print("%),y: ");
  Serial.print(joy.y.value);
  Serial.print(" (");
  Serial.print(treatValuePercent(joy.y.value));
  Serial.print("%), sw: ");
  Serial.print(joy.sw.value);
  Serial.print(" (reading: ");
  Serial.print(joy.sw.reading);
  Serial.println(") }");
  
 }

