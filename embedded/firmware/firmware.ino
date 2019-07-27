/*
 * Project: Vendo Firmware
 * Version: 2.0
 * Author: reedleoneil
 * 
 * Command Reference
 * q - return credit
 * w - add credit
 * e - remove credit
 * r - reset credit
 * 1 - slot 1
 * 2 - slot 2
 * 3 - slot 3
 * 4 - slot 4
 */

#include <Servo.h>
#include <SoftwareSerial.h>

/*
 * Variables
 */
volatile int credit = 0;
Servo slot1;
Servo slot2;
Servo slot3;
Servo slot4;

/*
 * Setup Function
 */
void setup() {
  Serial.begin(9600);
  attachInterrupt(3, credit_inc, RISING);
  slot1.attach(9);
  slot2.attach(10);
  slot3.attach(11);
  slot4.attach(12);
}

/*
 * Main Loop
 */
void loop() {
  if(Serial.available()){
    char cmd = Serial.read();
    if(cmd == 'q'){
      credit_ret();
    }else if(cmd == 'w'){
      credit_inc();
    }else if(cmd == 'e'){
      credit_dec(); 
    }else if(cmd == 'r'){
      credit_res();
    }else if(cmd == '1' || cmd == '2' || cmd == '3' || cmd == '4'){
      dispense(cmd);
    }
  }
}

/*
 * Credit Functions
 */
int credit_ret(){
  Serial.println("{ credit: " + String(credit) + " }");
}

void credit_inc(){
  credit++;
}

void credit_dec(){
  credit--;
}

void credit_res(){
  credit=0;
}

/*
* Dispense Item
*/
void dispense(char slot){
  if(slot == '1'){
    slot1.write(30);
    delay(1000);
    slot1.write(90);
    delay(1000);
  }else if(slot == '2'){
    slot2.write(30);
    delay(1000);
    slot2.write(90);
  }else if(slot == '3'){
    slot3.write(180);
    delay(1000);
    slot3.write(90);
  }else if(slot == '4'){
    slot4.write(180);
    delay(1000);
    slot4.write(90);
  }
}



