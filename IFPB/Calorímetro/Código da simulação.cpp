/* IFPB - PROJETO DE QUÍMICA - CLORÍMETRO COM ARDUÍNO
 * CALCULA CAPACIDADE TÉRMICA COM BASE NA TEMPERATURA AMBIENTE E FINAL
 * FOI APENAS SIMULADO***
 * FEITO POR: YASMIN ALVES DA SILVA E LAURA ALVES OLIVEIRA MACAÍBA DE SOUSA
 * LINK: https://www.tinkercad.com/things/09XVPzmS52Z-projeto-quimica-calorimetro/
 */

// Biblioteca LCD
#include <LiquidCrystal.h>

// Inicializa a biblioteca LCD
LiquidCrystal LCD(12,11,5,4,3,2);

// Define o pino analogico A0 como entrada do Sensor de Temperatura
int SensorTempPino = A0;

// Define as temperaturas a serem obtidas na simulação
float TempAmbiente;
float TempFinal;
float TempAgua1 = 0; 
float MassaAgua1 = 0;
float TempAgua = 0; 
float MassaAgua = 0;
int BTNSet = 8;
int BNTtemp = 7;
int BNTmassa = 6;

//Define função que retorna a capacidade térmica
float temperatura(int pino, float TempAmbiente);
void DadosAutomaticos(float TempAmbiente, float TempFinal);
void DadosInseridosManualmente( float TempAgua, float MassaAgua );


void setup() {
  Serial.begin(9600);
  pinMode(BTNSet, INPUT);
  pinMode(BNTtemp, INPUT);
  pinMode(BNTmassa, INPUT);
  
  // Define a quantidade de colunas e linhas do LCD
  LCD.begin(16,2);
  // Imprime a mensagem no LCD
  LCD.print("Capacidade Term:");
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  LCD.setCursor(0,1);
  // Imprime a mensagem no LCD
  LCD.print("           cal/C");
  Serial.println("Digite o Valor da massa");
  Serial.println("Digite o Valor da temperatura da agua");
  
  TempAmbiente = temperatura(SensorTempPino, 0);
  TempFinal = temperatura(SensorTempPino, TempAmbiente);
  
}

void loop() {
  
  DadosAutomaticos(TempAmbiente, TempFinal);
  DadosInseridosManualmente( TempAgua, MassaAgua );
  
  float Var1 = TempFinal - TempAmbiente;
  float Var2 = TempFinal - TempAgua1;  
      
  //C*Var1 + mc*Var2 = 0;
      float capacidade = ((-1)*MassaAgua1*1.0*Var2)/Var1;
      
      Serial.println("TempFinal: ");
      Serial.println(TempFinal);
      Serial.println("TempAmbiente: ");
      Serial.println(TempAmbiente);
      Serial.println("TempAgua1:");
      Serial.println(TempAgua1);
      Serial.println("MassaAgua1:");
      Serial.println(MassaAgua1);
      Serial.println("A capacidade eh:");
      Serial.println(capacidade);
  
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  LCD.setCursor(0,1);

  // Imprime a temperatura em Graus Celsius
  LCD.print(capacidade);

  // Aguarda 1 segundo
  delay(1000);
}

float temperatura(int pino, float TempAmbiente) {
  
  float TempFinal;

  do{
    
    int SensorTempTensao = analogRead(pino); // Leitura
    float Tensao = SensorTempTensao*5.0; // Converte para 5V
    Tensao/=1024;
    TempFinal = (Tensao-0.5)*100; // Converte para Celcius
    
    delay(1000);
    
    if (TempFinal != TempAmbiente) break;
    
  } while (TempAmbiente == TempFinal);
  
  delay(4000);
  
  return TempFinal;
  
}

void DadosInseridosManualmente(float TempAgua, float MassaAgua ){
  
  if (digitalRead(BNTtemp) == HIGH) {
      if (Serial.available()>0){
                float TempAgua = Serial.parseFloat();
                Serial.println("A temperatura registrada foi:");
                Serial.println(TempAgua);
                TempAgua1=TempAgua;
         }     
    }
  
    if (digitalRead(BNTmassa) == HIGH) {
      if (Serial.available()>0){
                float MassaAgua = Serial.parseFloat();
                Serial.println("A Massa registrada foi:");
                Serial.println(MassaAgua);
                MassaAgua1=MassaAgua;    
         }
    }   
}

void DadosAutomaticos(float TempAmbiente, float TempFinal) {
  
  if(digitalRead(BTNSet) == 1){
      
      MassaAgua1 = 500;
      TempAgua1 = 100;
    }
     
}
