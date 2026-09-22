#define led_01 10 // Verde
#define led_02 9  // Amarelo
#define led_03 8  // Vermelho

#define bttn_01 7
#define bttn_02 6
#define bttn_03 5

#define buzzer 3

#define mult 11

int sequencia_leds[10] = {1, 3, 3, 1, 2, 1, 3, 2, 1, 2};
int sequencia_jogador[10]; // Array para guardar as jogadas
bool is_primeira_execucao = true; 

void setup() {
  pinMode(led_01, OUTPUT);
  pinMode(led_02, OUTPUT);
  pinMode(led_03, OUTPUT);

  // Assumindo uso de resistores pull-down físicos (botão solto = LOW, apertado = HIGH)
  pinMode(bttn_01, INPUT);
  pinMode(bttn_02, INPUT);
  pinMode(bttn_03, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(mult, OUTPUT);
  
  analogWrite(mult, 100);
}

void loop() {
  if (is_primeira_execucao) {
    delay(3000);
    is_primeira_execucao = false;
  }

  // 1. O Arduino mostra a sequência
  executar_sequencia();

  // 2. O jogador insere a sua sequência
  ler_jogada();

  // 3. O jogo verifica e dá o resultado
  if (verificar_resultado()) {
    animacao_acerto();
  } else {
    animacao_erro();
  }

  // Pausa antes de reiniciar a rodada inteira
  delay(2000);
}

// --- FUNÇÕES DE CONTROLE DE HARDWARE ---

void acionar_led_e_som(int numero) {
  int pino_led = (numero == 1) ? led_01 : (numero == 2) ? led_02 : led_03;
  int nota_hz = (numero == 1) ? 262 : (numero == 2) ? 330 : 392;

  digitalWrite(pino_led, HIGH);
  tone(buzzer, nota_hz);
}

void desligar_led_e_som(int numero) {
  int pino_led = (numero == 1) ? led_01 : (numero == 2) ? led_02 : led_03;
  
  digitalWrite(pino_led, LOW);
  noTone(buzzer);
}

// --- FUNÇÕES DO JOGO ---

void executar_sequencia() {
  // Toca as 10 notas
  for (int numero : sequencia_leds) {
    acionar_led_e_som(numero);
    delay(400);
    
    desligar_led_e_som(numero);
    delay(200); // Pequena pausa entre as notas para não embolar
  }

  delay(300);

  // Sinal de que a sequência acabou (pisca tudo 5 vezes)
  for (int i = 0; i < 5; i++) {
    digitalWrite(led_01, HIGH); digitalWrite(led_02, HIGH); digitalWrite(led_03, HIGH);
    tone(buzzer, 440);
    delay(100);
    
    digitalWrite(led_01, LOW); digitalWrite(led_02, LOW); digitalWrite(led_03, LOW);
    noTone(buzzer);
    delay(100);
  }
}

void ler_jogada() {
  for (int i = 0; i < 10; i++) {
    int botao_pressionado = 0;

    // Fica travado aqui até o jogador apertar um dos botões
    while (botao_pressionado == 0) {
      if (digitalRead(bttn_01) == HIGH) botao_pressionado = 1;
      else if (digitalRead(bttn_02) == HIGH) botao_pressionado = 2;
      else if (digitalRead(bttn_03) == HIGH) botao_pressionado = 3;
    }

    // Salva a escolha e liga o LED/Som correspondente
    sequencia_jogador[i] = botao_pressionado;
    acionar_led_e_som(botao_pressionado);

    // Fica travado aqui até o jogador SOLTAR o botão
    while (digitalRead(bttn_01) == HIGH || digitalRead(bttn_02) == HIGH || digitalRead(bttn_03) == HIGH) {
      delay(10); 
    }

    // Desliga quando solta
    desligar_led_e_som(botao_pressionado);
    delay(100); // Pausa breve para evitar cliques duplos acidentais (debounce)
  }
}

bool verificar_resultado() {
  for (int i = 0; i < 10; i++) {
    if (sequencia_leds[i] != sequencia_jogador[i]) {
      return false; // Errou algum passo
    }
  }
  return true; // Acertou todos
}

void animacao_acerto() {
  // Liga apenas LED Verde e toca nota aguda de vitória
  digitalWrite(led_01, HIGH);
  tone(buzzer, 523); // Dó mais agudo
  delay(1500);
  
  digitalWrite(led_01, LOW);
  noTone(buzzer);
}

void animacao_erro() {
  // Liga apenas LED Vermelho e toca nota grave de erro
  digitalWrite(led_03, HIGH);
  tone(buzzer, 150); // Som bem grave
  delay(1500);
  
  digitalWrite(led_03, LOW);
  noTone(buzzer);
}
