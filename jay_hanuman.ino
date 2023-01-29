#define rr 8
#define r 3
#define m 4
#define l 5
#define ll 7

#define l2 6
#define l1 9
#define r1 10
#define r2 11

#define led 13

#define back A0

int SPEEDR = 80;
int CORR = 20;
int CORL = 30;
int SPEEDL = 88;
int medium = 60;
int RR, R, M, L, LL, B;
int mov1 = 2, mov2 = 30,movu=14;
int backtime = 300;

void setup() {
   Serial.begin(9600);
  pinMode(ll, INPUT);
  pinMode(l, INPUT);
  pinMode(m, INPUT);
  pinMode(r, INPUT);
  pinMode(rr, INPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  pinMode(back, INPUT);
  pinMode(led, OUTPUT);

//  attachInterrupt(digitalPinToInterrupt(2),switchP,RISING);
  
//  moveforward();
//  uturn();
//  stopbot();
}



void moveforward()
 {
  //Serial.println("Moving ahead");
  analogWrite(l1, 0);
  analogWrite(l2, SPEEDL);
  analogWrite(r1, 0);
  analogWrite(r2, SPEEDR);
}

void stopbot(){
  analogWrite(l1, 0);
  analogWrite(l2, 0);
  analogWrite(r1, 0);
  analogWrite(r2, 0);

  
}
void turnleft()
{
  //Serial.println("Moving left");
  int total = 1500;
  analogWrite(l1, 0);
  analogWrite(l2, 0);
  analogWrite(r1, 0);
  analogWrite(r2, SPEEDR);
  delay(total-200);
  int c = 0;
  while((M==1 || B==0) && c<200){
    updater();
//    printArray();
    delay(1);
    c++;
  }
  Serial.println(c);
  moveback();
  delay(backtime);
  stopbot();
  delay(100);
  
}

void turnright(){
  int total = 1600;
  analogWrite(l1, 0);
  analogWrite(l2, SPEEDL);
  analogWrite(r1, 0);
  analogWrite(r2, 0);
  delay(total-200);

  int c = 0;
  while((M==1 || B==0) && c<200){
    updater();
//    printArray();
    delay(1);
    c++;
  }
  Serial.println(c);
  moveback();
  delay(backtime);
  stopbot();
  delay(100);
  
  
//  stopbot();
}

void show(String msg) {
  Serial.println(msg);
}


void uturn(){
  show("uturn");
  int total = 1400;
  analogWrite(l1, SPEEDL);
  analogWrite(l2, 0);
  analogWrite(r1, 0);
  analogWrite(r2, SPEEDR);
  delay(total-200);

  int c = 0;
  while((M==1 || B==0) && c<200){
    updater();
//    printArray();
    delay(1);
    c++;
  }
  Serial.println(c);

  moveback();
  delay(backtime);
  stopbot();
  delay(100);
//  stopbot();
}

void moveback(){
  analogWrite(l1, SPEEDL);
  analogWrite(l2, 0);
  analogWrite(r1, SPEEDR);
  analogWrite(r2, 0);
  
}
void updater()
{
  RR = digitalRead(rr);
  R = digitalRead(r);
  M = digitalRead(m);
  L = digitalRead(l);
  LL = digitalRead(ll);
  B = digitalRead(back);
}

int patternIs(String bits) {
  updater();
  int a, b, c, d, e;
  a = bits[0] - '0';
  b = bits[1] - '0';
  c = bits[2] - '0';
  d = bits[3] - '0';
  e = bits[4] - '0';
  
  if (bits[0] == 'x') {
    LL = 72;
  }
  if (bits[1] == 'x') {
    L = 72;
  }
  if (bits[2] == 'x') {
    M = 72;
  }
  if (bits[3] == 'x') {
    R = 72;
  }
  if (bits[4] == 'x') {
    RR = 72;
  }
  if (a == LL && b == L && c == M && d == R && e == RR) {
    return 1;
  }
  return 0;
}

void correct()
{
  updater();
  if(B==1 && M==0)
  {
      digitalWrite(led,HIGH);
      moveforward();    
//    show("ma kata chu");
    return;
  }
  else
  {
      digitalWrite(led,LOW); 
      if (patternIs("10011") || patternIs("10111") || patternIs("00111") || patternIs("01111")) {
//        show("CL");
//        printArray();
        correctleft();
        delay(1);
      }
      else if (patternIs("11001") || patternIs("11101") || patternIs("11100") || patternIs("11110")) {

//        show("CR");
//        printArray();
        correctright();
        delay(1);
      }
      else{
        moveforward();
      }
  }
}

void correctleft() {

  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r1, LOW);
  analogWrite(r2, SPEEDR);
}

void correctright() {
  digitalWrite(l1, LOW);
  analogWrite(l2, SPEEDL);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
}



void printArray() {
  //  Serial.print("ll: ");
  Serial.print(LL);
  //  Serial.print("l: ");
  Serial.print(L);
  //  Serial.print("m: ");
  Serial.print(M);
  //  Serial.print("r: ");
  Serial.print(R);
  //  Serial.print("rr: ");
  Serial.print(RR);
  Serial.println();
}

void moveBitForward(int timed) {
  stopbot();
//  delay(500);

//  show("Moving bit forward");
//  show((String)timed);
  int count = 0;
  moveforward();
  while (count < timed) {
//    correct();
    delay(1);
    count++;
  }
//  moveforward();
  stopbot();
//  delay(500);
}

void loop() 
{ 
// printArray();
 correct();
 
 if (patternIs("00011")) { //left Turn Detected
  
    moveBitForward(mov1);
    if (patternIs("xx000"))
    {
      show("left and right turn");
      moveBitForward(mov2);
      
      if (patternIs("11111") )
      {
        
        //T path
        show("Only left and right Turn");
        turnleft();
      }
      else
      {
        show("4 way Junction");
        turnleft();
      }
    }
    else {
      show("left Turn");
      moveBitForward(mov2+100);
//      printArray();
      if (M == 1)
      {
        show("Only left");
        turnleft();
      }
      else
      {
        show("left with Forward");
        turnleft();
        //Decide garna parne
      }
    }
  }

  else if (patternIs("11000") || patternIs("10000") || patternIs("11100")) { //right Turn Detected
    moveBitForward(mov1);
    if (patternIs("000xx"))
    {
      show("left and right turn");
      moveBitForward(mov2);
      if (patternIs("11111"))
      { 
        show("Only left and right Turn");
        turnleft();
      }
      else
      {
        show("4 way Junction");
        turnleft();
      }
    }
    else {
      show("Right Turn");
      moveBitForward(mov2);
      if (patternIs("11111"))
      {
        printArray();
        show("Only right");
        turnright();
      }
      else
      {
        show("right with Forward");
        moveforward();
      }
    }
  }

  else if(patternIs("11111") && B==1){
    moveBitForward(movu);
    updater();
    if(!patternIs("11111")){
      return;
    }
    moveBitForward(movu);
    updater();
    if(!patternIs("11111")){
      return;
    }
    show("may be a U turn");
    moveBitForward(mov2);
    updater();
    if(!patternIs("11111")){
      return;
    }
    show("got a u turn");
    uturn();
    
  }
  

 delay(1);
// stopbot();
// delay(10);
 
}
