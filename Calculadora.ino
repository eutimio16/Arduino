 #include <LiquidCrystal.h> //import lcd library
#include <Keypad.h> //import keypad library

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'X'},
  {'4', '5', '6', '+'},
  {'7', '8', '9', '-'},
  {'*', '0', '=', '/'}
};

byte rowPins[ROWS] = {
  0 ,1 ,2 ,3}; //connect keypad ROW1, ROW2, ROW3, ROW4 to these arduino pins
byte colPins[COLS] = {
  4, 5, 6, 7}; //connect keypad COL1, COL2, COL3, COL4 to these arduino pins

//create the keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//variables declaration
boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1, num2;
int ans;
char op;

void setup(){
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Semana i");
  delay(2500);
  lcd.clear(); //clears the LCD screen and positions the cursor in the upper-left corner. 
}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (valOnePresent != true){
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (valOnePresent == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')){
    if (valOnePresent == false){
      valOnePresent = true;
      op = key;
      lcd.setCursor(15,0); //operator on right corner
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      ans = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      ans = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      ans = num1.toInt() * num2.toInt();
    }
    else if (op == '/'){
      ans = num1.toInt() / num2.toInt();
    }    
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
  }
  else if (key != NO_KEY && key == 'X'){
    lcd.clear();
    valOnePresent = false;
    final = false;
    num1 = "";
    num2 = "";
    ans = 0;
    op = ' ';
  }
}
