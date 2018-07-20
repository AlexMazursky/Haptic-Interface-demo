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

void setup(){
 size(1000,700);
 String portName = Serial.list()[2]; // Port [2] is the left USB on my Macbook Pro
 myPort = new Serial(this, portName, 9600);
 myPort.bufferUntil('\n'); 
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
 
 // set initial background
 background(0);
}

void draw(){
  // draw the line:
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - inByte);
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
  myPort.write(freq); // sends freq variable over serial to the Arduino script
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
  inByte = map(inByte, 0, 1023, 0, 2*height/3);
  }
}
