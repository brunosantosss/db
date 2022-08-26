//#include <Wire.h>
 
const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
#define PINO_SENSOR A0
#define LED_SOM_BAIXO 3
#define LED_SOM_MODERADO 4
#define LED_SOM_ALTO 5
 
void setup ()  
{   
  pinMode (PINO_SENSOR, INPUT); // Setando a entrada do pino sensor A0
  pinMode(LED_SOM_BAIXO, OUTPUT);
  pinMode(LED_SOM_MODERADO, OUTPUT);
  pinMode(LED_SOM_ALTO, OUTPUT); 
 
  digitalWrite(LED_SOM_BAIXO, LOW);
  digitalWrite(LED_SOM_MODERADO, LOW);
  digitalWrite(LED_SOM_ALTO, LOW);
  
  Serial.begin(115200);
}  
 
   
void loop ()  
{ 
    unsigned long startMillis = millis();                  
    float peakToPeak = 0;                                  // nivel pico a pico

    unsigned int signalMax = 0;                            // valor maximo
    unsigned int signalMin = 1024;                         // valor minimo

    // roda a cada 50 ms
    while (millis() - startMillis < sampleWindow)
    {
        sample = analogRead(PINO_SENSOR);                    // Lendo o microfone
        if (sample < 1024)                                  // Jogando fora sons inuteis
        {
            if (sample > signalMax)
            {
                signalMax = sample;                           // Salva o nivel maximo
            }
            else if (sample < signalMin)
            {
                signalMin = sample;                           // Salve o nivel minimo
            }
        }
    }

    peakToPeak = signalMax - signalMin;                    // amplitude pico a pico 
    int db = map(peakToPeak, 20, 900, 49.5, 90);             // Calibrando para decibeis
    Serial.println("Volume (dB): ");
    Serial.println(db);
    
    if (db <= 60) // Som normal / baixo
    {
        digitalWrite(LED_SOM_BAIXO, HIGH);
        digitalWrite(LED_SOM_MODERADO, LOW);
        digitalWrite(LED_SOM_ALTO, LOW);
    }
    else if (db > 60 && db < 85) // Som mais alto / moderado
    {
        digitalWrite(LED_SOM_BAIXO, LOW);
        digitalWrite(LED_SOM_MODERADO, HIGH);
        digitalWrite(LED_SOM_ALTO, LOW);
    }
    else if (db >= 85) // Som muito alto / alto
    {
        digitalWrite(LED_SOM_BAIXO, LOW);
        digitalWrite(LED_SOM_MODERADO, LOW);
        digitalWrite(LED_SOM_ALTO, HIGH);
    }

    delay(200); 
}
