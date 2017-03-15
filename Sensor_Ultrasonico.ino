long tiempo;
int disparador = 7;   // triger
int entrada = 8;      // echo
float distancia;

int ledNaranja=6;  //leds
int ledVerde=5;
int ledAmarillo=4;
int pushbutton=3;
int val=0;

void setup(){
  pinMode(ledAmarillo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledNaranja,OUTPUT);

  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);

  pinMode(pushbutton, INPUT);
  
  Serial.begin(9600);
}
void loop(){
  // lanzamos un pequeño pulso para activar el sensor
  
  digitalWrite(disparador, HIGH);
  delayMicroseconds(10);
  digitalWrite(disparador, LOW);
  tiempo = (pulseIn(entrada, HIGH)/2); 
  distancia = float(tiempo * 0.0343);

   val = digitalRead(pushbutton);

 
  if (val == HIGH) { 
  
  if(distancia <= 15.0){
    digitalWrite(ledAmarillo,HIGH);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledNaranja,LOW);
    }
    else if(distancia >15.0 && distancia <=30.0 ){
    digitalWrite(ledAmarillo,LOW);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledNaranja,HIGH);
      
      }
      else{
         digitalWrite(ledAmarillo,LOW);
         digitalWrite(ledVerde,HIGH);
         digitalWrite(ledNaranja,LOW);
        }
  }
    
  else{
         digitalWrite(ledAmarillo,LOW);
         digitalWrite(ledVerde,LOW);
         digitalWrite(ledNaranja,LOW);
    
    }
   
  // y lo mostramos por el puerto serie una vez por segundo
  Serial.println(distancia);
  delay(1000);
}
