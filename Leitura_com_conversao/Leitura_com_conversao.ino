char serialInput[150];
char commandByte = 0;
int serialCounter = 0;
bool recebeuPeso = false;
#define intervalo 2000

unsigned long tempo_atual = 0, tempo_anterior = 0;

void serialEvent1(){
  char incomingByte;
  incomingByte = Serial1.read();
  serialInput[serialCounter] = incomingByte;

 // Serial.print("Recebido: ");
 // Serial.print(serialInput[serialCounter]);

  serialCounter++;
  
 // Serial.println(" ");
 // Serial.println(serialCounter, DEC);

  if(serialCounter >= 150){
    recebeuPeso = true;
    serialCounter = 0;
  }
}

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){
  tempo_atual = millis(); // Solicita sozinho a cada 1 segundo. 
  if(tempo_atual - tempo_anterior > intervalo){
    commandByte = Serial.read();
    commandByte = 5;
    Serial.println("inicio");
    Serial1.write(commandByte);
    tempo_anterior = tempo_atual;
   }
  if(recebeuPeso == true)
  {
    int int_Peso = 0;
    recebeuPeso = false;
    int_Peso = serialToInt(serialInput[79], serialInput[81], serialInput[82], serialInput[83]);
    Serial.print("Peso: ");
    Serial.println(int_Peso);
  }
}

int serialToInt (char mil,char cem,char dez,char um){
  int inteiro_retorno = 0;
  inteiro_retorno = ((mil-48)*1000) + ((cem-48)*100) + ((dez-48)*10) + (um-48);
  return inteiro_retorno;
}
