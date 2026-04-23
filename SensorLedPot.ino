/*
  PROYECTO: Sistema de Adquisición de Datos (DAQ)
  COMPONENTES: Potenciómetro (A0), Sensor LM35 (A1) y LED (D13)
*/

// Definición de pines
const int potPin = A0;   
const int tempPin = A1;  
const int ledPin = 13;

void setup() {
  // Iniciamos comunicación serial a 9600 bps
  Serial.begin(9600);
  
  // Configuramos el LED como salida
  pinMode(ledPin, OUTPUT);
  
  // Mensaje de depuración opcional (Python debe ignorar líneas que no sean números)
  // Serial.println("Iniciando Sistema DAQ...");
}

void loop() {
  // 1. Leer el Potenciómetro (valor de 0 a 1023)
  int potValue = analogRead(potPin);

  // 2. Leer el Sensor de Temperatura LM35
  int tempRaw = analogRead(tempPin);
  
  // 3. Convertir lectura de LM35 a grados Celsius
  // Fórmula: (Lectura * VoltajeReferencia / Resolución) * 100
  // Para Arduino Uno (5V y 10 bits):
  float celsius = (tempRaw * 5.0 / 1023.0) * 100.0;

  // 4. Transmisión de datos formateada para Python
  // Enviamos: "ValorPot,ValorTemp"
  Serial.print(potValue);
  Serial.print(",");
  Serial.println(celsius);

  // 5. Indicador visual (Parpadeo rápido por cada envío)
  digitalWrite(ledPin, HIGH);
  delay(20); 
  digitalWrite(ledPin, LOW);

  // 6. Frecuencia de muestreo (200ms = 5 lecturas por segundo)
  // Es un balance ideal para no saturar el puerto y ver cambios fluidos
  delay(180); 
}
