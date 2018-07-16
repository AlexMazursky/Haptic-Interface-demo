class Square
{
  // Class Member Variables
  // These are initialized at startup
  int signalPin;      // the number of the LED pin
  float PulseWidth;
  float PulseOff; 
  float freq = 5;
  float duty = 50;
  
  // These maintain the current state
  int signalState;
  unsigned long previousMillis; // will store last time Signal was updated

  // Constructor - creates a Square 
  // and initializes the member variables and state
  public:
  Square(int pin, float on, float off)
  {
  signalPin = pin;
  pinMode(signalPin, OUTPUT);     
    
  PulseWidth = on;
  PulseOff = off;
  
  signalState = HIGH; 
  previousMillis = 0;
  }

  void Update()
  {// Read Frequency from Serial
  if (Serial.available())
  // If data is available to read,
  freq = Serial.read(); // read it and store it in freq
  PulseWidth = ((duty/100)/freq)*1000;
  PulseOff = (1/freq)*1000 - PulseWidth;
  // Check current time
  unsigned long currentMillis = millis();

  // Is it time to turn OFF?
  if((signalState == HIGH) && (currentMillis - previousMillis >= PulseWidth))
  {
    signalState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(signalPin, signalState);  // Update the actual Signal
  }

  // or.. Is it time to turn ON?
  else if ((signalState == LOW) && (currentMillis - previousMillis >= PulseOff))
  {
    signalState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(signalPin, signalState);    // Update the actual Signal
  }
 }
};

// Uses state machine logic to avoid using delay()
// Make Square Wave Object  
Square sqsignal(3,100,100);

void setup(){
  Serial.begin(9600); 
}

void loop(){
  sqsignal.Update();
}

