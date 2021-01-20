int analogInput = A1;

float vout = 0.0;
float vin = 0.0;

float R1 = 30000.0;
float R2 = 7500.0;

int value = 0;

void setup() {
  pinMode(analogInput, INPUT);

  Serial.begin(9600);
  Serial.println("DC VOLTMETER");
  delay(1000);
}
void loop() {

  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  Serial.print("INPUT Voltage= ");
  Serial.println(vin, 2);
  delay(100);

}

