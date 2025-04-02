struct Roda {
  int IN1;
  int IN2;
  int PWM;
  int vel;

  void init(int _IN1, int _IN2, int _PWM) {
    IN1 = _IN1;
    IN2 = _IN2;
    PWM = _PWM;
    vel = 0;
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(PWM, OUTPUT);
  }
  
  void move(int newVel) {
    if (newVel == 0) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(PWM, newVel);
      return;
    }


    if (newVel > 0) {
      if (newVel > 255) {
        newVel = 255;
      }
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

    } else {
      if (newVel < -255) {
        newVel = -255;
      }
      newVel = -newVel;
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }

    vel = newVel;
    analogWrite(PWM, newVel);
  }
};


struct Carro {
  Roda frenteEsquerda;
  Roda frenteDireita;
  Roda trasEsquerda;
  Roda trasDireita;

  void init(Roda fEsq, Roda fDir, Roda tEsq, Roda tDir) {
    frenteEsquerda = fEsq;
    frenteDireita = fDir;
    trasEsquerda = tEsq;
    trasDireita = tDir;
  }

  void parar() {
    frenteEsquerda.move(0);
    frenteDireita.move(0);
    trasDireita.move(0);
    trasEsquerda.move(0);
  }

  void frente(int vel) {
    frenteEsquerda.move(vel);
    frenteDireita.move(vel);
    trasDireita.move(vel);
    trasEsquerda.move(vel);
  }

  void tras(int vel) {
    vel = -vel;
    frenteEsquerda.move(vel);
    frenteDireita.move(vel);
    trasDireita.move(vel);
    trasEsquerda.move(vel);
  }

  void direita(int vel) {
    frenteEsquerda.move(-vel);
    frenteDireita.move(vel);
    trasEsquerda.move(vel);
    trasDireita.move(-vel);
  }

  void esquerda(int vel) {
    frenteEsquerda.move(vel);
    frenteDireita.move(-vel);
    trasEsquerda.move(-vel);
    trasDireita.move(vel);
  }
};


Roda motorA;
Roda motorB;
Roda motorC;
Roda motorD;

Carro carro;

void setup() {
  //          IN1/IN2/PWM
  //Frente Esquerda
  motorA.init(15, 2, 4);
  //Frente Direita
  motorB.init(16, 17, 5);
  //Tras Esquerda
  motorC.init(27, 26, 25);
  //Tras Direita
  motorD.init(13, 12, 14);

  carro.init(motorA, motorB, motorC, motorD);
}

void loop() {
  carro.frente(200);
  delay(2000);
  carro.parar();
  delay(2000);
  carro.tras(200);
  delay(2000);
  carro.parar();
  delay(2000);
  carro.direita(200);
  delay(2000);
  carro.parar();
  delay(2000);
  carro.esquerda(200);
  delay(2000);
  carro.parar();
  delay(2000);
}