const int potPin = A0;   
const int tempPin = A1;  
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int pot = analogRead(potPin);
  int temp= analogRead(tempPin);
  float celsius = (temp * 5000.0) / 1023.0;

  Serial.print(pot);
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
