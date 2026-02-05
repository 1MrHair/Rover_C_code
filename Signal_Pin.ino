const int Channel1_Pin = 11;
const int Channel2_Pin = 12;
const int Channel3_Pin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Channel1_Pin, INPUT);
  pinMode(Channel2_Pin, INPUT);
  pinMode(Channel3_Pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // int Signal_Pin_Output = digitalRead(Signal_Pin);
  // Serial.println(Signal_Pin_Output);
  int Channel1 =  pulseIn(Channel1_Pin ,HIGH, 25000);
  int Channel2 =  pulseIn(Channel2_Pin ,HIGH, 25000);
  int Channel3 =  pulseIn(Channel3_Pin ,HIGH, 25000);
  Serial.print("Channel One > ");
  Serial.println(Channel1);
  delay(500);
  Serial.print("Channel Two > ");
  Serial.println(Channel2);
  delay(500);
  Serial.print("Channel Three > ");
  Serial.println(Channel3);
  delay(500);
}
