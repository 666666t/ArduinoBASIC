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
String progVars = "TEST=5,MEMES=8,";
/* Buffers and Program strings
wordBuffer - holds direct words read before attaching them or tokenizing, example "PRINT"
tokenBuffer - holds token before being added at once to the program, example ",L10C1PA=5"
lineBuffer - holds entire line on input, is taken apart one word at a time
basicProg - holds tokens delimited by commas, open ending, example ",L10C1PA=5,L20C2P"FOO""
progVars - holds variables created by program
subLineBuf and lastLine are just buffers for LCD display */

int currLin = 0;
int currCom = 0;
int progPoint = 0;
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
    for(int charNum = 0; charNum < lineBuffer.length(); charNum++)
    {
      tokenBuffer += lineBuffer[charNum];
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
  Serial.println("Execution Begin");
  currCom = 0;
  currLin = 0;
  String parmBuffer = "";
  bool isQuote = false;
  int parmLoc = 0;
  if(basicProg[basicProg.length() - 1] != ',') {basicProg += ',';}
  wordBuffer = "";
  for(progPoint = 1; progPoint < basicProg.length(); progPoint++)
  {
    if(basicProg[progPoint] == ',' && progPoint != 0)
    {
      runCom(currCom, parmBuffer);
      //Serial.print("Ran command ");
      //Serial.print(currCom);
      //Serial.print(" with Parameter ");
      //Serial.println(parmBuffer);
      parmBuffer = "";
      parmLoc = 0;
      currCom = 0;
      currLin = 0;
    }
    if(basicProg[progPoint] == 'L')
    {
      progPoint++;
      parmLoc = progPoint;
      while(basicProg[progPoint] != 'C')
      {
        progPoint++;
      }
      wordBuffer = basicProg.substring(parmLoc, progPoint);
      currLin = wordBuffer.toInt();
      //Serial.println(currLin);
      progPoint++;
      parmLoc = progPoint;
      while(basicProg[progPoint] != 'P')
      {
        progPoint++;
      }
      wordBuffer = basicProg.substring(parmLoc, progPoint);
      currCom = wordBuffer.toInt();
      //Serial.println(currCom);
      progPoint++;
      parmLoc = progPoint;
      while(basicProg[progPoint + 1] != ',')
      {
        progPoint++;
      }
      parmBuffer = basicProg.substring(parmLoc, progPoint + 1);
      //Serial.println(parmBuffer);
    }
  }  
  loop();
}

void runCom(int comNum, String parm)
{
  //Serial.println(parm);
  //Serial.println(comNum);
  String parmOut = "";
  if(comNum == 1)
  {
    if(parm[0] == '(')
    {
      if(parm.indexOf('+') == -1 && parm.indexOf('-') == -1 && parm.indexOf('*') == -1 && parm.indexOf('/') == -1)
      {
        int endName = parm.indexOf(')');
        String varName = parm.substring(1, endName);
        if(progVars.indexOf(varName) == -1) {SynErr();}
        else
        {
          endName = progVars.indexOf(varName);
          int varLen = 0;
          while(progVars[endName] != ',')
          {
            endName++;
            varLen++;
          }
          progVars.remove(progVars.indexOf(varName), endName + 1);
          varLen = 0;
          while(varLen < parm.length())
          {
            if(parm[varLen] != '(' && parm[varLen] != ')')
            {
              parmOut += parm[varLen]; 
            }
            varLen++;
          }

          progVars += parmOut;
          progVars += ',';
        }
      }
      else if(parm.indexOf('+') != -1)
      {
        
      }
      else if(parm.indexOf('-') != -1)
      {
        
      }
      else if(parm.indexOf('*') != -1)
      {
        
      }
      else if(parm.indexOf('/') != -1)
      {
        
      }
      
    }
    else
    {
      if(parm.indexOf('+') == -1 && parm.indexOf('-') == -1 && parm.indexOf('*') == -1 && parm.indexOf('/') == -1)
      {
        String parmName = parm.substring(0, parm.indexOf('='));
        if(progVars.indexOf(parmName) != -1) {SynErr();}
        else
        {
          progVars += parm;
        }
      } 
    }
    //Serial.print("Declared Variable ");
    //Serial.println(parmOut);
    //Serial.print("Current Varset: ");
    //Serial.println(progVars);
  }
  
  else if(comNum == 2)
  {
    if(parm[0] == '(')
    {
      int i = 1;
      
      while(parm[i] != ')')
      {
        parmOut += parm[i];
        i++;
      }
      
      i = progVars.indexOf(parmOut);
      if(i != -1)
      {
        i += (parmOut.length() + 1);
        parmOut = "";
        while(progVars[i] != ',' && i < progVars.length())
        {
          parmOut += progVars[i];
          i++;
        }
        lastLine = subLineBuf;
        lcd.clear();
        lcd.print(lastLine);
        lcd.setCursor(0,1);
        lcd.print(parmOut);
        subLineBuf = parmOut;
      }
      else
      {
        SynErr();
      }
    }
    
    else if(parm[0] == '"')
    {
      int i = 1;

      while(parm[i] != '"')
      {
        parmOut += parm[i];
        i++;
        if(i >= parm.length()) {SynErr();}
      }
      lastLine = subLineBuf;
      lcd.clear();
      lcd.print(lastLine);
      lcd.setCursor(0,1);
      lcd.print(parmOut);
      subLineBuf = parmOut;
      
    }
    else{SynErr();}
  }
  
  else if(comNum == 3)
  {
    parmOut = 'L' + parm;
    int i = basicProg.indexOf(parmOut);
    if(i != -1)
    {
      progPoint = i;
    }
    else {SynErr();}
  }
}

void SynErr()
{
  runCom(2, "\"SYNTAX ERROR\"");
  while(1){}
}
