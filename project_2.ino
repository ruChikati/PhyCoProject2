
#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4

#define L1 8
#define L2 9
#define L3 10
#define L4 11


void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
}

int t1, t2, t3, t4, t5, time = millis(); // millis() gibt die Anzahl an Millisekunden die nach Programmstart vergangen sind zurueck

void loop() {
  if (analogRead(S1) < 250) { // Die Sensoren geben bei Erkunnung des Balles ein LOW Signali ab, was typischerweise unter 250 liegt
    t1 = millis();
    digitalWrite(L1, HIGH);
    delay(100);
    digitalWrite(L1, LOW);
  }
  if (analogRead(S2) < 250) {
    t2 = millis();
    digitalWrite(L2, HIGH);
    delay((unsigned long)(6.5 * abs(t2 - t1) / 14.5)); // Der Abstand zwischen den ersten beiden Sensoren ist 14,5cm; der Abstand zwischen dem 2. Sensor und der Mitte der 2. Spule ist 6,5cm. 
    digitalWrite(L2, LOW);
  }
  if (analogRead(S3) < 250) {
    t3 = millis();
    digitalWrite(L3, HIGH);
    delay((unsigned long)(6.5 * abs(t3 - t2) / 15.0));
    digitalWrite(L3, LOW);
  }
  if (analogRead(S4) < 250) {
    t4 = millis();
    digitalWrite(L4, HIGH);
    delay((unsigned long)(6.5 * abs(t4 - t3) / 14.0));
    digitalWrite(L4, LOW);
  }
  if (analogRead(S5) < 250) {
    t5 = millis();
  }
}

