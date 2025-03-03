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


// struct Carro {
//   Roda frenteEsquerda;
//   Roda frenteDireita;
//   Roda trasEsquerda;
//   Roda trasDireita;

//   void init(Roda fEsq, Roda fDir, Roda tEsq, Roda tDir) {
//     frenteEsquerda = fEsq;
//     frenteDireita = fDir;
//     trasEsquerda = tEsq;
//     trasDireita = tDir;
//   }


// }


Roda motorA;
Roda motorB;
Roda motorC;
Roda motorD;

void setup() {
  //          IN1/IN2/PWM
  motorA.init(15, 19, 4);
  motorB.init(16, 17, 5);
  motorC.init(18, 2, 1);
  motorD.init(21, 3, 22);

}

void loop() {
  //Frente Esquerda
  motorA.move(255);
  //Frente Direita
  motorB.move(-255);
  //Tras Esquerda
  motorC.move(255);
  //Tras Direita
  motorD.move(-255);
}