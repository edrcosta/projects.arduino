//Programa: Pisca led com ATtiny85
//Autor: Arduino e Cia

void setup()
{
  //Define o pino 0 do ATtiny85 como saida
  pinMode(0, OUTPUT);
}

void loop()
{
  //Acende o led
  digitalWrite(0, HIGH);
  //Aguarda 1 segundo
  delay(1000);
  //Apaga o led
  digitalWrite(0, LOW);
  delay(1000);
}
