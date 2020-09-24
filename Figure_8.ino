/* Figure_8.ino
* Car Test
* Makes the modified RC car go in a figure 8.


* Date: Fall 2016
* Author: blaine-ww (Elaine Wu)

*/


// Plug the striped white wires into the Arduino pins
int forward = 11; // forward pin
int reverse = 10; // reverse pin
int left = 12; // left pin
int right = 13; // right pin

// The setup() method runs once, when the sketch starts
void setup() {
	// initialize the digital pins as an outputs:
	pinMode(forward, OUTPUT);
	pinMode(reverse, OUTPUT);
	pinMode(left, OUTPUT);
	pinMode(right, OUTPUT);
}



void go_forward(){
	analogWrite(forward, 150);
	//digitalWrite(forward,HIGH); // turn forward motor on
	digitalWrite(reverse,LOW); // turn revers motor off
}



void go_reverse(){
	digitalWrite(reverse,HIGH); // turn reverse motor on
	digitalWrite(forward,LOW); // turn forward notor off
}



void stop_car(){
	digitalWrite(reverse,LOW); // turn revers motor off
	digitalWrite(forward,LOW); // turn forward motor off
	digitalWrite(left,LOW);
	digitalWrite(right,LOW);
}



void go_left(){
	analogWrite(left, 255);  
	//digitalWrite(left,HIGH); // turn left motor on
	digitalWrite(right,LOW); // turn right motor off
}



void go_right(){
	analogWrite(right, 255);  
	//digitalWrite(right,HIGH); // turn right motor on
	digitalWrite(left,LOW); // tune left motor off
}



// the loop() method runs over and over again,
// as long as the Arduino has power
void loop(){

	delay(5000);	//Place Arduino UNO + retrofitted RC chassis on flat surface with open space to operate

	//delay(1000);
	go_right();			//clockwise
	delay(500);
	go_forward();
	delay(10000);
	
	//go_forward();		//counterclockwise
	//delay(1000);
	go_left();	
	delay(10000);
	
	//go_forward();		//clockwise
	//delay(1000);
	go_right();
	delay(10000);

	stop_car();			

	exit(0);
}
