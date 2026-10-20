
#include <Servo.h>

// Pin connections
const int ENTRY_SENSOR = 2;
const int EXIT_SENSOR  = 3;
const int SERVO_PIN    = 9;

// Parking capacity
const int MAX_CAPACITY = 4;
int occupiedSpaces = 0;

// Most IR sensors are active LOW.
// Change to HIGH if your sensor detects with HIGH.
const int DETECTED = LOW;

// Gate settings
const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE   = 90;
const unsigned long GATE_OPEN_MS = 5000UL; // 5 seconds

const unsigned long DEBOUNCE_MS = 60UL;

Servo gateServo;

bool gateIsOpen = false;
unsigned long gateOpenedAt = 0;

bool entryHandled = false;
bool exitHandled = false;

unsigned long lastEntryChange = 0;
unsigned long lastExitChange = 0;

void openGate() {
  gateServo.write(GATE_OPEN_ANGLE);
  gateIsOpen = true;
  gateOpenedAt = millis();

  Serial.println("Gate opened to 90 degrees.");
  Serial.println("Gate will stay open for 5 seconds.");
}

void closeGateSlowly() {
  Serial.println("Closing gate gradually...");

  for (int angle = GATE_OPEN_ANGLE;
       angle >= GATE_CLOSED_ANGLE; angle--) {
    gateServo.write(angle);
    delay(20);
  }

  gateIsOpen = false;
  Serial.println("Gate closed at 0 degrees.");
}

void printStatus() {
  Serial.print("Occupied spaces: ");
  Serial.println(occupiedSpaces);

  Serial.print("Available spaces: ");
  Serial.println(MAX_CAPACITY - occupiedSpaces);

  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(9600);

  pinMode(ENTRY_SENSOR, INPUT);
  pinMode(EXIT_SENSOR, INPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED_ANGLE);

  Serial.println("SMART PARKING SYSTEM READY");
  printStatus();
}

void loop() {
  unsigned long now = millis();

  int entryReading = digitalRead(ENTRY_SENSOR);
  int exitReading  = digitalRead(EXIT_SENSOR);

  if (entryReading != DETECTED) {
    entryHandled = false;
  }

  if (exitReading != DETECTED) {
    exitHandled = false;
  }

  // ENTRY SENSOR
  if (entryReading == DETECTED && !entryHandled &&
      now - lastEntryChange >= DEBOUNCE_MS) {

    entryHandled = true;
    lastEntryChange = now;

    if (occupiedSpaces < MAX_CAPACITY) {
      occupiedSpaces++;
      Serial.println("Vehicle entered.");
      openGate();
    } else {
      Serial.println("Parking FULL. Entry not counted.");
    }

    printStatus();
  }

  // EXIT SENSOR
  if (exitReading == DETECTED && !exitHandled &&
      now - lastExitChange >= DEBOUNCE_MS) {

    exitHandled = true;
    lastExitChange = now;

    if (occupiedSpaces > 0) {
      occupiedSpaces--;
      Serial.println("Vehicle exited.");
      openGate();
    } else {
      Serial.println("Parking is already empty.");
    }

    printStatus();
  }

  // Close 7 seconds after the most recent valid event.
  if (gateIsOpen &&
      millis() - gateOpenedAt >= GATE_OPEN_MS) {
    closeGateSlowly();
  }

  delay(10);
}
