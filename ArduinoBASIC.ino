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
  //Give time for keyboard to init, start serial monior for debug
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
    // Checks the last keypress, adds it to the line buffer if it's a standard char, removes 1 character on backspace and pushes the line on enter
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
  
  //RUN does not go into the program, so it follows a different execution condition
  if(lineBuffer.length() == 3) {CheckRun();}
  else if(isDigit(firstChar)) {NumRead();}
  TokenizeCom();
  Serial.println(basicProg);
  Serial.println(lineBuffer);
  lineBuffer = "";
}

void CheckRun()
{
  // Input should not start with a space in any case, breaks in case of invalid syntax
  if(lineBuffer[0] != ' ')
  {
    //creates a word from the string, not necessary for RUN but consisten
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      wordBuffer += lineBuffer[charNum];
    }
    wordBuffer.toUpperCase();
    if(wordBuffer == "RUN")
    {
      //Clears All Used Buffers, Runs Program
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
  //Adds beginning of token if string starts with proper syntax
  if(lineBuffer.length() > 0 && lineBuffer[0] != ' ') {tokenBuffer += ",L";}
  //Creates a string consisting of the numbers up to the first space
  for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
  {
    if(lineBuffer[charNum] != ' ')
    {
      //Adds Number to Token Buffer
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
  //Begins Token Addition to String, Space Checking Not Needed Because NumRead Removes Itself + Spaces
  tokenBuffer += 'C';
  //Create Word From Next Command
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
//TODO: ADD TOKEN TRANSLATIONS
  

  basicProg += tokenBuffer;
  tokenBuffer = "";
}

void RunProg()
{
  Serial.println("PROGRAM IS RUNNING");
  loop();
}

