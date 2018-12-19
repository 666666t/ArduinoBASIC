#include <LiquidCrystal.h>
#include <PS2Keyboard.h>
//using the PS2Keyboard library for simplicity
const int RS = 12;
const int EN = 11;
const int D4 = 10;
const int D5 = 9;
const int D6 = 8;
const int D7 = 7;
const int DP = 3;
const int IP = 2;
//Data Pin and Interrupt Pin

PS2Keyboard keyboard;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
//Keyboard and LCD object

String wordBuffer = "";
String tokenBuffer = "";
String lineBuffer = "";
String subLineBuf = "";
String lastLine = "";
String basicProg = "";
String progVars = "";
/* Buffers and Program strings
wordBuffer - holds direct words read before attaching them or tokenizing, example "PRINT"
tokenBuffer - holds token before being added at once to the program, example ",L10C1PA=5"
lineBuffer - holds entire line on input, is taken apart one word at a time
basicProg - holds tokens delimited by commas, open ending, example ",L10C1PA=5,L20C2P"FOO""
progVars - holds variables created by program
subLineBuf and lastLine are just buffers for LCD display */

int currLin = 0;
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
  lcd.begin(16,2);
  lcd.cursor();
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
      lastLine = lineBuffer;
      lcd.clear();
      lcd.print(lastLine);
      lcd.setCursor(0,1);
      
      ReadAndAdd();
    } else if (c == PS2_DELETE || c == PS2_BACKSPACE) {
      lineBuffer.remove((lineBuffer.length() - 1));
      lcd.clear();
      lcd.print(lastLine);
      lcd.setCursor(0,1);
      if(lineBuffer.length() > 16) {subLineBuf = lineBuffer.substring(lineBuffer.length() - 16);}
      else {subLineBuf = lineBuffer;}
      lcd.print(subLineBuf);
    } else {
      lineBuffer += c;
      lcd.setCursor(0,1);
      if(lineBuffer.length() > 16) {subLineBuf = lineBuffer.substring(lineBuffer.length() - 16);}
      else {subLineBuf = lineBuffer;}
      lcd.print(subLineBuf);
    }
  }
}



void ReadAndAdd()
{
  char firstChar = lineBuffer[0];
  // used solely for differentiating between RUN and a line command
  
  if(lineBuffer.length() == 3) {CheckRun();}
  else if(isDigit(firstChar))
  {
    NumRead();
    TokenizeCom();
    InsParm(currCom);
  }

  
  basicProg += tokenBuffer;

  Serial.println(basicProg);

  tokenBuffer = "";
  lineBuffer = "";
  wordBuffer = "";
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

void RunProg()
{
  Serial.println("");
  Serial.println("Execution Begin");
  if(basicProg[basicProg.length() - 1] != ',') {basicProg += ',';}
  currCom = 0;
  currLin = 0;
  int tokLen = 0;
  String parmBuffer = "";
  bool isParm = false;
  int lastLoc = 0;
  for(int i = 1; i < basicProg.length(); i++)
  {
    if(basicProg[i] == ',' && !isParm && currLin > 0)
    {
      
      parmBuffer = basicProg.substring(lastLoc, i);
      runCom(currCom, parmBuffer);
      Serial.print("Command ");
      Serial.print(currCom);
      Serial.print(" at line ");
      Serial.print(currLin);
      Serial.println(" has been run");
    }

    else if(basicProg[i] == 'L' && !isParm)
    {
      lastLoc = i + 1;
      tokLen = i;
      while(basicProg[i] != 'C')
      {
        tokLen++;
        i++;
      }
      tokLen++ ;
      wordBuffer = basicProg.substring(lastLoc, tokLen);
      currLin = wordBuffer.toInt();

      
      lastLoc = i + 1;
      tokLen = i;
      while(basicProg[i] != 'P' && !isParm)
      {
        tokLen++;
        i++;
      }
      tokLen++;
      wordBuffer = basicProg.substring(lastLoc, tokLen);
      currCom = wordBuffer.toInt();

      lastLoc = i + 1;
    }
  }
  loop();
  
}


void runCom(int comNum, String parm)
{
  Serial.println(parm);
  Serial.println(comNum);
  if(comNum == 1)
  {
    if(parm[0] == '(')
    {
      for(int i = 1; i < parm.length();i++)
      {
        if(parm[i] == ')')
        {
          wordBuffer = parm.substring(1, i);
          Serial.println(wordBuffer); 
        }
      }
    }
  }
}

