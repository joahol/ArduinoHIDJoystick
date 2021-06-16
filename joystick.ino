
#include <Mouse.h>
#include <HID.h>
const int xAxis =A0;
const int yAxis =A1;
const int switchPin =2;
const int mouseButton =3;
const int ledPin = 5;

int range=12;
int responseDelay =5;
int threshold = range /4;
int center = range/2;

boolean mouseIsActive=false;
int lastSwitchState  = LOW;
void setup(){
    pinMode(switchPin, INPUT);
    pinMode(ledPin,OUTPUT);
  }

 void loop(){
  int switchState = digitalRead(switchPin);
  if(switchState==HIGH){
  Mouse.begin();
  }
  if(switchState != lastSwitchState){
    if(switchState == HIGH){
      mouseIsActive=true;
      digitalWrite(ledPin, mouseIsActive);
      Mouse.begin();
      }
      else{
        mouseIsActive=false;
        }
      }
      lastSwitchState = switchState;
      int xRead = readAxis(A0);
      int yRead = readAxis(A1);
      if(mouseIsActive){
        Mouse.move(xRead, yRead, 0);
        }
        if(digitalRead(mouseButton)==HIGH){
          if(!Mouse.isPressed(MOUSE_LEFT)){
              Mouse.press(MOUSE_LEFT);
            }
          }
          else{
            if(Mouse.isPressed(MOUSE_LEFT)){
                Mouse.release(MOUSE_LEFT);
              }
            }
            delay(responseDelay);
  }
int readAxis(int thisAxis){
  int reading = analogRead(thisAxis);
  reading = map(reading, 0, 1023,0, range);
  int distance = reading - center;
  if(abs(distance < threshold)){
    distance =0;
    }
    return distance;
  }
