int num[10][8] = {
  //{a,b,c,d,e,f,g,h}
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0 - Inicialização
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1 - Faixa 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2 - Faixa 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3 - Faixa 3
  {0, 0, 0, 0, 0, 0, 0, 1}, // F - Fora da faixa
};

// Informações das faixas de pesagem, pré-definidas.
#define min_faixa_1 430
#define max_faixa_1 435
#define max_faixa_2 440
#define max_faixa_3 445
// Informações do Sensor ultrassonico HC-SR04
#define trigPin 12
#define echoPin 13
#define DISTANCIA_LIMITE 15 // A distância (medida em cm) deve ser alterada neste ponto.

char serialInput[150]; // buffer para leitura
char commandByte = 0;
int serialCounter = 0;
bool recebeuPeso = false;
bool passando = false;
int quantidade = 0;
long duration, distance;

// Funcionamento a base de interrupção, aguarda alguma ação na porta Serial do Arduino.
void serialEvent1() {
  char incomingByte;
  incomingByte = Serial1.read();
  serialInput[serialCounter] = incomingByte;

//  Serial.print("Recebido: ");
//  Serial.print(serialInput[serialCounter]);

  serialCounter++;

//  Serial.println(" ");
//  Serial.println(serialCounter, DEC);

  if (serialCounter >= 150) {
    recebeuPeso = true;
    serialCounter = 0;
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  for (int i = 46; i < 54; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  acende(4);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

//  Serial.print("Distancia: ");
//  Serial.print(distance);
//  Serial.print(" cm | ");
  if (distance < DISTANCIA_LIMITE)
  {
    passando = true;
  //  Serial.print("Passando um elemento | ");
  //  Serial.println(quantidade);
  }
  else if (passando == true)
  {
    passando = false;
    quantidade++;
  }
//  Serial.print("Itens que ja passaram: ");
  //Serial.print(quantidade);
//  Serial.println();

  if (Serial.available() > 0)
  {
    commandByte = Serial.read();
    commandByte = 5;
   // Serial.println("inicio");
    Serial1.write(commandByte); // Envia uma requisição de forma manual
  }
  if (recebeuPeso == true)
  {
    int int_Peso = 0;
    recebeuPeso = false;
    int_Peso = serialToInt(serialInput[79], serialInput[81], serialInput[82], serialInput[83]); // Os bytes que contem a medida do peso em gramas
    Serial.print("Peso: ");
    Serial.println(int_Peso);
    Serial.print("Itens que passaram: ");
    Serial.println(quantidade);
    if (int_Peso >= min_faixa_1 && int_Peso <= max_faixa_1)
    {
      acende(1);
      //Serial.println("Faixa 1 ! 430 a 435g");
    }
    else if (int_Peso > max_faixa_1 && int_Peso <= max_faixa_2)
    {
      acende(2);
      //Serial.println("Faixa 2 ! 435 a 440g");
    }
    else if (int_Peso > max_faixa_2 && int_Peso <= max_faixa_3)
    {
      acende(3);
      //Serial.println("Faixa 3 ! 440 a 445g");
    }
    else
    {
      acende(4);
      //Serial.println("Fora da faixa !");
    }
  }
  delay(10);
}

int serialToInt (char mil, char cem, char dez, char um) {
  int inteiro_retorno = 0;
  inteiro_retorno = ((mil - 48) * 1000) + ((cem - 48) * 100) + ((dez - 48) * 10) + (um - 48);
  return inteiro_retorno;
}

void acende(int n) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(i + 46, num[n][i]);
  }
}
