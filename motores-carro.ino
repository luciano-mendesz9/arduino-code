#define motorA_in1 7
#define motorA_in2 8
#define motorB_in3 9
#define motorB_in4 10

void setup(){
  pinMode(motorA_in1, OUTPUT);
  pinMode(motorA_in2, OUTPUT);
  pinMode(motorB_in3, OUTPUT);
  pinMode(motorB_in4, OUTPUT);
}

void andar_frente(){
  digitalWrite(motorA_in1, HIGH);
  digitalWrite(motorA_in2, LOW);
  digitalWrite(motorB_in3, HIGH);
  digitalWrite(motorB_in4, LOW);
}

void andar_tras(){
  digitalWrite(motorA_in1, LOW);
  digitalWrite(motorA_in2, HIGH);
  digitalWrite(motorB_in3, LOW);
  digitalWrite(motorB_in4, HIGH);
}

void parar(){
  digitalWrite(motorA_in1, LOW);
  digitalWrite(motorA_in2, LOW);
  digitalWrite(motorB_in3, LOW);
  digitalWrite(motorB_in4, LOW);
}

void loop(){
  andar_frente();
  delay(3000); // esperar 3 segundos
  parar();
  delay(3000); // esperar 3 segundos
  andar_tras();
  delay(3000); // esperar 3 segundos
  parar();
  delay(3000); // esperar 3 segundos
}

