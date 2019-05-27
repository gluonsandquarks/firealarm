#include <DHT.h>

DHT dht(A2, DHT11);

float t, h, l;
int l1, l2, l3;
int tr = 0;
char ltr;

const long A = 1000;
const int B = 15, Rc = 5.6;

void setup() {
  //Serial & pinouts
  Serial.begin(9600);
  dht.begin();
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
}

void loop() {
  
  //RX
  t = analogRead(A0);
  delay(10);
  t = analogRead(A0);
  delay(10);
  t = (t * 0.48828125);

  l = analogRead(A1);
  delay(10);
  l = analogRead(A1);
  delay(10);
  l = ((long)(1024-l)*A*10)/((long)B*Rc*l);
  
  h = dht.readHumidity();
  delay(10);
  h = dht.readHumidity();
  delay(10);

  //temp flags
  if (t > 40) {
    l1 = 1;
    digitalWrite(13, HIGH);
  } else if (t < 38) {
    l1 = 0;
    digitalWrite(13, LOW);
  }
  
  //hum flags
  if (h < 30) {
    l2 = 1;
    digitalWrite(11, HIGH);
  } else if (h > 35) {
    l2 = 0;
    digitalWrite(11, LOW);
  }
  
  //lum flags
  if (l < 30) {
    l3 = 1;
    digitalWrite(12, HIGH);
  } else if (l > 60) {
    l3 = 0;
    digitalWrite(12, LOW);
  }
  
  //alarm trigger
  if (Serial.available()) {
    ltr = Serial.read();
    }
    
  tr = digitalRead(6);
  delay(10);
  tr = digitalRead(6);
  delay(10);
  //var values
  Serial.print(tr);
  Serial.print(" ");
  Serial.print(t);
  Serial.print("C ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print(l);
  Serial.println("LX ");
  
  if (((l1 == 1) && (l2 == 1) && (l3 == 1)) || tr == 1 || ltr == 'a') {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  delay(50);
}
