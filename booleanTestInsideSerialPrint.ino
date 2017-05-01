boolean test=false;

void setup() { 
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  test=!test;
  Serial.println(test ? "test=true " : "test=false ");
  delay(2000);
}
