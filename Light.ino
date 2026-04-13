// FULL TURN SIGNAL TEST (LEFT + RIGHT ALTERNATING)

// Pin setup
// LED pins
const int LED_LEFT_TURN = 49;
const int LED_RIGHT_TURN = 43;
const int LED_LEFT_BACK_TURN = 31;
const int LED_RIGHT_BACK_TURN = 37;
const int LED_LEFT_BRAKE = 27;
const int LED_RIGHT_BRAKE = 33;

void setup() {
  pinMode(LED_LEFT_TURN, OUTPUT);
  pinMode(LED_RIGHT_TURN, OUTPUT);
  pinMode(LED_LEFT_BACK_TURN , OUTPUT);
  pinMode(LED_RIGHT_BACK_TURN, OUTPUT);
  pinMode(LED_LEFT_BRAKE, OUTPUT);
  pinMode(LED_RIGHT_BRAKE, OUTPUT);
}

void loop() {

  // ===== LEFT SIDE BLINK =====
  for (int i = 0; i < 4; i++) {
    // Left ON, Right OFF
    digitalWrite(LED_LEFT_TURN, HIGH);
    digitalWrite(LED_LEFT_BACK_TURN, HIGH);
    digitalWrite(LED_RIGHT_TURN, LOW);
    digitalWrite(LED_RIGHT_BACK_TURN, LOW);
    delay(300);

    // Left OFF
    digitalWrite(LED_LEFT_TURN, LOW);
    digitalWrite(LED_LEFT_BACK_TURN, LOW);
    delay(300);
  }

  delay(500); // pause between sides

  // ===== RIGHT SIDE BLINK =====
  for (int i = 0; i < 4; i++) {
    // Right ON, Left OFF
    digitalWrite(LED_RIGHT_TURN, HIGH);
    digitalWrite(LED_RIGHT_BACK_TURN, HIGH);
    digitalWrite(LED_LEFT_TURN, LOW);
    digitalWrite(LED_LEFT_BACK_TURN, LOW);
    delay(300);

    // Right OFF
    digitalWrite(LED_RIGHT_TURN, LOW);
    digitalWrite(LED_RIGHT_BACK_TURN, LOW);
    delay(300);
  }

  // ===== BREAK LIGHTS =====
  void BrakeLight() {
    allLightsOff();
    digitalWrite(LED_LEFT_BRAKE, HIGH);
    digitalWrite(LED_RIGHT_BRAKE, HIGH);
  }
  
  // ===== ALL LIGHTS OFF =====
  void allLightsOff() {
  digitalWrite(LED_LEFT_TURN, LOW);
  digitalWrite(LED_RIGHT_TURN, LOW);
  
  digitalWrite(LED_LEFT_BACK_TURN, LOW);
  digitalWrite(LED_RIGHT_BACK_TURN, LOW);

  digitalWrite(LED_LEFT_BRAKE, LOW);
  digitalWrite(LED_RIGHT_BRAKE, LOW);
}

  delay(1000); // pause before repeating
}