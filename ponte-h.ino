#define motor_in_1 10
#define motor_in_2 11

void setup(){
  pinMode(motor_in_1, OUTPUT);
  pinMode(motor_in_2, OUTPUT);
}

void girar_frente(){
  digitalWrite(motor_in_1, HIGH);
  digitalWrite(motor_in_2, LOW);
}

void girar_tras(){
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, HIGH);
}

void parar(){
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);
}

void loop(){
  girar_frente(); // girar para frente
  delay(3000);   // esperar 3 segundos
  parar();       // desligar motor
  delay(2000);  // esperar 2 segundos
  girar_tras(); // girar para trás
  delay(3000);  // esperar 3 segundos
  parar();      // desligar motor
  delay(2000);  // esperar 2 segundos
}
