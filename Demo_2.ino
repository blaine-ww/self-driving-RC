/* Self-driving RC Car

* Architect based on:
* http://www.instructables.com/id/Autonomous-Race-Car/?ALLSTEPS
* Created by Jesper Birk - 2014

* Heavily Modified by blaine-ww (Elaine Wu) - 2016

*/


// Forward A1_A 8 Orange
int motorPin_Forward =  10;    	// motor wire connected to digital pin 10

// Reverse A1_B 9 Yellow
int motorPin_Back =  11;    	// motor wire connected to digital pin 11

// Left B1_A 11 White
int motorPin_Left =  12;    	// steering motor wire connected to digital pin 12

// Right B1_B 12 Green
int motorPin_Right =  13;    	// steering motor wire connected to digital pin 13

// Set Speed
int steeringMotorSpeed = 250;	// Set default power to send to steering motor
int gentleSteeringSpeed = 170; 	// Minimum to activate steering
int fullTrottleSpeed = 250;
int cruiseSpeed = 140;
int cautiousSpeed = 110;
int avoidSpeed = 120;
int reverseSpeed = 170;

// Set Distance
int avoidDistance = 70;
int endAvoidDistance = 80;
int goToReverseDistance = 60;
int fullTrottleMinDistance = 250;

// Set Default Reaction Times
int reverseTime = 400;
int sensorDelay = 400;
int how_long = 30000;
unsigned long previousMillis;

// RSSI Calibration
int target_dB = 0; //Will change after figuring out RSSI function on xbee chip
int turn_around_db = 0;

// Additional Miscellanous Variables
long randNumber;
int avoidDirection = 1;
int avoidCirclesBeforeDirectionChange = 10;
int countDown = 1;
int distanceCountDown = 1;
int distance = 0;
int measurement = 0;
int k = 0;
int iterations = 3;

// Laser
#define Laser_din 2

// Ultrasonic Distance Sensor Setup
#include <NewPing.h>
#define SONAR_NUM     3 // Number or sensors.
#define PING_INTERVAL 33 // Milliseconds between pings.

// Sensor 1: LEFT
#define trigPin1  5
#define echoPin1  4
#define LEFT      1
int LeftSensor = 0;

// Sensor 2: FRONT
#define trigPin2  9 //Orange
#define echoPin2  8 //Yellow
#define FRONT     2
int FrontSensor = 0;

// Sensor 3: RIGHT
#define trigPin3  7 //Orange
#define echoPin3  6 //Yellow
#define RIGHT     3
int RightSensor = 0;

double echoTime = 0;
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, fullTrottleMinDistance);

NewPing Sonar1(trigPin1, echoPin1, fullTrottleMinDistance);
NewPing Sonar2(trigPin2, echoPin2, fullTrottleMinDistance);
NewPing Sonar3(trigPin3, echoPin3, fullTrottleMinDistance);

// The setup() method runs once, when the sketch starts



