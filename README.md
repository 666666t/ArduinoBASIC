# ArduinoBASIC
Incredibly Simple and Cheaply-Written BASIC Interpreter for Arduino

STATUS AS OF 2019-01-01: PRINT/GOTO Working, LET Only Supports Declaration and Direct Changes, No Math

This project was/is made for a HS-level final project for a digital electronics class.
The interpreter is intended to follow the pattern of receiving each string line-by-line via PS/2 keyboard input, searching an inputted line to tokenize the command and delimit each command before inserting it into a string, which, upon execution, will simply iterate through the string and execute the proper instructions accordingly.

Example:

-10 LET A = 5  
-20 PRINT A  
-30 PRINT "Looping String, Complete with symbols"  
-40 GOTO 30  
 
assuming each line is separated by Linebreaks/Enter presses, and the dashes at the start of each line are not present, 
the example would be tokenized and compressed into  

',L10C01PA=5,L20C03P(A),L30C03P"Looping String, Complete with symbols",L40C02P30'.

Each command is made up of a set of parts, and is delimited by a comma between commands.

-L<x> marks the line number of each command, and is included for commands like GOTO
  
-C<x> represents the tokenized commands, which, while not yet determined in final, use C01 for LET, C02 for GOTO, and C03 for PRINT in the example.
  
-P<x> represents any parameters a command may take, and the compression may vary based on the command. For Example, LET's parameter takes text to the left of an = sign to a variable name, and numbers to the right as the data.
variables used inside the compressed string will use (<var>) as a notation for readability.

Operations use LET for variable changing operations (ex. LET (a) = ((b) + (c)) or LET (a) = (a) + (b) ), and basic operations are handled directly (ex. PRINT ((a) + (b)). Supported mathematic operations will include: + - * / %

Included commands will be:

LET - Variable Assignment/Modification; Syntax Example: LET foo = 5; LET (foo) = 10   
PRINT - Visual Output Command; Syntax Example: PRINT "TEXT"  
GOTO - Program Jump Command; Syntax Example: GOTO 10    
IF - Conditional Statement; Syntax Example: IF (foo) < (bar)
THEN - Conditional Response Statement; Every Line Contained by an IF Needs THEN; Syntax Example: THEN PRINT "TEXT" 
FOR - Loop Of Given Length; Syntax Example: FOR X = -2  
TO - Provides Range of Values for Loop, Inclusive; Syntax Example: TO x = 5  
STEP - Provides Interval of Values for Loop; Syntax Example; STEP 1
NEXT - Provides Point for Loop to Restart and increments X by STEP; Syntax Example: FOR X = -2 TO 2 STEP 1 <commands> NEXT  
REM - Provides Line That is Not Executed, Comment line: Syntax Example: REM <comment>  
