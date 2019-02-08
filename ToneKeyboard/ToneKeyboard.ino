#include <LiquidCrystal.h>
int noteStorage[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int storageAmt = 0;
bool newNote=true;
LiquidCrystal lcd (12,11,10,9,7,1);
void clearStorage(){
  for(int i = 0;i<20;i++){
    noteStorage[i]=0;
  }
  storageAmt=0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT); //RS
  pinMode(11, OUTPUT); //E
  pinMode(10, OUTPUT); //D4
  pinMode(9, OUTPUT); //D5
  pinMode(7, OUTPUT); //D6
  pinMode(1, OUTPUT); //D7
  pinMode(A0, OUTPUT); //red led
  pinMode(A1, OUTPUT); //yellow led
  pinMode(A2, OUTPUT); //green led
  pinMode(A3, OUTPUT); //blue led
  pinMode(8, OUTPUT); //speaker
  pinMode(6, INPUT); //replay button
  pinMode(5, INPUT); //C button
  pinMode(4, INPUT); //D button
  pinMode(3, INPUT); //E button
  pinMode(2, INPUT); //F button
  lcd.begin(16,2);
  lcd.print("Note:");
}
void printNote(int hz){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Note:");
  lcd.setCursor(0,1);
  if(hz==349)
    lcd.print("F (349Hz)");
  else if(hz==330)
    lcd.print("E (330Hz)");
  else if(hz==294)
    lcd.print("D (294Hz)");
  else if(hz==262)
    lcd.print("C (262Hz)");
}
void blueNote(int dur){
  digitalWrite(A3,HIGH);
  digitalWrite(A2,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A0,LOW);
  tone(8,349,dur);
}
void greenNote(int dur){
  digitalWrite(A3,LOW);
  digitalWrite(A2,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A0,LOW);
  tone(8,330,dur);
}
void yellowNote(int dur){
  digitalWrite(A3,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(A0,LOW);
  tone(8,294,dur);
}
void redNote(int dur){
  digitalWrite(A3,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A0,HIGH);
  tone(8,262,dur);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(6)==HIGH&&digitalRead(5)==HIGH){ //if both replay and left-most button pushed, reset memory
    clearStorage();
    tone(8,220,1500); //reset tone
    digitalWrite(A3,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A0,HIGH);
    lcd.clear();
    lcd.print("Resetting stored");
    lcd.setCursor(0,1);
    lcd.print("song...");
    delay(1500);
    lcd.clear();
  }
  
  if(digitalRead(6)==HIGH){ //replay
    for(int i = 0;noteStorage[i]!=0;i++){
      if(noteStorage[i]==1){
        blueNote(500);
        printNote(349);
        delay(500);        
      }
      if(noteStorage[i]==2){
        greenNote(500);
        printNote(330);
        delay(500);        
      }
      if(noteStorage[i]==3){
        yellowNote(500);
        printNote(294);
        delay(500);
      }
      if(noteStorage[i]==4){
        redNote(500);
        printNote(262);
        delay(500);
      }
    }
    newNote=false;
  }
  else if(digitalRead(2)==HIGH){ //F,Blue,349hz
    blueNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 1;
      newNote=false;
      storageAmt++;
      printNote(349);
    }
  }
  else if(digitalRead(3)==HIGH){//E,Green,330
    greenNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 2;
      newNote=false;
      storageAmt++;
      printNote(330);
    }
  }
  else if(digitalRead(4)==HIGH){//D,Yellow,294hz
    yellowNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 3;
      newNote=false;
      storageAmt++;
      printNote(294);
    }
  }
  else if(digitalRead(5)==HIGH){//C,Red,262hz
    redNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 4;
      newNote=false;
      storageAmt++;
      printNote(262);
    }
  }
  else { //no buttons pressed, turn off LEDs and reset note bool
    digitalWrite(A3,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A1,LOW);
    digitalWrite(A0,LOW);
    if(!newNote){
      lcd.clear();
      lcd.print("Note:");
      newNote=true;
    }
  }
}
