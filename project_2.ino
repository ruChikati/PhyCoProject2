
#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4

#define L1 8
#define L2 9
#define L3 10
#define L4 11

#define epsilon 10

int S1Normal, S2Normal, S3Normal, S4Normal, S5Normal = 0;


// Vor.: Keine
// Eff.: `S*Normal` sind dem durchschnittlichen Wert der Sensoren gleichgesetzt. Dies dauerte `dur` Millisekunden. 
void calibrateSensors(int dur) {
  int max1, max2, max3, max4, max5 = 0;
  int min1, min2, min3, min4, min5 = 1023;
  for(int i=0; i<=dur; i++) {
    min1 = min1 < analogRead(S1) ? analogRead(S1) : min1; // if (min1 < analogRead(S1)) {min1 = analogRead(S1);} else {min1 = min1;}
    min2 = min2 < analogRead(S2) ? analogRead(S2) : min2;
    min3 = min3 < analogRead(S3) ? analogRead(S3) : min3;
    min4 = min4 < analogRead(S4) ? analogRead(S4) : min4;
    min5 = min5 < analogRead(S5) ? analogRead(S5) : min5;
    
    max1 = max1 > analogRead(S1) ? analogRead(S1) : max1;
    max2 = max2 > analogRead(S2) ? analogRead(S2) : max2;
    max3 = max3 > analogRead(S3) ? analogRead(S3) : max3;
    max4 = max4 > analogRead(S4) ? analogRead(S4) : max4;
    max5 = max5 > analogRead(S5) ? analogRead(S5) : max5;
    
    delay(1);
  }
  S1Normal = (max1 + min1) / 2;
  S2Normal = (max2 + min2) / 2;
  S3Normal = (max3 + min3) / 2;
  S4Normal = (max4 + min4) / 2;
  S5Normal = (max5 + min5) / 2;
}

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  calibrateSensors(2000);
  Serial.begin(9600);
}

int time = millis(); // millis() gibt die Anzahl an Millisekunden die nach Programmstart vergangen sind zurueck
int t1, t2, t3, t4, t5 = 0;

void loop() {
  if(analogRead(S1) < S1Normal - epsilon) { // epsilon wird abgezogen, um zufaellige Lichtfluktuationen im Raum von dem Signal rauszufiltrieren
    t1 = millis();
    digitalWrite(L1, HIGH);
    delay(100);
    digitalWrite(L1, LOW);
  }
  if(analogRead(S2) < S2Normal - epsilon) {
    t2 = millis();
    digitalWrite(L2, HIGH);
    delay((int)(6.5 * (t2 - t1) / 14.5)); // Der Abstand zwischen den ersten beiden Sensoren ist 14,5cm; der Abstand zwischen dem 2. Sensor und der Mitte der 2. Spule ist 6,5cm. 
    digitalWrite(L2, LOW);
  }
  if(analogRead(S3) < S3Normal - epsilon) {
    t3 = millis();
    digitalWrite(L3, HIGH);
    delay((int)(6.5 * (t3 - t2) / 15.0));
    digitalWrite(L3, LOW);
  }
  if(analogRead(S4) < S4Normal - epsilon) {
    t4 = millis();
    digitalWrite(L4, HIGH);
    delay((int)(6.5 * (t4 - t3) / 14.0));
    digitalWrite(L4, LOW);
  }
  Serial.println(analogRead(S2));
}

