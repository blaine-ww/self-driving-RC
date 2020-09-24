/* HC-SR04_Triple_delay.ino

* Ultrasonic distance sensors layout:
	*Left
	*Front
	*Right

* Date: Fall 2016
* Author: blaine-ww (Elaine Wu)
*/



// Connect Arduino pins as listed
#define trigPin1 5
#define echoPin1 4
#define trigPin2 9
#define echoPin2 8
#define trigPin3 7
#define echoPin3 6

long duration, distance, RightSensor, BackSensor, FrontSensor, LeftSensor;




void setup(){
	Serial.begin (9600);
	pinMode(trigPin1, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(echoPin2, INPUT);
	pinMode(trigPin3, OUTPUT);
	pinMode(echoPin3, INPUT);
}



void loop() {

	// Run loop for 10 seconds
	while (millis() <= 10000){


		// Calculate distance between sensor and detected object
		SonarSensor(trigPin1, echoPin1);	
		LeftSensor = distance;

		SonarSensor(trigPin2, echoPin2);
		FrontSensor = distance;
		
		SonarSensor(trigPin3, echoPin3);
		RightSensor = distance;


		// Print out left, front, right distance calculated on console
		Serial.print("Left = ");Serial.print(LeftSensor); Serial.print(" cm  ");
		Serial.print("Front = "); Serial.print(FrontSensor); Serial.print(" cm  ");
		Serial.print("Right = "); Serial.println(RightSensor); Serial.print(" cm  ");
		Serial.println();
	}
}




// Calculate the distance [cm]
// Input: power, echo
// Output: ditance [cm]
void SonarSensor(int trigPin,int echoPin) {
	
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration/2) / 29.1;

}
