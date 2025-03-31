enum cardinalidade{
  NORTE, SUL, ESTE, OESTE
};

struct Detetor {
  int SensorN;

  int SensorS;

  int SensorE;

  int SensorO;
  
  void init(int S1,int S2,int S3,int S4){
    SensorN = S1;
    SensorS = S2;
    SensorE = S3;
    SensorO = S4;
  }

  int getSensor(cardinalidade sensor){
    switch(sensor){
      case cardinalidade::NORTE:
        return filtrar(SensorN);
      case cardinalidade::SUL:
        return filtrar(SensorS);
      case cardinalidade::ESTE:
        return filtrar(SensorE);
      case cardinalidade::OESTE:
        return filtrar(SensorO);
    }
  }

  int filtrar(int sensor){
    if(analogRead(sensor) < 700){
      return 1;
    return 0;
    }
  }

  void rodar(int graus){
    if (graus = 90){
      SensorN, SensorE, SensorS, SensorO = SensorE, SensorS, SensorO, SensorN;
    }

  }

};






struct Estabilizador {
  //Superior Esquerdo
  int Sensor1;

  //Superior Direito
  int Sensor2;

  //Inferior Esquerdo
  int Sensor3;

  //Inferior Direito
  int Sensor4;

  void init(int S1,int S2,int S3,int S4){
      Sensor1 = S1;
      Sensor2 = S2;
      Sensor3 = S3;
      Sensor4 = S4;
  }
  int getSensor(int sensor){
      switch(sensor){
        case 1:
          return filtrar(Sensor1);
        case 2:
          return filtrar(Sensor2);
        case 3:
          return filtrar(Sensor3);
        case 4:
          return filtrar(Sensor4);
      }
  }
  int filtrar(int sensor){
    if(analogRead(sensor) < 700){
      return 1;
    return 0;
    }
  }
  int direcao(){
    return getSensor(Sensor2) - getSensor(Sensor1) - getSensor(Sensor3) + getSensor(Sensor4);
  }
};

void setup() {
  Serial.begin(115200);
}

void loop() {

}