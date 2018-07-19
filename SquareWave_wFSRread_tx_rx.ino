// Bit-bang style square wave generator.
// Alex Mazursky
// July, 2018
// This script uses state machine logic to avoid using delay(). 

// Create a class for the sensor
class FSR
{
  // Class Member Variables
  int fsrPin;     // the FSR and pulldown are connected to A0
  int fsrReading;     // the analog reading from the FSR resistor divider
  // State Maintenance
  unsigned long previousMillis_FSR; // stores the last time the fsrReading is updated
  long interval = 50;  // interval at which to read FSR (milliseconds)

  // Constructor - creates an FSR 
  // and initializes the member variables and state
  public:
  FSR(int pin)
  {
  fsrPin = pin;
  previousMillis_FSR = 0;
  }

  void Update()
  {// check to see if it's time to read the FSR; that is, if the 
  // difference between the current time and last time you read 
  // the FSR is bigger than the interval at which you want to 
  // read the FSR.
  unsigned long currentMillis_FSR = millis();
 
  if(currentMillis_FSR - previousMillis_FSR > interval) {
    // save the last time you read the FSR 
    previousMillis_FSR = currentMillis_FSR;   
    fsrReading = analogRead(fsrPin);   
    Serial.print("Analog reading = ");
    Serial.print(fsrReading);     // the raw analog reading
    Serial.println();
    } 
  }
};

// Creates a class for the waveform
class Square
{
  // Class Member Variables
  // These are initialized at startup
  int signalPin;
  float PulseWidth;
  float PulseOff; 
  float freq = 5;
  float duty = 50;
  
  // These maintain the current state
  int signalState;
  unsigned long previousMillis_sq; // will store last time Signal was updated

  // Constructor - creates a Square 
  // and initializes the member variables and state
  public:
  Square(int pin)
  {
  signalPin = pin;
  pinMode(signalPin, OUTPUT);     
  
  signalState = HIGH; 
  previousMillis_sq = 0;
  }

  // Update function
  void Update()
  {// Read Frequency from Serial
  if (Serial.available())
  // If data is available to read,
  freq = Serial.read(); // read it and store it in freq
  PulseWidth = ((duty/100)/freq)*1000; // Convert freq to a time value for the ON signal
  PulseOff = (1/freq)*1000 - PulseWidth; // Convert freq to a time value for the OFF signal
  // Check current time
  unsigned long currentMillis_sq = millis();

  // Is it time to turn OFF?
  if((signalState == HIGH) && (currentMillis_sq - previousMillis_sq >= PulseWidth))
  {
    signalState = LOW;  // Turn it off
    previousMillis_sq = currentMillis_sq;  // Remember the time
    digitalWrite(signalPin, signalState);  // Update the actual Signal
  }

  // or... Is it time to turn ON?
  else if ((signalState == LOW) && (currentMillis_sq - previousMillis_sq >= PulseOff))
  {
    signalState = HIGH;  // turn it on
    previousMillis_sq = currentMillis_sq;   // Remember the time
    digitalWrite(signalPin, signalState);    // Update the actual Signal
  }
 }
};

// Make sensor object
FSR fsr(0); // Assign FSR to pin A0
// Make Square Wave Object  
Square sqsignal(3); // at PIN 3


void setup(){
  Serial.begin(9600); // Don't change!
  establishContact(); // send a byte to establish contact until receiver responds
}

void loop(){
  fsr.Update();
  sqsignal.Update(); // Merely loops through updating the signal!
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}
