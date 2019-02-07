int noteStorage[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int storageAmt = 0;
bool newNote=true;

void clearStorage(){
  for(int i = 0;i<20;i++){
    noteStorage[i]=0;
  }
  storageAmt=0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT); //red led
  pinMode(11, OUTPUT); //yellow led
  pinMode(10, OUTPUT); //green led
  pinMode(9, OUTPUT); //blue led
  pinMode(8, OUTPUT); //speaker
  pinMode(6, INPUT); //replay button
  pinMode(5, INPUT); //C button
  pinMode(4, INPUT); //D button
  pinMode(3, INPUT); //E button
  pinMode(2, INPUT); //F button
  
}

void blueNote(int dur){
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  tone(8,349,dur);
}
void greenNote(int dur){
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  tone(8,330,dur);
}
void yellowNote(int dur){
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  tone(8,294,dur);
}
void redNote(int dur){
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  tone(8,262,dur);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(6)==HIGH&&digitalRead(5)==HIGH){
    clearStorage();
    tone(8,220,500); //reset tone
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    delay(500);
  }
  
  if(digitalRead(6)==HIGH){ //replay
    for(int i = 0;noteStorage[i]!=0;i++){
      if(noteStorage[i]==1){
        blueNote(500);
        delay(500);
      }
      if(noteStorage[i]==2){
        greenNote(500);
        delay(500);
      }
      if(noteStorage[i]==3){
        yellowNote(500);
        delay(500);
      }
      if(noteStorage[i]==4){
        redNote(500);
        delay(500);
      }
    }
  }
  else if(digitalRead(2)==HIGH){ //F,Blue
    blueNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 1;
      newNote=false;
      storageAmt++;
    }
  }
  else if(digitalRead(3)==HIGH){//E,Green
    greenNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 2;
      newNote=false;
      storageAmt++;
    }
  }
  else if(digitalRead(4)==HIGH){//D,Yellow
    yellowNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 3;
      newNote=false;
      storageAmt++;
    }
  }
  else if(digitalRead(5)==HIGH){//C,Red
    redNote(20);
    if(storageAmt<20&&newNote){
      noteStorage[storageAmt] = 4;
      newNote=false;
      storageAmt++;
    }
  }
  else { //no buttons pressed, turn off LEDs and reset note bool
    newNote=true;
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }
}
