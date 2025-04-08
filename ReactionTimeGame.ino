const int ledPins[4] = {2, 3, 4, 5};     // LED pins
const int buttonPins[4] = {6, 7, 8, 9};  // Game button pins
const int startButtonPin = 10;           // Start/reset button pin
const int buzzerPin = 11;                // Buzzer pin

unsigned long reactionTimes[10];         // Store reaction times
int currentTrial = 0;                     // Current trial number
bool gameStarted = false;                 // Tracks whether the game is active

void setup() {
  Serial.begin(9600);

  // Set up LED pins as OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Set up button pins as INPUT
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Internal pull-up resistors
  }

  // Configure start/reset button and buzzer
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.println("Press the start button to begin the game!");
}

void loop() {
  if (digitalRead(startButtonPin) == LOW) { // Start/reset button pressed
    delay(200); // Debounce delay
    if (!gameStarted) {
      startGame();
    } else {
      resetGame(); // Reset game if button pressed during gameplay
    }
  }

  if (gameStarted && currentTrial < 10) {
    playTrial();
  } else if (gameStarted && currentTrial >= 10) {
    endGame();
  }
}

void startGame() {
  gameStarted = true;
  currentTrial = 0; // Reset trial count
  Serial.println("Game started!");

  // Play start buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(1000); // 1 second
  digitalWrite(buzzerPin, LOW);

  delay(1000); // Delay before the first trial
}

void playTrial() {
  int randomLED = random(0, 4); // Choose a random LED
  digitalWrite(ledPins[randomLED], HIGH);
  unsigned long startTime = millis();

  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
        unsigned long reactionTime = millis() - startTime;

        if (i == randomLED) { // Correct button pressed
          reactionTimes[currentTrial] = reactionTime;
          Serial.print("Reaction Time for Trial ");
          Serial.print(currentTrial + 1);
          Serial.print(": ");
          Serial.print(reactionTime);
          Serial.println(" ms");
          digitalWrite(ledPins[randomLED], LOW);
          delay(500);
          currentTrial++;
          return;
        } else {
          Serial.println("Wrong button! Try again.");
        }
      }
    }
  }
}

void endGame() {
  // Play end buzzer for 1 second
  digitalWrite(buzzerPin, HIGH);
  delay(1000); // 1 second
  digitalWrite(buzzerPin, LOW);

  // Calculate average reaction time
  unsigned long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += reactionTimes[i];
  }
  unsigned long averageTime = sum / 10;
  Serial.print("Average Reaction Time: ");
  Serial.print(averageTime);
  Serial.println(" ms");

  Serial.println("Game over. Press the reset button to play again.");
  gameStarted = false; // Stop game until reset
}

void resetGame() {
  Serial.println("Game reset.");
  gameStarted = false;
  currentTrial = 0;
  Serial.println("Press the start button to begin a new game.");
}