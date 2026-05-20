#include <AFMotor.h>

// MOTORES
AF_DCMotor motor_esq(1);
AF_DCMotor motor_dir(2); 



// ULTRASSÔNICOS
#define TRIG_ESQ 8
#define TRIG_ESQ 9 

#define TRIG_DIR 10
#define TRIG_DIR 11



// IRs (BORDA)
#define IR_ESQ A0
#define IR_DIR A1



// CONFIG
int limite_borda = 500; 
int distancia_busca = 60;
int distancia_ataque = 30;

int velocidade_busca_esq = 170;
int velocidade_busca_dir = 120;

int velocidade_ajuste = 160;
int velocidade_ataque = 255;



// LER DISTÂNCIA 
int LerDistancia(int trig, int echo) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH, 25000);

    if (duraracao == 0) {
        return 999; 
    }
    return duracao / 58;
}



// MOVIMENTOS
void frente(int vel_esq, int vel_dir) {
  motor_esq.setSpeed(vel_esq);
  motor_dir.setSpeed(vel_dir);

  motor_esq.run(FORWARD);
  motor_dir.run(FORWARD);
}

void re(int vel) {
  motor_esq.setSpeed(vel);
  motor_dir.setSpeed(vel);

  motor_esq.run(BACKWARD);
  motor_dir.run(BACKWARD);
}

void girarEsquerda(int vel) {
  motor_esq.setSpeed(vel);
  motor_dir.setSpeed(vel);

  motor_esq.run(BACKWARD);
  motor_dir.run(FORWARD);
}

void girarDireita(int vel) {
  motor_esq.setSpeed(vel);
  motor_dir.setSpeed(vel);

  motor_esq.run(FORWARD);
  motor_dir.run(BACKWARD);
}

void parar() {
  motor_esq.run(RELEASE);
  motor_dir.run(RELEASE);
}


//BORDA
int bordaDetectada() {
    int valor_esq = analogRead(IR_ESQ);
    int valor_dir = analogRead(IR_DIR);

    if (valor_esq < limite_borda || valor_dir < limite_borda) {
        return 1; 
    }
    return 0;  
}


//SETUP
void setup(){
    pinMode(TRIG_ESQ, OUTPUT);
    pinMode(ECHO_ESQ, INPUT);

    pinMode(TRIG_DIR, OUTPUT);
    pinMode(ECHO_DIR, INPUT);

    pinMode(IR_ESQ, INPUT);
    pinMode(IR_DIR, INPUT);

    delay(5000);
}

//LOOP
void loop() {
  int dist_esq = lerDistancia(TRIG_ESQ, ECHO_ESQ);
  int dist_dir = lerDistancia(TRIG_DIR, ECHO_DIR);

  // 1. BORDA TEM PRIORIDADE
  if (bordaDetectada()) {
    re(255);
    delay(250);

    girarDireita(200);
    delay(350);

    return;
  }

  // 2. INIMIGO CENTRALIZADO = ATAQUE TOTAL
  if (dist_esq < distancia_ataque && dist_dir < distancia_ataque) {
    frente(255, 255);
    return;
  }

  // 3. INIMIGO MAIS À ESQUERDA
  if (dist_esq < dist_dir && dist_esq < distancia_busca) {
    girarEsquerda(velocidade_ajuste);
    delay(40);
    frente(220, 220);
    return;
  }

  // 4. INIMIGO MAIS À DIREITA
  if (dist_dir < dist_esq && dist_dir < distancia_busca) {
    girarDireita(velocidade_ajuste);
    delay(40);
    frente(220, 220);
    return;
  }
}

  // 5. HUNTER MODE
  frente(velocidade_busca_esq, velocidade_busca_dir);



















