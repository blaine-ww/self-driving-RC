# self-driving-RC
Date: 12.12.2016
Author: [blaine-ww](http://www.github.com/blaine-ww)
Video: [YouTube](https://youtu.be/90q5XMcJOZo)
@file _README.md_


## Scope
Programmed RC car to avoid obstacles w/o prior mapping solely based on equipped ultrasonic distance & laser sensors’ feedback, in which my car successfully navigated around eight various sized objects on final day demonstration.

Please refer to *Final Application Presentation.pptx* for details about project scope and background. Refer to mehcanics and retrofitting in *RC Dissection.pdf*. Refer to technical specifications of individual components in *Self-Driving Car - Technical Documents.pdf*.


## Environment
Operable indoors on flat surface with enough space provided to manuever RC toy car to avoid oncoming obstacles. 

### Disclaimer:
Depending on the type of ultrasonic distance sensors utilized, refractive, curved, or metallic/transparent surfaces will not provide accurate distance readings.


## Requirments
* Radio control car with motorized rear axle and pivoting front axle. 
* H-bridge dual motor controller soldered/wired to rear and front axle motors
* Arduino UNO Microcontroller
* Ultrasonic distance sensors (3)
* Infrared Logic Sensor
* Miniature breadboard and male-to-male wires for circuitry/connecting components
* *Optional*: Xbee RSSI transmitter + reeiver 


## Instructions
1. Disassemble miniature toy car such that the remaining chassis only has the motorized front and rear axle wheels attached.
2. Solder H-bridge dual motor controller to front motor and rear motor noting which inputs triggers left, right motion for front wheels as well as forward, reverse motion for back wheels. This can be done by tapping each soldered wire with power input to determine the direction of the front wheel pivoting or rear wheels rotating. 
3. Attach the Arduino UNO microcontroller onto the chassis, connect the wiring from the battery compartment of the chassis to power the Arduino UNO microncontroller. 
*Note: If the RC car does not run at least 5V to power the microcontroller, additional battery pack may be added.*
4. Attach the soldered wiring fron the 4 inputs of the H-bridge to the microntoller, noting which pins were used and cross-correlate with *left, right, forward, reverse* motions, and modify associated pins in *HG7881_Dual_Motor.ino*.
5. After successful retrofit of chassis, test out the setup with the *Figure_8.ino*. The chassic should move in a figure-8 motion continuosly as seen in Final Application Presentation.pptx.
6. Attach the miniature breadboard to the roof of the plastic body (that was previously removed) and pin the 3 ultrasonic distance sensors facing front, left, and right on the breadboard. Route wiring from distance sensor pins on breadboard to Arduino UNO microntroller pins underneath plastic cover.
*Note: Record which microcontroller pins are connected to each distance sensor.* 
Modify associated pins in *HC-SR04_Triple_delay.ino*.
7. Pin the infrared logic sensor behind the front orientated distance sensor. Route wiring from logic sensor pins on the breadboard to Arduino Uno pins. 
*Note: Record which microcontroller pins are connected to the logic sensor.*
Modify associated pins in *IR_Laser_Sensor.ino*.
8. Finalize orientation of distance sensors to maximize field of view.
9. In *Demo_2.ino*, replace all pin numbers with appropriate pins noted earlier during installation. 
10. Xbee RSSI is also optional to determine final destination of vehicle. Need to program master-slave setting as indicated in *Technical Specifications*. And attached, wire the receiver component to the roof/breadboard. Set the transmitter component at desired location for final destination.


## Testing Setup
Place obstacles such that there is ample space for a full span of RC car to manuever past objects. Set the program on a 30sec timer to test program *Demo_2.ino*.


## Main Build
The main program is *Demo_2.ino*. To calibrate sensors, determine full speed of car when 5V is applied to microcontroller, then adjust the time delays in the *Demo_2.ino* to reflect the reaction time in real-time.

After adjusting settings to optimization, turn on the RC car, and let the vehicle roam indefinitely (until battary dies). Also can implement *Step 10* in ##Instructions to set a destination.
