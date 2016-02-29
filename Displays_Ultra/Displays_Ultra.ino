#define trigPin 12
#define echoPin 13
#define DISTANCIA_LIMITE 15 // A distância (medida em cm) deve ser alterada neste ponto.

int passando = 0;
int quantidade = 0;

int num[10][8] = {
  //{a,b,c,d,e,f,g,h}
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 1, 0, 1, 1, 0}
};

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm | ");

  if (distance < DISTANCIA_LIMITE)
  {
    passando = 1;
    Serial.print("Passando um elemento | ");
  }
  else if (passando == 1)
  {
    passando = 0;
    quantidade++;
  }

  acende(quantidade);

  Serial.print("Itens que ja passaram: ");
  Serial.print(quantidade);
  Serial.println();

  delay(200);
}

void acende(int n) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(i + 2, num[n][i]);
  }
}
/*
   Considerando um caso hipotético de uma linha de produção, estou considerando
   uma distância de 15 cm. Visto que qualquer coisa menor do que isso, "deveria"
   ser um objeto que estará passando.
*/
