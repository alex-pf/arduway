int  REL = 13;
bool flag1=true;

class MyVector {
  unsigned long oldTime;
  int repCount;
  int iterator;
  int repInterval;
  int vId;
  boolean theEnd = false;

public:
  MyVector(int interval, int rcount, int id){
    oldTime = 0;
    repCount = rcount;
    iterator = 0;
    repInterval = interval;
    vId = id;
  }

  void Step(unsigned long curMill){
    if(flag1){
      flag1 = !flag1;
      if(!theEnd){
        if(curMill-oldTime>repInterval){
          if(++iterator==repCount){
            theEnd=true;
            Serial.print("I'm finished ");
            Serial.print(vId);
            Serial.print(" counter = ");
            Serial.println(iterator);
            return;
          }
          else{
            oldTime=curMill;
            Serial.print("Ping ");
            Serial.print(vId);
            Serial.print(" oldTime ");
            Serial.print(oldTime);
            Serial.print(" Time ");
            Serial.print(curMill);
            Serial.print(" counter = ");
            Serial.println(iterator);
          }
        }
      }
      flag1 = !flag1;
    }
  }
};

MyVector *vv1 = new MyVector(5000,10,1);
MyVector *vv2 = new MyVector(3000,20,2);


void setup(){
  delay(5000); 
  Serial.begin(9600);
  //Serial.print('Ping go!');
  // Timer0 
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
} 

SIGNAL(TIMER0_COMPA_vect){
  unsigned long currentMillis = millis();
  vv1->Step(currentMillis);
  vv2->Step(currentMillis);
}

void loop(){
  
}

