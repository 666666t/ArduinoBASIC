#include <PS2Keyboard.h>

const int DP = 8;
const int IP = 5;

PS2Keyboard keyboard;
String basicProg = "";
String lineBuffer = "";
int currentLine = 0;


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  keyboard.begin(DP, IP);
  Serial.begin(9600);
  Serial.println("Basic Interpreter v0.0.1");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (keyboard.available()) 
  {
    char c = keyboard.read();

    if (c == PS2_ENTER) {
      ReadAndAdd();
    } else if (c == PS2_DELETE || c == PS2_BACKSPACE) {
      lineBuffer.remove((lineBuffer.length() - 1));
    }
  }
}


void ReadAndAdd()
{
  
}

