#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

int speedPin=5;
int dir1=4;
int dir2=3;
int mSpeed=0;
int fanSpeed;
int LED1=A1;
int LED2=A2;
int LED3=A3;
int LED4=A4;
int LED5=A5;

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver

  pinMode(speedPin,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);  

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch(results.value) {
      case 0xFF30CF:
        fanSpeed=123;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        break;

      case 0xFF18E7:
        fanSpeed=156;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        break;

      case 0xFF7A85:
        fanSpeed=189;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        break;

      case 0xFF10EF:
        fanSpeed=222;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);
        digitalWrite(LED5,LOW);
        break;

      case 0xFF38C7:
        fanSpeed=255;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,HIGH);
        digitalWrite(LED4,HIGH);
        digitalWrite(LED5,HIGH);
        break;

      case 0xFFA25D:
        fanSpeed=0;
        analogWrite(speedPin,fanSpeed);
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        break;
              
      case 0xFF906F: 
                      small_stepper.setSpeed(500); //Max seems to be 700
                      Steps2Take  =  256;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      break; 

      case 0xFFE01F: 
                      small_stepper.setSpeed(500);
                      Steps2Take  =  -256;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      break; 
                      
    }
    
      irrecv.resume(); // receive the next value
  }  


}/* --end main loop -- */
