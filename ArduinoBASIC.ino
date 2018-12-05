#include <PS2Keyboard.h>

const int DP = 8;
const int IP = 3;

PS2Keyboard keyboard;
String basicProg = "";
String lineBuffer = "";
String wordBuffer = "";
int currentLine = 0;
int spaceNum = 0;


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  keyboard.begin(DP, IP);
  Serial.begin(9600);
  Serial.println("Basic Interpreter v0.0.1");
}

void loop() {
  // put your main code here, to run repeatedly:
KeyboardLoop();
}

void KeyboardLoop()
{
  if (keyboard.available()) 
  {
    char c = keyboard.read();

    Serial.print(c);
    if (c == PS2_ENTER) {
      Serial.println("");
      ReadAndAdd();
    } else if (c == PS2_DELETE || c == PS2_BACKSPACE) {
      lineBuffer.remove((lineBuffer.length() - 1));
    } else {
      lineBuffer += c;
    }
  }
}

void ReadAndAdd()
{
  spaceNum = 0;
  basicProg += ',';
  for(int charNum = 0; charNum <= lineBuffer.length(); charNum++)
  {
    if(lineBuffer[charNum] != ' ')
    {
      wordBuffer += lineBuffer[charNum];
    }
    else if(lineBuffer[charNum] == ' ')
    {
      TokenizeCom(charNum);
      Serial.println(wordBuffer);
      Serial.println(basicProg);
      break;
    }
  }

  lineBuffer = "";
}

void TokenizeCom(int charNum)
{
  
}

