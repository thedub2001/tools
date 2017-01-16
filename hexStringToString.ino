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
  String textString="";
  for (int i=0;i< hexString.length();i=i+2){
    char hexLetterBuf[3];
    String hexLetter=hexString.substring(i,i+2);
    hexLetter.toCharArray(hexLetterBuf,3);
    textString+=char(strtol(hexLetterBuf, 0, 16)); // Strange but working !
  }
  return textString;
}
