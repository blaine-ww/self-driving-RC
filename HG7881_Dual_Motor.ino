/* HG 7881_Dual_Motor.ino

  * H-bridge module HG7881CP/HG7881CP example code:
  ** http://diyprojects.eu/how-to-use-h-bridge-hg7881-with-external-power-supply-and-arduino

  * Date: Fall 2016
  * Modified by Author: blaine-ww (Elaine Wu)
 */




/**
 * Create variables to be used to run motor A
 */

 
int motorAPin_Forward = 10;   //Forward A1_A 10 Orange 
                              //Arduino digital 8 is connected to HG7881's A-1A terminal

int motorAPin_Back = 11;    //Reverse A1_B 11 Yellow
                            //Arduino digital 9 is connected to HG7881's A-1B terminal

int motorBPin_Left = 12;    // Left B1_A 11 White

int motorBPin_Right = 13;   // Right B1_B 12 Green




void setup(){
  /**
   * When program starts set Arduino pinmode for 8 and 9 digital to be OUTPUT
   * so we can use analogWrite to output values from 0 to 255 (0-5V) (PWM) 
   */
  pinMode(motorAPin_Forward, OUTPUT); //direction
  pinMode(motorAPin_Back, OUTPUT); //speed
}

void loop() {
    //set motor direction to "X"
    analogWrite(motorAPin_Forward, LOW);

    //start motor and increase speed while spinnning to direction "X"
    for(int i=0; i<=255; i++){
        
        //motor speed increases while we loop trough 
        //values from 0 to 255 (0V to power supply max voltage)
        analogWrite(motorAPin_Back, i);
        delay(40);
    }
   


    //wait 3 seconds while motor is running full speed
    delay( 3000 );
    
    //take 1 second pause, cutting power from motor ( speed pint to 0V )
    //so motor can stop (maybe your motor needs more time to spin down)
    analogWrite(motorAPin_Forward, LOW);
    analogWrite(motorAPin_Back, LOW);
    delay(1000);
    
  
    //now we switch direction to "Y" by setting 5V to 
    //direction pin A-1A
    analogWrite(motorAPin_Forward, 255);
    

    //start motor and increase speed while spinnning to direction "Y"
    for(int i=0; i<=255; i++){

        //To speed up like we did in direction "X" this module needs 
        //inverting of value we set on speed pin. 
        //So we go trough loop like before, but this time speed value 
        //decreases from 255 to 0 (via inverting value)
        analogWrite(motorAPin_Back, invertOurValue( i ) );
        delay(40);
    }
  


    //wait 3 seconds while motor is running full speed
    delay( 3000 );
    
    //take 1 second pause, cutting power from motor ( speed pint to 0V )
    analogWrite(motorAPin_Forward, LOW);
    analogWrite(motorAPin_Back, LOW);
    delay(1000);

//------------------------------------------------------------
//Steering

   analogWrite(motorBPin_Left, LOW);
    
    //start motor and increase speed while spinnning to direction "X"
    for(int i=0; i<=255; i++){
        
        //motor speed increases while we loop trough 
        //values from 0 to 255 (0V to power supply max voltage)
        analogWrite(motorBPin_Right, i);
        delay(40);
    }
   
    //wait 3 seconds while motor is running full speed
    delay( 3000 );
    
    //take 1 second pause, cutting power from motor ( speed pint to 0V )
    //so motor can stop (maybe your motor needs more time to spin down)
    analogWrite(motorBPin_Left, LOW);
    analogWrite(motorBPin_Right, LOW);
    delay(1000);
  
  
    //now we switch direction to "Y" by setting 5V to 
    //direction pin A-1A
    analogWrite(motorBPin_Left, 255);
    

    //start motor and increase speed while spinnning to direction "Y"
    for(int i=0; i<=255; i++){
        
        //To speed up like we did in direction "X" this module needs 
        //inverting of value we set on speed pin. 
        //So we go trough loop like before, but this time speed value 
        //decreases from 255 to 0 (via inverting value)
        analogWrite(motorBPin_Right, invertOurValue( i ) );
        delay(40);
    }
  
    //wait 3 seconds while motor is running full speed
    delay( 3000 );
    
    //take 1 second pause, cutting power from motor ( speed pint to 0V )
    analogWrite(motorBPin_Left, LOW);
    analogWrite(motorBPin_Right, LOW);
    delay(1000);
    
    //and now back to top

    exit(0);
}


int invertOurValue(int input) {
  return 255 - input;
}
