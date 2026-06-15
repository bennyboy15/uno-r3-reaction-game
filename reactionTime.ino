#define RED 13
#define YELLOW 12
#define GREEN 11
#define WHITE 10
#define BUTTON 9
#define DELAY 1000

void trafficLights() {
  digitalWrite(WHITE, LOW); // ENSURE WHITE IS OFF
  digitalWrite(RED, HIGH);  // RED ON
  delay(DELAY);
  digitalWrite(RED, LOW);      // RED OFF
  digitalWrite(YELLOW, HIGH);  // YELLOW ON
  delay(DELAY);
  digitalWrite(YELLOW, LOW);  // YELLOW OFF
  digitalWrite(GREEN, HIGH);  // GREEN ON
  delay(DELAY);
  digitalWrite(GREEN, LOW);  // GREEN OFF
  digitalWrite(WHITE, HIGH);
}

void turnOffLeds() {
  digitalWrite(WHITE, LOW); 
  digitalWrite(RED, LOW);      
  digitalWrite(YELLOW, LOW);  
  digitalWrite(GREEN, LOW);  
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);             // START SERIAL LISTENER
  pinMode(RED, OUTPUT);           // RED
  pinMode(YELLOW, OUTPUT);        // YELLOW
  pinMode(GREEN, OUTPUT);         // GREEN
  pinMode(WHITE, OUTPUT);         // WHITE
  pinMode(BUTTON, INPUT_PULLUP);  // BUTTON
  turnOffLeds();  // ENSURE LEDS ARE OFF TO START
}

int input;
bool timerRunning = false;
unsigned long startTime = 0;

// the loop function runs over and over again forever
void loop() {

  input = digitalRead(BUTTON);

  // START SEQUENCE
  if (input == LOW && !timerRunning) {
    trafficLights();
    timerRunning = true;
    startTime = millis();
    Serial.println("TIMER STARTED!");
    return;
  }  

  // BUTTON PRESSED AND GET REACTION TIME!!
  if (input == LOW && timerRunning) {
    unsigned long reactionTime = millis() - startTime;
    Serial.print("TIMER ENDED! REACTION TIME: ");
    Serial.print(reactionTime);
    Serial.println("ms");
    digitalWrite(WHITE, LOW);
    timerRunning = false;
    return;
  }

  delay(100);
}
