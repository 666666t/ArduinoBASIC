#include <PS2Keyboard.h>
//using the PS2Keyboard library for simplicity

const int DP = 8;
const int IP = 3;
//Data Pin and Interrupt Pin

PS2Keyboard keyboard;
//Keyboard object

String wordBuffer = "";
String tokenBuffer = "";
String lineBuffer = "";
String basicProg = "";
String progVars = "";
/* Buffers and Program strings
wordBuffer - holds direct words read before attaching them or tokenizing, example "PRINT"
tokenBuffer - holds token before being added at once to the program, example ",L10C1PA=5"
lineBuffer - holds entire line on input, is taken apart one word at a time
basicProg - holds tokens delimited by commas, open ending, example ",L10C1PA=5,L20C2P"FOO""
progVars - holds variables created by program */

int currentLine = 0;
int currCom = 0;
/* Basic Variables for Execution and Tokenizing
currentLine - Stores current line being executed by program
currCom - Stores current command number */


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
  // used solely for differentiating between RUN and a lined command
  
  if(lineBuffer.length() == 3) {CheckRun();}
  else if(isDigit(firstChar)) {NumRead();}
  TokenizeCom();
  InsParm(currCom);
  
  basicProg += tokenBuffer;

  Serial.println(currCom);
  Serial.println(wordBuffer);
  Serial.println(lineBuffer);
  Serial.println(basicProg);

  tokenBuffer = "";
  lineBuffer = "";
  wordBuffer = "";
}

void RunProg()
{
  Serial.println("PROGRAM IS RUNNING");
  loop();
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
      lineBuffer.remove(0, (charNum + 1));
      break;
    }
  }

  tokenBuffer += ComToCNum(wordBuffer);
  String comBuf = tokenBuffer.substring(tokenBuffer.length() - 1);
  currCom = comBuf.toInt();
}



String ComToCNum(String commandGiven)
{
  commandGiven.toUpperCase();
  if(commandGiven == "LET") {return "1";}
  else if(commandGiven == "PRINT") {return "2";}
  else if(commandGiven == "GOTO") {return "3";}
  else if(commandGiven == "IF") {return "4";}
  else if(commandGiven == "THEN") {return "5";}
  else if(commandGiven == "FOR") {return "5";}
  else if(commandGiven == "TO") {return "6";}
  else if(commandGiven == "STEP") {return "7";}
  else if(commandGiven == "NEXT") {return "8";}
  else if(commandGiven == "REM") {return "9";}
}



void InsParm(int currCom)
{
  tokenBuffer += 'P';

  
  if(currCom == 1)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 2)
  {
    bool quotesOpen = false;
    
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] == '"' && quotesOpen == false)
      {
        quotesOpen = true;
        tokenBuffer += lineBuffer[charNum];
      }
      else if(lineBuffer[charNum] == '"' && quotesOpen == true)
      {
        tokenBuffer += lineBuffer[charNum];
        break;
      }
      else if(quotesOpen == true) {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 3)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 4)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 5)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 6)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 7)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 8)
  {
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      if(lineBuffer[charNum] != ' ') {tokenBuffer += lineBuffer[charNum];}
    }
  }
  else if(currCom == 9)
  {
    
  }
}




