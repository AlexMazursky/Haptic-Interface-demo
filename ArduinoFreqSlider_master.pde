import processing.serial.*;
import controlP5.*;

Serial myPort;  // Create object from Serial class

ControlP5 cp5;
int freq = 5; // Start at 5 Hz

void setup(){
 size(1000,200);
 String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
 myPort = new Serial(this, portName, 9600);
 
 cp5 = new ControlP5(this);
 
 // change the default font to Verdana
 PFont p = createFont("Verdana",20); 
 ControlFont font = new ControlFont(p);
 cp5.setFont(font);
 
 cp5.addSlider("freq")
 .setSize(800,100)
 .setPosition(100,50)
 .setRange(0,100);  
}

void draw(){
  background(0);
  myPort.write(freq);
}
