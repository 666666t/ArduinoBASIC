#include <PS2Keyboard.h>

const int DP = 8;
const int IP = 3;

PS2Keyboard keyboard;
String basicProg = "";
String lineBuffer = "";
String wordBuffer = "";
String tokenBuffer = "";
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
  char firstChar = lineBuffer[0];
  if(lineBuffer.length() == 3) {CheckRun();}
  else if(isDigit(firstChar)) {NumRead();}
  TokenizeCom();
  Serial.println(basicProg);
  Serial.println(lineBuffer);
  lineBuffer = "";
}

void CheckRun()
{
  if(lineBuffer[0] != ' ')
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      wordBuffer += lineBuffer[charNum];
    }
    wordBuffer.toUpperCase();
    if(wordBuffer == "RUN")
    {
      wordBuffer = "";
      lineBuffer = "";
      basicProg += ',';
      RunProg();
    }
  }
}

void NumRead()
{
  bool stringStarted = false;
  if(lineBuffer.length() > 0 && lineBuffer[0] != ' ') {tokenBuffer += ",L";}
  for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
  {
    if(lineBuffer[charNum] != ' ')
    {
      tokenBuffer += lineBuffer[charNum];
    }
    else
    {
      lineBuffer.remove(0, (charNum + 1));
      break;
    }
  }
}

void TokenizeCom()
{
  tokenBuffer += 'C';
  for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
  {
    if(lineBuffer[charNum] != ' ')
    {
      wordBuffer += lineBuffer[charNum];
    }
    if(lineBuffer[charNum] == ' ')
    {
      break;
    }
  }

  

  basicProg += tokenBuffer;
  tokenBuffer = "";
}

void RunProg()
{
  Serial.println("PROGRAM IS RUNNING");
  loop();
}

