//DIYREVOLUTION
#include <Servo.h>

// Pin definitions
const int servoPin = 9;     // Servo signal pin
const int buttonPin = 2;    // Optional button to trigger spray
const int potPin = A0;      // Optional potentiometer for manual servo angle control

// Spray parameters
const int restPosition = 0;      // Servo angle when not spraying (degrees)
const int sprayPosition = 45;    // Servo angle when spraying (degrees)
const int sprayDuration = 1000;  // How long to spray (milliseconds)
const int sprayInterval = 5000;  // Time between sprays in auto mode (milliseconds)

// Mode parameters
const int modePin = 3;      // Switch to select between auto/manual modes
bool autoMode = false;      // Mode flag (true = auto, false = manual)

// Create servo object
Servo sprayServo;

// Variables to track timing and state
unsigned long lastSprayTime = 0;
bool isCurrentlySpraying = false;
int servoAngle = restPosition;

void setup() {
  // Initialize servo
  sprayServo.attach(servoPin);
  sprayServo.write(restPosition);
  
  // Initialize input pins
  pinMode(buttonPin, INPUT_PULLUP);  // Button uses internal pullup
  pinMode(modePin, INPUT_PULLUP);    // Mode switch uses internal pullup
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Spray Can Servo Controller");
  Serial.println("-------------------------");
  Serial.println("Mode: Manual (use button or potentiometer)");
}

void loop() {
  // Check mode switch
  autoMode = !digitalRead(modePin);  // Switch to ground = auto mode
  
  if (autoMode) {
    // AUTO MODE: Spray at regular intervals
    if (millis() - lastSprayTime > sprayInterval && !isCurrentlySpraying) {
      spray();
    }
    
    // Check if spray duration is complete
    if (isCurrentlySpraying && millis() - lastSprayTime > sprayDuration) {
      resetSpray();
    }
  } 
  else {
    // MANUAL MODE: Use button or potentiometer
    
    // Button control (momentary spray)
    if (digitalRead(buttonPin) == LOW) {
      sprayServo.write(sprayPosition);
      Serial.println("Button pressed - Spraying");
    } else {
      sprayServo.write(restPosition);
    }
    
    // Potentiometer control (manual positioning)
    int potValue = analogRead(potPin);
    servoAngle = map(potValue, 0, 1023, restPosition, sprayPosition);
    sprayServo.write(servoAngle);
  }
  
  // Small delay to stabilize readings
  delay(20);
}

// Function to start spraying
void spray() {
  sprayServo.write(sprayPosition);
  lastSprayTime = millis();
  isCurrentlySpraying = true;
  Serial.println("Auto spray activated");
}

// Function to stop spraying
void resetSpray() {
  sprayServo.write(restPosition);
  isCurrentlySpraying = false;
  Serial.println("Spray complete");
}
