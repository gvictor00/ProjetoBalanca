#define trigPin 12
#define echoPin 13
#define DISTANCIA_LIMITE 15 // A distância (medida em cm) deve ser alterada neste ponto.

int passando = 0;
int quantidade = 0;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
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

  Serial.print("Itens que ja passaram: ");
  Serial.print(quantidade);
  Serial.println();

  delay(200);
}

/*
 * Considerando um caso hipotético de uma linha de produção, estou considerando
 * uma distância de 15 cm. Visto que qualquer coisa menor do que isso, "deveria"
 * ser um objeto que estará passando.
 */
