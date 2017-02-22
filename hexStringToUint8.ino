#include <stdlib.h> // String manipulator

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println("init ok");
}

void loop() {

Serial.println(hexStringToString("68656c6c6f"));
delay(3000);
}

String hexStringToString(String hexString) {
  uint_8 cInt[6];
  int k=0;
  for (int i=0;i< hexString.length();i=i+2){
    char hexLetterBuf[3];
    String hexLetter=hexString.substring(i,i+2);
    hexLetter.toCharArray(hexLetterBuf,3);
    cInt[k]=strtol(hexLetterBuf, 0, 16);
    k++;
  }
  return textString;
}
