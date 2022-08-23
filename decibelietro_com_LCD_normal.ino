/* Codigo para mostrar valor em dB */

const int PinoSensor = A0; //pino Analagico de Entrada 0

//int Estado = 0;
int ValorSensor = 0;
int valorMaior = 0;
float tensao = 0;
int dB = 0;
int cont = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    while(cont < 10000)
    {
        ValorSensor = analogRead(PinoSensor);
        if(ValorSensor > valorMaior)
            valorMaior = ValorSensor;
    
        cont++;
    }
    cont = 0;
    tensao = valorMaior / 1023.0 * 4.53;
    //dB = 103.1*tensao - 115,4;
    dB = 87.1 * tensao - 75,4;
    if(dB < 0)
        dB = 0;
    
    Serial.print("Tensao: ");
    Serial.print(tensao);
    Serial.println(" V");
    Serial.print("Decibeis: ");
    Serial.print(dB);
    Serial.println(" dB");
    valorMaior = 0;
    delay(100);
}