void setup()   {
	  
	// Initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	randomSeed(analogRead(0));
	pinMode(motorPin_Forward, OUTPUT); // initialize the digital pins as an output
	pinMode(motorPin_Back, OUTPUT);
	pinMode(motorPin_Left, OUTPUT);
	pinMode(motorPin_Right, OUTPUT);

	pinMode(trigPin1, OUTPUT); //initialize ultrasonic distance sensors
	pinMode(echoPin1, INPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(echoPin2, INPUT);
	pinMode(trigPin3, OUTPUT);
	pinMode(echoPin3, INPUT);

  	pinMode(Laser_din, INPUT); //initialize Laser

}




////////////   MAIN LOOP    ////////////
void loop() {
  
	while (millis() < how_long) {

		Serial.println("start loop  ");
		distance = Measure_Distance(FRONT);

		if (distance > 0) {

		    if ( (distance <= goToReverseDistance) || (digitalRead(Laser_din)==LOW) ) {
				
				Serial.println("ReverseMode Activated");
				digitalWrite(motorPin_Forward, LOW);
				ReverseMode();
		    }
		    
		    distance = Measure_Distance(FRONT);

		    if ( (distance < avoidDistance) || (digitalRead(Laser_din)==LOW) ) {
			
				Serial.println("AvoidMode Activated");
				AvoidMode();
			}
		    
		    distance = Measure_Distance(FRONT);

		    while (distance > fullTrottleMinDistance) {
		    
				Serial.println("FullThrottleMode Activated");
				FullThrottleMode();
			}
		    
		    distance = Measure_Distance(FRONT); 

		    if ((distance > avoidDistance)  && (distance < fullTrottleMinDistance)) {
				
				Serial.println("CruiseMode Activated");
				CruiseMode();
			}
		    
		    distance = Measure_Distance(FRONT);
		}

		else {					//(distance == 0) {
			Reset_Motors();
			analogWrite(motorPin_Forward, cautiousSpeed);
		}
		
		distance = Measure_Distance(FRONT);

		Serial.println("REstart loop  ");  Serial.println();

	}	

	Reset_Motors();
	exit(0);

}



//-------------Functions------------------------------------------------------------------

/* Measure distance from input sensor based on median of three pings
 * Input: LEFT, FRONT, RIGHT 
 * Output: distance [cm]
 */
int Measure_Distance(int direction) {

	//measurement=sonar.ping_cm();
	//echoTime=sonar.ping_median(iterations);
	//measurement=sonar.convert_cm(echoTime);
	//Serial.print(measurement); Serial.println("cm");


	// Modified for 3 sensor inputs
	echoTime=Sonar1.ping_median(iterations); delayMicroseconds(10);
	LeftSensor = Sonar1.convert_cm(echoTime);
	echoTime=Sonar2.ping_median(iterations); delayMicroseconds(10);
	FrontSensor = Sonar2.convert_cm(echoTime);
	echoTime=Sonar3.ping_median(iterations); delayMicroseconds(10);
	RightSensor = Sonar3.convert_cm(echoTime);
  
	/*LeftSensor = Sonar1.ping_cm(); delayMicroseconds(10);
	RightSensor = Sonar2.ping_cm(); delayMicroseconds(10);
	FrontSensor = Sonar3.ping_cm(); delayMicroseconds(10);
	*/


    //Erase invalid values disabled due to latency
	//if (LeftSensor <0){LeftSensor=0; }
	//if (RightSensor <0){RightSensor=0; }
	//if (FrontSensor <0){FrontSensor=0; }

	//Print values on console
	Serial.print("Left = "); Serial.print(LeftSensor); Serial.print(" cm  ");
	Serial.print("Front = "); Serial.print(FrontSensor); Serial.print(" cm  ");
	Serial.print("Right = "); Serial.print(RightSensor); Serial.print(" cm  ");
	Serial.println();

	if (direction == LEFT) {
		return LeftSensor;
	}
	
	else if (direction == RIGHT) {
		return RightSensor;
	}
	
	else if (direction == FRONT) {
		return FrontSensor;
	}
	
	else {
		return 0;
	}
 
}



/* Direct wheels toward direction of greater distance measured
 * Input: LEFT, FRONT, RIGHT 
 * Output: distance [cm]
 */
void TurnAway(int direction, int speed) {
  
	//  if(avoidDirection == 1){        <---- This method is Roomba's random turn method.
	//randNumber=random(2,4);           <-----But decided against this method because it is not the best navigation method.
	//Serial.println("Random Number =");
	//Serial.println(randNumber);
	
	if ( ((direction > 0) && (Measure_Distance(LEFT) > Measure_Distance(RIGHT)) ) || ( (direction < 0) && (Measure_Distance(LEFT) < Measure_Distance(RIGHT))) ) {
		Serial.println("LEFT");
		analogWrite(motorPin_Left, speed); // turn one way <left>
		digitalWrite(motorPin_Right, LOW);
	}
	
	else {
		Serial.println("RIGHT");
		analogWrite(motorPin_Right, speed); // or turn the other way <right>
		digitalWrite(motorPin_Left, LOW);
	}
	//} end of random direction if loop
}


/* Turn off motors; re-align steering
 */
void Reset_Motors() {
  digitalWrite(motorPin_Forward, LOW);
  digitalWrite(motorPin_Back, LOW);
  digitalWrite(motorPin_Left, LOW);
  digitalWrite(motorPin_Right, LOW);
}




////////////   REVERSE MODE    ////////////
/* Reverse motor direction
 */
void ReverseMode() {

	Serial.println("Begin Reverse");
	avoidDirection = avoidDirection * -1; //(-)Negative
	//Reset_Motors(); delayMicroseconds(10);

	//while(distance < avoidDistance) {

	digitalWrite(motorPin_Forward, LOW);
	analogWrite(motorPin_Back, reverseSpeed);            //rotates motor - backwards
	//if ( (Measure_Distance(LEFT) < 15) || (Measure_Distance(RIGHT) < 15 ) ) {
	TurnAway(avoidDirection, steeringMotorSpeed);
	//}

	delay(reverseTime);                              	// for time set in reverseTime
	//   delay(sensorDelay);
	distance = Measure_Distance(FRONT);
	//   }

	digitalWrite(motorPin_Back, LOW);                    // stop motors
	digitalWrite(motorPin_Left, LOW);
	digitalWrite(motorPin_Right, LOW);
	avoidDirection = avoidDirection * -1;             	// (+)switch steering direction back forward
	distance = Measure_Distance(FRONT);
	digitalWrite(motorPin_Left, LOW);
	digitalWrite(motorPin_Right, LOW);
}
////////////////////////////////////////////////




////////////   AVOID MODE    ////////////
/* Slows motor down and re-direct RC car gently toward sensor with greater distance detected 
 */
void AvoidMode() {

	Serial.println("Begin Avoid");
	distance = Measure_Distance(FRONT);
	//if(distance < avoidDistance){
	countDown = avoidCirclesBeforeDirectionChange;
	distanceCountDown = distance;


	while (distance <= endAvoidDistance && distance > goToReverseDistance) {
		
		analogWrite(motorPin_Forward, avoidSpeed); 	//rotates motor
		digitalWrite(motorPin_Back, LOW);    		// set the Pin motorPin_Back LOW
		TurnAway(avoidDirection, steeringMotorSpeed);
		delay(sensorDelay);
		distance = Measure_Distance(FRONT);
		
		// countdown remaining distance per loop
		if (distance < distanceCountDown) {
			countDown--;  // if obstacle is getting closer - count down to changing direction
		}

		// last resort reverse backward to direction with wheels turned toward direction with greater distance
		if (countDown < 1) {
			avoidDirection = avoidDirection * -1;   // switch steering direction
			countDown = avoidCirclesBeforeDirectionChange;
			distanceCountDown = distance;
		}
		
		// Serial.println(distance);
		// Serial.println(avoidDirection);
	}   // end while (avoid)

	digitalWrite(motorPin_Left, LOW); //Realign wheels
	digitalWrite(motorPin_Right, LOW);
}
////////////////////////////////




////////////   FULL SPEED MODE    ////////////
/* Max motor speed going forward
 */
void FullThrottleMode() {

	Serial.println("Begin Full Speed");
	distance = Measure_Distance(FRONT);
	TurnAway(avoidDirection, gentleSteeringSpeed);
	//while(distance > fullTrottleMinDistance){
	
	analogWrite(motorPin_Forward, fullTrottleSpeed); //rotates motor
	digitalWrite(motorPin_Back, LOW);    // set the Pin motorPin_Back LOW
	digitalWrite(motorPin_Left, LOW);
	digitalWrite(motorPin_Right, LOW);
	
	delay(sensorDelay);
	distance = Measure_Distance(FRONT);
	// Serial.println("FULL");
	// Serial.println(distance);
	// end while
}



////////////   CRUISE MODE    ////////////
/* Moderate motor speed going forward and slight avoidance
 */
void CruiseMode() {

	Serial.println("Begin Cruise");

	//distance = (ultrasonic.Ranging(CM));
	distance = Measure_Distance(FRONT);	
	//TurnAway(avoidDirection, cautiousSpeed);
	//if ( (Measure_Distance(LEFT) < 15) || (Measure_Distance(RIGHT) < 15 ) ) {

	//}
	//  while(distance > avoidDistance  && distance < fullTrottleMinDistance){
	analogWrite(motorPin_Forward, cruiseSpeed); //rotates motor
	digitalWrite(motorPin_Back, LOW);    // set the Pin motorPin_Back LOW
	TurnAway(avoidDirection, gentleSteeringSpeed);
	delay(sensorDelay);
	digitalWrite(motorPin_Left, LOW);
	digitalWrite(motorPin_Right, LOW);
	delayMicroseconds(10);

	//distance = (ultrasonic.Ranging(CM));
	//Serial.println("cruise");
	//Serial.println(distance); Serial.println("cm");
	//}   // end while
}

//---------------END of FUNCTIONS----------------------------------------------
