// Pines del driver
#define RPWM 5
#define R_EN 6
#define L_EN 7 

// Pines de los LDR
#define LDR_LEFT A0
#define LDR_RIGHT A1

// Pin del potenciómetro
#define POT A2  

// Configuración
int umbral = 365;       // Se sobrescribirá con el potenciómetro
int velocidad = 25;     // PWM (0-255) ajusta la fuerza del motor

void setup() {
  pinMode(RPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  analogWrite(RPWM, 0);
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  Serial.begin(9600);
}

void loop() {
  int leftValue = analogRead(LDR_LEFT);
  int rightValue = analogRead(LDR_RIGHT);

  // Leer potenciómetro y mapearlo al rango 0–2046
  umbral = map(analogRead(POT), 0, 1023, 0, 2046);

  int diff = rightValue - leftValue;

  Serial.print("Izq: ");
  Serial.print(leftValue);
  Serial.print("  Der: ");
  Serial.print(rightValue);
  Serial.print("  Diff: ");
  Serial.print(diff);
  Serial.print("  Umbral: ");
  Serial.println(umbral);

  if (diff > umbral) {
    analogWrite(RPWM, velocidad);
    Serial.println("Girando derecha");
  }
  else if (diff < -umbral) {
    Serial.println("Debería girar izquierda pero no gira");
  }
  else {
    // Diferencia pequeña → parar
    analogWrite(RPWM, 0);
    Serial.println("Parando");
  }
  //delay(1000); No debería de hacer falta
}