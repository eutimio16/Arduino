#include <NewPing.h>
 
/*Aqui se configuran los pines donde debemos conectar el sensor*/
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
int Valor;  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
 // pinMode(5, INPUT);  //lectura de sensonr de tierra digital

}

void loop() {

  //sensor de temperatura de suelo
  Serial.print("Sensor de Humedad valor:");  
Valor = analogRead(7);  
Serial.print(Valor);  
if (Valor <= 300)  
   Serial.println(" Encharcado");  
if ((Valor > 300) and (Valor <= 700))  
    Serial.println(" Humedo, no regar");   
if (Valor > 700)  
    Serial.println(" Seco, necesitas regar");  
delay(1000); 

      int uS = sonar.ping_median();
        // Imprimir la distancia medida a la consola serial
      Serial.print("Distancia: ");
        // Calcular la distancia con base en una constante
      Serial.print(uS / US_ROUNDTRIP_CM);
      Serial.println("cm");

      delay(1000);
}
