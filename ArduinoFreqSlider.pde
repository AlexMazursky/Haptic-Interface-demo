import processing.serial.*; // serial communication library
import controlP5.*;         // sliders library

Serial myPort;  // Create object "myPort" from Serial class
ControlP5 cp5;  // Create object "cp5" from ControlP5 class

int freq = 5;   // Starting frequency at 5 Hz
int duty = 50;  // Begin duty cycle at 50%

void setup(){
 size(1000,350);
 String portName = Serial.list()[2]; // Port [2] is the left USB on my Macbook Pro
 myPort = new Serial(this, portName, 9600);
 cp5 = new ControlP5(this);
 
 // Font settings inside ControlP5
 PFont p = createFont("Verdana",20); // Makes font bigger than default
 ControlFont font = new ControlFont(p);
 cp5.setFont(font);
 
 // Add slider to adjust freq
 cp5.addSlider("freq")
 .setSize(800,100)
 .setPosition(100,50)
 .setRange(0,100);  // 0 to 100 Hz
 
 // Add slider to adjust duty
 cp5.addSlider("duty")
 .setSize(800,100)
 .setPosition(100,200)
 .setRange(0,100);  // 0 to 100%
}

void draw(){
  background(0);
  myPort.write(freq); // sends freq variable over serial to the Arduino script
  //myPort.write(":");
  //myPort.write(duty); // sends duty variable over serial to the Arduino script
  //myPort.write("&");
}
