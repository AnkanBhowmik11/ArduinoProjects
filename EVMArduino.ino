#include <LiquidCrystal.h>

// Pin Definitions
const int redLED = 6;
const int greenLED = 7;
const int buzzer = 8;
const int resetButton = 9;
const int countButton = 10;
const int candidateA = A0;
const int candidateB = A1;
const int candidateC = A2;
const int candidateD = A3;

// Variables to Track Votes and State
int votesA = 0, votesB = 0, votesC = 0, votesD = 0;
bool voteEnabled = false;  // Voting enabled flag
bool votingFinished = false; // To handle "No More Votes!" state

// Debounce Timing
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200; // 200ms debounce delay

void setup() {
  // Pin Modes
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(countButton, INPUT_PULLUP);
  pinMode(candidateA, INPUT_PULLUP);
  pinMode(candidateB, INPUT_PULLUP);
  pinMode(candidateC, INPUT_PULLUP);
  pinMode(candidateD, INPUT_PULLUP);

  // Initial States
  digitalWrite(redLED, HIGH); // Red LED ON initially
  digitalWrite(greenLED, LOW); // Green LED OFF initially
  digitalWrite(buzzer, LOW);   // Buzzer OFF initially

  // Initialize Serial for Debugging
  Serial.begin(9600);
  Serial.println("System Ready. Waiting for Reset...");
}

void loop() {
  // Handle "No More Votes!" state
  if (votingFinished) {
    if (debounceButton(resetButton) || debounceButton(countButton) ||
        debounceButton(candidateA) || debounceButton(candidateB) ||
        debounceButton(candidateC) || debounceButton(candidateD)) {
      noMoreVotesMessage();
    }
    return; // Exit the loop if voting has finished
  }

  // Check for Reset Button Press
  if (debounceButton(resetButton)) {
    resetMachine();
  }

  // Check for Voting Buttons
  if (voteEnabled) { // Voting enabled only after reset
    if (debounceButton(candidateA)) castVote('A');
    if (debounceButton(candidateB)) castVote('B');
    if (debounceButton(candidateC)) castVote('C');
    if (debounceButton(candidateD)) castVote('D');
  }

  // Check for Count Button Press
  if (debounceButton(countButton)) {
    countVotes();
    votingFinished = true; // Mark voting as finished
  }
}

void resetMachine() {
  if (votingFinished) return; // Do not allow reset after voting is finished

  voteEnabled = true; // Enable voting for a new voter
  digitalWrite(greenLED, HIGH); // Green LED ON
  digitalWrite(redLED, LOW);   // Red LED OFF

  // Debugging Output
  Serial.println("Reset pressed. Voting enabled.");
}

void castVote(char candidate) {
  if (voteEnabled) {
    voteEnabled = false; // Disable voting until reset
    digitalWrite(greenLED, LOW); // Green LED OFF
    digitalWrite(redLED, HIGH);  // Red LED ON

    // Count vote for selected candidate
    if (candidate == 'A') votesA++;
    else if (candidate == 'B') votesB++;
    else if (candidate == 'C') votesC++;
    else if (candidate == 'D') votesD++;

    // Debugging Output
    Serial.print("Vote cast for Candidate ");
    Serial.println(candidate);

    // Play buzzer
    tone(buzzer, 523, 1000); // Buzzer for 1 second
    delay(1000);

    // Debugging Output
    Serial.println("Voting complete. Please Reset to vote again.");
  }
}

void countVotes() {
  int totalVotes = votesA + votesB + votesC + votesD;

  // Debugging Output
  Serial.println("Counting Votes...");
  Serial.print("Total Votes: ");
  Serial.println(totalVotes);

  // Display Individual Votes in Specified Format (via Serial Output)
  Serial.print("Candidate A=");
  Serial.print(votesA);
  Serial.print(" / B=");
  Serial.println(votesB);

  Serial.print("Candidate C=");
  Serial.print(votesC);
  Serial.print(" / D=");
  Serial.println(votesD);

  // Play buzzer
  tone(buzzer, 440, 1000); // Buzzer for 1 second
  delay(1000);

  // Mark voting process as finished
  votingFinished = true;
}

void noMoreVotesMessage() {
  // Debugging Output
  Serial.println("No More Votes! Counting has already been done.");

  // Play buzzer
  tone(buzzer, 440, 500); // Buzzer for 0.5 second
  delay(500);
}

bool debounceButton(int buttonPin) {
  if (digitalRead(buttonPin) == LOW) {
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
      lastDebounceTime = currentTime;
      return true; // Button press confirmed
    }
  }
  return false; // Button not pressed
}
