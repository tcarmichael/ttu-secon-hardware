int pinYellow = 8;
int pinRed = 9;
int pinBlue = 10;
int pinGreen = 11;
const int MAX_SEQUENCE = 32;
int sequence[MAX_SEQUENCE];

int current = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinYellow, INPUT);
  pinMode(pinRed, INPUT);
  pinMode(pinBlue, INPUT);
  pinMode(pinGreen, INPUT);
  return;
  for (current = 0; current < MAX_SEQUENCE; current++) {
    // Wait for Simon sequence
    //Serial.println("Waiting for Simon");
    for (int i = 0; i < current; i++) {
      // Ignore color
      get_color();
    }
    
    Serial.println("Waiting for color");
    sequence[current] = get_color();
    
    play_sequence(current);
    Serial.println();
    
    // Wait for user sequence
    Serial.println("Wait for user");
    for (int i = 0; i < current + 1; i++) {
      get_color();
    }
    //Serial.println(current);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int col = 0;
  col = get_color();
  Serial.println(col);
}

  int get_color() {
  
  int redValue = 0, blueValue = 0, yellowValue = 0, greenValue = 0;
  
  for(int i = 0; i < 1000; i++) {
    int _redValue = digitalRead(pinRed);
    int _blueValue = digitalRead(pinBlue);
    int _yellowValue = digitalRead(pinYellow);
    int _greenValue = digitalRead(pinGreen);
    
    if (_redValue == 0) {
      //Serial.print("RED");
      redValue++;
    }
    if (_blueValue == 0) {
      //Serial.print("BLUE");
      blueValue++;
    }
    if (_yellowValue == 0) {
      //Serial.print("YELLOW");
      yellowValue++;
    }
    if (_greenValue == 0) {
      //Serial.print("GREEN");
      greenValue++;
    }
    
    delayMicroseconds(100);

  }
  
  
  int color = -1;
/*    Serial.print("yellow: ");
    Serial.print(yellowValue);
    Serial.print(" red: ");
    Serial.print(redValue);
    Serial.print(" blue: ");
    Serial.print(blueValue);
    Serial.print(" green: ");
    Serial.println(greenValue);
*/
    
    // 1000 means really colored, 1 means almost nada, 0 means absolutely nothing
    if (redValue > 750) {
      //Serial.print("RED");
      color = 1;
    }
    else if (blueValue > 750) {
      //Serial.print("BLUE");
      color = 2;
    }
//    else if (yellowValue == 0 && greenValue == 0) {
//      //Serial.print("YELLOW");
//      color = 3;
//    }
    else if (yellowValue > 750) {
      //Serial.print("YELLOW");
      color = 3;
    }
    else if (greenValue > 750) {
      //Serial.print("GREEN");
      color = 4;
    }

    
    
    
    return color;
}

void play_sequence(int curr) {
  for (int i = 0; i <= curr; i++) {
    switch (sequence[i]) {
      case 1:
        press_red();
        break;
      case 2:
        press_blue();
        break;
      case 3:
        press_yellow();
        break;
      case 4:
        press_green();
        break;
    }
  }
}

void press_red() {
  Serial.print("RED ");
}

void press_blue() {
  Serial.print("BLUE ");
}

void press_yellow() {
  Serial.print("YELLOW ");
}

void press_green() {
  Serial.print("GREEN ");
}
