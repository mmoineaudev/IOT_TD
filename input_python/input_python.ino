
#define LED_BUILTIN 23 

char receivedchar;
int sensorValue;
int coef = 1;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  if(coef==1){
    sensorValue = analogRead(A0);
  }else{
    sensorValue=0;
  }
  
  Serial.println(sensorValue, DEC);
  //Serial.print("\n");
  //--
  receivedchar = Serial.read();

    if(receivedchar == '1'){
      digitalWrite(LED_BUILTIN, HIGH); 
    }if(receivedchar == '2'){
      digitalWrite(LED_BUILTIN, LOW);
    }  
 delay(1000);
}
