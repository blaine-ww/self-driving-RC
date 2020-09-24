/* IR_Laser_Sensor.ino

* Logic sensor oriented forward for redundancy

* Date: Fall 2016
* Author: blaine-ww (Elaine Wu)

*/


int laser_din = 2;    // IR Laser connected at Pin 2


void setup(){

    pinMode(laser_din,INPUT);
    Serial.begin(9600);
}



void loop(){
  
    if(digitalRead( laser_din)==HIGH){

        Serial.println("NO Obstacles!");
    }
  
    else{
    
      Serial.println("Obstacles!");
    }
  
    delay(500);   //Detect every 0.5s
    exit(0);
}
