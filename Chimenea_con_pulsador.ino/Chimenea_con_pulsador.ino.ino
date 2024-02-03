// Codigo escrito por Adrian Lara para Kamikaze Soluciones Electronicas.

#define MOTOR 3  // Ajusta el pin D3 para alimentar MOTOR atraves del Transistor TIP122
#define BUTTON_PIN 2  // Ajusta el pin D2 del pulsador para cambio de Estado

unsigned long tiempoAnterior = 0;
const unsigned long tiempoEncendido = 120000;  // 2 minutos en milisegundos
const unsigned long tiempoApagado = 300000;    // 5 minutos en milisegundos
boolean estadoMotor = HIGH;
boolean cambioRutina = false;

void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configura el pin D2 del pulsador como entrada con pull-up
  digitalWrite(MOTOR, estadoMotor);  // Inicia encendido del MOTOR
}

void loop() {
  unsigned long tiempoActual = millis();

  // Verifica el estado del pulsador
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Pulsador presionado, marca el cambio de rutina
    cambioRutina = true;
    delay(50);  // Anti-rebote (puedes ajustar este valor según sea necesario)
  }

  // Cambio de rutina si el pulsador fue presionado
  if (cambioRutina) {
    cambioRutina = false;  // Reinicia la marca de cambio de rutina
    tiempoAnterior = tiempoActual;  // Reinicia el tiempo para la nueva rutina
    estadoMotor = HIGH;  // Enciende el MOTOR de manera continua
    digitalWrite(MOTOR, estadoMotor);
  } else {
    // Rutina original
    if (estadoMotor == HIGH && tiempoActual - tiempoAnterior >= tiempoEncendido) {
      // Apaga el MOTOR después de 2 minutos encendido
      estadoMotor = LOW;
      tiempoAnterior = tiempoActual;
    } else if (estadoMotor == LOW && tiempoActual - tiempoAnterior >= tiempoApagado) {
      // Enciende el MOTOR después de 5 minutos apagado
      estadoMotor = HIGH;
      tiempoAnterior = tiempoActual;
    }

    // Actualiza el estado del MOTOR
    digitalWrite(MOTOR, estadoMotor);
  }
  
  // Otras operaciones que puedes realizar durante el ciclo
  // ...
}
