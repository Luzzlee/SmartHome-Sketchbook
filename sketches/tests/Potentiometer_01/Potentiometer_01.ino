int redPin = 8;
int greenPin = 9;
int bluePin = 10;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  potentio();
}

void potentio() {
  redVal = 255;
  greenVal = 255;
  blueVal = 100;

  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}