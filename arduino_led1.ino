#define ledA 13  
#define ledR 12  
#define ledV 11     

// Estado inicial del LED  (apagado)
bool estadoVerde = LOW;      
bool estadoRojo = LOW;       
bool estadoAmarillo = LOW;   

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    switch (comando) {
      case '1':
      case '2':
      // Alternar el estado del LED verde
        estadoVerde = !estadoVerde;  
        controlarLuz(ledV, estadoVerde);
        break;
      case '3':
      case '4':
      // Alternar el estado del LED rojo
        estadoRojo = !estadoRojo;  
        controlarLuz(ledR, estadoRojo);
        break;
      case '5':
      case '6':
      // Alternar el estado del LED amarillo
        estadoAmarillo = !estadoAmarillo;  
        controlarLuz(ledA, estadoAmarillo);
        break;
      case '7':
      case '8':
      // cambia el estado de todas las luces
		EncenderTodasLasLuces();  
        break;
      case '9':
      // Activar modo intermitente
        modoIntermitente();  
        break;
      default:
        Serial.println("Comando invalido");
        break;
    }
  }
}

//controla el estado de una luz conectada a un pin específico
void controlarLuz(int pin, int estado) {
  digitalWrite(pin, estado);
}

//enciende todas las luces 
void EncenderTodasLasLuces() {
  //si todas están encendidas las apaga, si no las enciende
  int nuevoEstado = (estadoVerde == HIGH && estadoRojo == HIGH && estadoAmarillo == HIGH) ? LOW : HIGH;

  // se asigna el nuevo estado en todas las luces
  digitalWrite(ledV, nuevoEstado);
  digitalWrite(ledR, nuevoEstado);
  digitalWrite(ledA, nuevoEstado);

  // actualiza los estados internos
  estadoVerde = nuevoEstado;
  estadoRojo = nuevoEstado;
  estadoAmarillo = nuevoEstado;
}


//controla el estado de varias luces al mismo tiempo
void controlarTodasLasLuces(int estado) {
  digitalWrite(ledA, estado);
  digitalWrite(ledR, estado);
  digitalWrite(ledV, estado);
}


//hace que todas las luces parpadeen en modo intermitente
void modoIntermitente() {
  for (int i = 0; i < 3; i++) {
    controlarTodasLasLuces(HIGH);
    delay(800);
    controlarTodasLasLuces(LOW);
    delay(800);
  }
}
