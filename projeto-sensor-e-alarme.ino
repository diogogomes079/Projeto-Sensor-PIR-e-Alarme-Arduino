// Programa : Sensor de presenca com modulo PIR e Buzzer
// Autor : Diogo Gomes Pinheiro

#define botao 2        // Define o Botão no Pino 2
#define PIR 3          // Define o PIR(Sensor de presensa) no Pino 3
#define buzzer 4       // Define o Buzzer no Pino 4
#define ledVermelho1 5 // Define o pino do LED Vermelho(1) no Pino 5
#define ledVermelho2 6 // Define o pino do LED Vermelho(2) no Pino 6
#define ledVerde 7     // Define o pino do LED Verde no Pino 7

int PIREstado;         // Variavel para verificar o estado do PIR
long UltimoTempo = 0;       // Pega o Ultimo tempo apertado do Botao
int EstadoDoBotao = LOW;    // Pega o Ultimo estado do Botao
int filtro = 300;           // Filtra o ruido do botao 300 millseconds voce poder mudar
int pegaValorDoBotao = LOW; // Set o valor Atual do botao como desligado

void setup()
{
  //Serial.begin(9600);
  pinMode(ledVermelho1, OUTPUT); // Define o LED Vermelho(1) como SAIDA
  pinMode(ledVermelho2, OUTPUT); // Define o LED Vermelho(2) como SAIDA
  pinMode(ledVerde, OUTPUT);     // Define o LED Verde como SAIDA
  pinMode(buzzer, OUTPUT);       // Define o Buzzer como SAIDA

  pinMode(botao, INPUT); // Define o botao como ENTRADA
  pinMode(PIR, INPUT);   // Define o PIR como ENTRADA
}

void loop()
{
  PIREstado = digitalRead(PIR); // Ler o Valor do PIR
  pegaValorDoBotao = digitalRead(botao); // Pega o valor atual do botao
  //Serial.println("Valor do Botão: " + String(pegaValorDoBotao));

  if ((pegaValorDoBotao == HIGH) && ((millis() - UltimoTempo) > filtro))
  {
    /*  Aki esta o pulo do gato!
     *  Verifico se vc apertou o botao, e verifico na mesma condicao se 
     *  millis() = cronometro interno do arduino menos o Ultimoperiodo for maior que o ruido   
     *  esta condicao vai ser sempre verdadeira.
     */

    if (EstadoDoBotao == HIGH)
    {
      EstadoDoBotao = LOW;
    }
    else
    {
      EstadoDoBotao = HIGH;
    }
    UltimoTempo = millis();
    //Serial.println("Estado do Botão: " + String(EstadoDoBotao));
  }
  //Aqui verifico o estado o Sensor de Presença
  if (PIREstado == LOW) // Sem movimento, mantem LED Verde ligado
  {
    digitalWrite(ledVermelho1, LOW);
    digitalWrite(ledVermelho2, LOW);
    digitalWrite(ledVerde, HIGH);
  }
  else /*Caso seja detectado um movimento, aciona o LED Vermelho(1 e 2) alternando
        * e caso o Botão tenha sido apertado o Buzzer toca ou não.
        */ 
  {
    Botao(EstadoDoBotao);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho1, HIGH);
    digitalWrite(ledVermelho2, LOW);
    delay(300);
    digitalWrite(ledVermelho1, LOW);
    digitalWrite(ledVermelho2, HIGH);
    delay(300);
  }
  pegaValorDoBotao = digitalRead(botao); // Pega o valor atual do botao
}

void Botao(int estado)
{
  if (estado == HIGH)
  {
    Sirene(1000);
  }
}
void Sirene(int frequencia)
{
  int duracao = 200;
  tone(buzzer, frequencia, duracao);
}
