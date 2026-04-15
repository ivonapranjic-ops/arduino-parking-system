#include <LiquidCrystal.h>
// LCD pinovi: RS, E, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Ultrazvučni senzor
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 14;
const int echoPin2 = 13;
// Konstante i varijable
const int totalSpots = 4;
int occupiedSpots = 0;
const int detectionThreshold = 10;
bool vehicleDetected1 = false;
bool vehicleDetected2 = false;
void setup() {
lcd.begin(16, 2);
lcd.print("Slobodno: ");
lcd.print(totalSpots - occupiedSpots);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
Serial.begin(9600);
}
void loop() {
int distance1 = getDistance1();
if (distance1 > 0 && distance1 < detectionThreshold) {
if (!vehicleDetected1) {
vehicleDetected1 = true;
if (occupiedSpots < totalSpots) {
occupiedSpots++;
updateLCD();
}
}
} else {
if (vehicleDetected1) {
vehicleDetected1 = false;
}
}
delay(50);
int distance2 = getDistance2();
if (distance2 > 0 && distance2 < detectionThreshold) {
if (!vehicleDetected2) {
vehicleDetected2 = true;
if (occupiedSpots > 0) {
occupiedSpots--;
updateLCD();
}
}
} else {
if (vehicleDetected2) {
vehicleDetected2 = false;
}
}
delay(50);
}
int getDistance1() {
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
long duration1 = pulseIn(echoPin1, HIGH);
int distance1 = duration1 * 0.034 / 2;
return distance1;
}
int getDistance2() {
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
long duration2 = pulseIn(echoPin2, HIGH);
int distance2 = duration2 * 0.034 / 2;
return distance2;
}
void updateLCD() {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Slobodno: ");
lcd.print(totalSpots - occupiedSpots);
lcd.setCursor(0, 1);
lcd.print("Zauzeto: ");
lcd.print(occupiedSpots);
}