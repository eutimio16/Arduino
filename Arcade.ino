 
 // Declaramos los pins de salida para los LED
  const int led_rojo = 2;         
  const int led_azul = 3;
  const int led_amarillo = 4;
  const int led_verde = 5;
  
 // buzzer
  const int zumbador = 6;  
  
 // Declaramos los pins de salida para los botones
  const int boton_rojo = 9;      
  const int boton_azul = 10;
  const int boton_amarillo = 11; 
  const int boton_verde = 12;   

  long sequence[20];             // Array que alberga la secuencia
  int contador = 0;              // Contador
  long input = 5;                // Indicador de boton pulsado
  int wait = 500;                // Retraso segun la secuencia se incrementa
  int puntuacion_maxima = 20;    // Puntuación máxima donde acaba el juego 

 // Declaramos algunas variables para los efectos musicales
  int length = 15;                  // Numero de notas de la melodia
  char notes[] = "ccggaagffeeddc "; // Notas de la melodia (cada letra es una nota distinta)
  int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  // Duracion de cada tono en un array
  int tempo = 100;  //Tempo de la melodia


  
  void setup() {
 // Configuramos los pines de los leds y del zumbador como salidas
  pinMode(led_rojo, OUTPUT);      
  pinMode(led_verde, OUTPUT); 
  pinMode(led_amarillo, OUTPUT); 
  pinMode(led_azul, OUTPUT); 
  pinMode(zumbador, OUTPUT);
    
 // Configuramos los pines de los botones como entradas
  pinMode(boton_rojo, INPUT);    
  pinMode(boton_verde, INPUT);
  pinMode(boton_amarillo, INPUT);
  pinMode(boton_azul, INPUT);
    
 // Iniciamos las resistencias PullUp internas para los botones
  digitalWrite(boton_rojo, HIGH);
  digitalWrite(boton_verde, HIGH);
  digitalWrite(boton_amarillo, HIGH);
  digitalWrite(boton_azul, HIGH);
    
  // Hacemos que suene la melodia al arrancar el Arduino    
  felicitacion();
  }
  
 
 
  void loop() {
  mostrar_secuencia();  // Reproduce la sequencia
  leer_secuencia();     // Lee la sequencia
  delay(1000);          // Espera 1 segundo
  }
  
  
  
 // Funcion para definir las notas y sus frecuencias
  void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  for (int i = 0; i < 8; i++) {
     if (names[i] == note) {
       playtone(tones[i], duration);
     }
  }
  }



 // Funcion para definir las notas segun la duración y el tono
  void playtone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone *2) {
      digitalWrite(zumbador, HIGH);
      delayMicroseconds(tone);
      digitalWrite(zumbador, LOW);
      delayMicroseconds(tone);
    }
  }
     
  
 
 // Funciones para encender los leds y reproducir el tono correspondiente
  void flash_rojo() {
  digitalWrite(led_rojo, HIGH);
  playtone(2273,wait);            
  digitalWrite(led_rojo, LOW);
  }
  
  void flash_azul() {
  digitalWrite(led_azul, HIGH);
  playtone(1700,wait);            
  digitalWrite(led_azul, LOW);
  }
  
  void flash_amarillo() {
  digitalWrite(led_amarillo, HIGH);
  playtone(1275,wait);             
  digitalWrite(led_amarillo, LOW);
  } 
  
  void flash_verde() {
  digitalWrite(led_verde, HIGH);
  playtone(1136,wait);             
  digitalWrite(led_verde, LOW);
  }
  
  

 // Funcion para mostrar que botón se tenia que pulsar en caso de error del jugador
  void mostrar_boton_correcto(long led) {
    switch (led) {
        case 0:
          flash_rojo();
          break;
        case 1:
          flash_verde();
          break;
        case 2:
          flash_amarillo();
          break;
        case 3:
          flash_azul();
          break;
      }
      delay(50);
  }
 
 
 
 // Función que reproduce la canción al arrancar el arduino y para el juego cuando se llega a la puntuacion maxima
  void felicitacion() {
  digitalWrite(led_rojo, HIGH);       
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_amarillo, HIGH);
  digitalWrite(led_azul, HIGH);
   
  for (int i = 0; i < length; i++) {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); // rest
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   delay(tempo / 2); 
  }
   
  delay(1000);   
  digitalWrite(led_rojo, LOW);      
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarillo, LOW);
  digitalWrite(led_azul, LOW);
  resetcontador();                    
  }
    
 // Reseteamos contadores
  void resetcontador() {
  contador = 0;
  wait = 500;
  }
 
  
  
 // Funcion para crear y reproducir los patrones
  void mostrar_secuencia() {

 // Con esto hacemos que la función Random sea aun mas aleatoria
  randomSeed(analogRead(8));
    
  sequence[contador] = random(4);       
    for (int i = 0; i < contador; i++) {  
      mostrar_boton_correcto(sequence[i]);             
    }
  wait = 500 - (contador * 15);        
  contador++;                          
  }
 
 
 
  // Funcion para leer los botones que pulsa el jugador
 void leer_secuencia() {
   for (int i=1; i < contador; i++) {              
      while (input==5){                          
        if (digitalRead(boton_rojo) == LOW) {    
          input = 0;
        }
        if (digitalRead(boton_verde) == LOW) {  
          input = 1;
        }
        if (digitalRead(boton_amarillo) == LOW) {
          input = 2;
        }
        if (digitalRead(boton_azul) == LOW) {   
          input = 3;
        }
      }
    
  if (sequence[i-1] == input) {              
        mostrar_boton_correcto(input);                           
        if (i == puntuacion_maxima) {                        
          felicitacion();                        
        }
      }
        else {
          playtone(4545,1500);                  
          delay(500);
          mostrar_boton_correcto(sequence[i-1]);                 
          mostrar_boton_correcto(sequence[i-1]);                 
          mostrar_boton_correcto(sequence[i-1]);
          delay(1000);
          felicitacion();
          resetcontador();                          
      } 
    input = 5;                                   
    }
  }  
