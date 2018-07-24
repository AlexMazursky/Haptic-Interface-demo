// A user interface for control and monitoring of the haptic actuator.
// To be used in conjunction with Arduino script.
// Alex Mazursky
// July, 2018

import processing.serial.*; // serial communication library
import controlP5.*;         // sliders library

Serial myPort;  // Create object "myPort" from Serial class
ControlP5 cp5;  // Create object "cp5" from ControlP5 class

// FSR
String fsrRead;
int xPos = 1;         // horizontal position of the graph
float inByte = 0;

// Square Wave
int freq = 5;   // Starting frequency at 5 Hz
int duty = 50;  // Begin duty cycle at 50%

// Toggle State
boolean HV = false; // Start without HV signal

void setup(){
 size(1000,600);
 noSmooth();
 String portName = Serial.list()[2]; // Port [2] is the left USB on my Macbook Pro
 myPort = new Serial(this, portName, 9600);
 myPort.bufferUntil('\n'); 
 cp5 = new ControlP5(this);
 
 // Font settings inside ControlP5
 PFont p = createFont("Verdana", 20); // Makes font bigger than default
 ControlFont font = new ControlFont(p);
 cp5.setFont(font);
 cp5.setColorForeground(color(38, 225, 160));
 cp5.setColorActive(color(40, 255, 180));
 cp5.setColorBackground(color(30, 178, 126));
 
 // Add slider to adjust freq
 cp5.addSlider("freq")
 .setSize(700,100)
 .setPosition(200,50)
 .setRange(0,100);  // 0 to 100 Hz
 
 // Add a toggle to switch HV ON or OFF
 cp5.addToggle("HV")
 .setPosition(50,50)
 .setSize(100,100)
 .setColorForeground(color(200, 33, 33))
 .setColorActive(color(255, 45, 45))
 .setColorBackground(color(175, 20, 20));
  
 // set initial background
 background(50);
}

void draw(){
  // draw the line:
    stroke(255, 253, 78);
    line(xPos, height, xPos, height - inByte);
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(50);
    } else {
      // increment the horizontal position:
      xPos++;
    }
    
  // Check to see if the button for HV is on
  if(HV==true){
  myPort.write(freq); // sends freq variable over serial to the Arduino script
  }
  if(HV==false){
  myPort.write(101); // sends freq variable over serial to the Arduino script
  }
}

void serialEvent( Serial myPort) {
//put the incoming data into a String - 
//the '\n' is our end delimiter indicating the end of a complete packet
fsrRead = myPort.readStringUntil('\n');
//make sure our data isn't empty before continuing
if (fsrRead != null) {
  //trim whitespace:
  fsrRead = trim(fsrRead);
  // convert to an int and map to the screen height:
  inByte = float(fsrRead);
  //println(inByte);
  inByte = map(inByte, 0, 1023, 0, 3*height/4);
  }
}
