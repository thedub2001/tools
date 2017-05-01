boolean test=false;

void setup() { 

  Serial.begin(115200);
  Serial.println();

}

void loop() {

  test=!test;

  Serial.println(test ? "test=false " : "test=true ");

  delay(2000);
}
