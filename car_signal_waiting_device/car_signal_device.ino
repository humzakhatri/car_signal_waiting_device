#include <avr/interrupt.h>
#include <avr/sleep.h>

/*
Code written by Humza khatri all rights reserved
feel free to edit and share but give credits to the orignal creator, Thanks :)
*/

/*
one button connected to pin 2
one button connected to pin 3
one button connected to pin 4
piezo connected to pin 7
*/

#define b1 2 //three buttons for 10 20 and 30 seconds
#define b2 3
#define b3 4


void setup() {
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
}

long count = 2000;
long prevTime = millis();//for decrementing counter
long prevSiren = millis();//for repeating siren
int sirenBeepCount=0;

void sleepNow(){//this code is available on the arduino website
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(0,wakeUpNow0, LOW);
    attachInterrupt(1,wakeUpNow1, LOW);
    sleep_mode();
    sleep_disable();
    detachInterrupt(0);//for waking up with button 1
    detachInterrupt(1);//for waking up with button 2
    delay(300);
}

void wakeUpNow0(){//reseting the values when it wakes up
  prevTime = millis();
  prevSiren = millis();
  sirenBeepCount=0;
  count = 10000;
}

void wakeUpNow1(){//reseting the values when it wakes up
  prevTime = millis();
  prevSiren = millis();
  sirenBeepCount=0;
  count = 20000;
}


void loop() {		
  //check if a button is pressed and increment the counter respectively	
  if(digitalRead(b1)==LOW){
    tone(7, 550, 50);
    count+=10000;
    delay(200);
  }
  if(digitalRead(b2)==LOW){
    tone(7, 550, 50);
    count+=20000;
    delay(200);
  }
  if(digitalRead(b3)==LOW){
    tone(7, 550, 50);
    count+=30000;
    delay(200);
  }
  //this condition for checking counter timeout so the siren rings
  if(count<0){
    if(millis()-prevSiren>200){
      tone(7, 550, 100);
      prevSiren = millis();
      sirenBeepCount++;
      if(sirenBeepCount>20){//sleep after number of beeps are played
        sirenBeepCount = 0;
        sleepNow();
      }
    }
  } else if(millis()-prevTime>1000){//decrement the counter only if the siren is not ringing
    count-=1000;
    prevTime = millis();
    tone(7, 550, 20);
    delay(10);
  }
  delay(5);
}
