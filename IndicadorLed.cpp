#include <IndicadorLed.h>
#include "Arduino.h"

IndicadorLed::IndicadorLed(int l_pin, bool l_Invertir){

    this->pin=l_pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW ^ Invertir);
    EstadoLed = LED_APAGADO;
    EstadoLedCiclos = LED_APAGADO;
    TiempoONPulso = 200;
    TiempoOFFPulso = 1000;
    NumeroPulsos = 1;
    TiempoONCiclo = 200;
    TiempoOFFCiclo = 1000;
    TiempoCiclo = 5000;
    NumeroPulsosCiclo = 1;
    CuentaMillisPulso=millis();
    CuentaMillisCiclo=millis();
    CuentaPulsos = 0;
    Invertir = l_Invertir;
    BuzzerPresent = false;

}

IndicadorLed::IndicadorLed(int l_pin, bool l_Invertir, int l_pinBuzzer){

    this->pin=l_pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW ^ Invertir);
    EstadoLed = LED_APAGADO;
    EstadoLedCiclos = LED_APAGADO;
    TiempoONPulso = 200;
    TiempoOFFPulso = 1000;
    NumeroPulsos = 1;
    TiempoONCiclo = 200;
    TiempoOFFCiclo = 1000;
    TiempoCiclo = 5000;
    NumeroPulsosCiclo = 1;
    CuentaMillisPulso=millis();
    CuentaMillisCiclo=millis();
    CuentaPulsos = 0;
    Invertir = l_Invertir;
    PinBuzzer = l_pinBuzzer;
    BuzzerPresent = true;
    pinMode(PinBuzzer, OUTPUT);
    FrecuenciaTono = 1000;

}

void IndicadorLed::Pulsos(unsigned int l_TiempoONPulso, unsigned int l_TiempoOFFPulso, unsigned int l_NumeroPulsos){


    // Controlar que la orden dada no sea una chorrada
    if(l_TiempoONPulso>0 && l_TiempoOFFPulso>0 && l_NumeroPulsos>0){

        TiempoONPulso=l_TiempoONPulso;
        TiempoOFFPulso=l_TiempoOFFPulso;
        NumeroPulsos=l_NumeroPulsos;
        FrecuenciaTono=0;
        CuentaPulsos = 0;
        digitalWrite(pin, LOW ^ Invertir);
        if (BuzzerPresent){noTone(PinBuzzer);}
        EstadoLed=LED_PULSO_OFF;
        CuentaMillisPulso = millis();

    }
   

}

void IndicadorLed::Pulsos(unsigned int l_TiempoONPulso, unsigned int l_TiempoOFFPulso, unsigned int l_NumeroPulsos, int l_frecuenciaTono){

    // Controlar que la orden dada no sea una chorrada
    if (l_TiempoONPulso>0 && l_TiempoOFFPulso>0 && l_NumeroPulsos>0 && l_frecuenciaTono>=0){

        TiempoONPulso=l_TiempoONPulso;
        TiempoOFFPulso=l_TiempoOFFPulso;
        NumeroPulsos=l_NumeroPulsos;
        FrecuenciaTono=l_frecuenciaTono;
        CuentaPulsos = 0;
        digitalWrite(pin, LOW ^ Invertir);
        if (BuzzerPresent){noTone(PinBuzzer);}
        EstadoLed=LED_PULSO_OFF;
        CuentaMillisPulso = millis();

    }
  

}

void IndicadorLed::Ciclo(unsigned int l_TiempoONCiclo, unsigned int l_TiempoOFFCiclo, unsigned int l_TiempoCiclo, unsigned int l_NumeroPulsos){


    // Controlar que la orden dada no sea una chorrada
    if (l_TiempoCiclo >0 && l_NumeroPulsos>0 && l_TiempoONCiclo>0 && l_TiempoONCiclo>0){

        TiempoONCiclo = l_TiempoONCiclo;
        TiempoOFFCiclo = l_TiempoOFFCiclo;
        TiempoCiclo = l_TiempoCiclo;
        NumeroPulsosCiclo = l_NumeroPulsos;
        EstadoLed = LED_CICLO;
        EstadoLedCiclos = LED_CICLO;
        CuentaMillisCiclo = millis();

    }

}

void IndicadorLed::Encender(){

    digitalWrite(pin, HIGH ^ Invertir);
    EstadoLed = LED_ENCENDIDO;
    EstadoLedCiclos = LED_ENCENDIDO;

}

void IndicadorLed::Apagar(){

    digitalWrite(pin, LOW ^ Invertir);
    if (BuzzerPresent){noTone(PinBuzzer);}
    EstadoLed = LED_APAGADO;
    EstadoLedCiclos = LED_APAGADO;

}

void IndicadorLed::RunFast(){


    switch (EstadoLed){
    
        // Si el LED esta en estado CICLO
        case LED_CICLO:

            // Cuando se cumpla el tiempo del ciclo, PULSOS
            if ((millis() - CuentaMillisCiclo) > TiempoCiclo){

                if (BuzzerPresent){noTone(PinBuzzer);}
                this->Pulsos(TiempoONCiclo, TiempoOFFCiclo, NumeroPulsosCiclo);
                CuentaMillisCiclo = millis();

            }

        break;
        
        // Si el LED esta en estado PULSOS y esta apagado ..... Este es el estado inicial cuando se da un pulso para esperar la pausa primero
        case LED_PULSO_OFF:

            // Si llevamos apagados mas del tiempo de apagado
            if ((millis() - CuentaMillisPulso) > TiempoOFFPulso){

                // Si quedan pulsos por hacer
                if (CuentaPulsos < NumeroPulsos || NumeroPulsos == 0){
                                        
                    digitalWrite(pin, HIGH ^ Invertir);                                 // ENCENDER
                    CuentaMillisPulso = millis();                                       // ACTUALIZAR EL TIEMPO DEL CONTADOR
                    if (BuzzerPresent && FrecuenciaTono>0){tone(PinBuzzer,FrecuenciaTono,TiempoONPulso);}   // SI HAY BUZZER PITAR
                    EstadoLed = LED_PULSO_ON;                                           // PASAR A ESTE ESTADO QUE HARA OTRO CICLO

                }

                // Si ya no hay pulsos por hacer
                else{

                    EstadoLed=EstadoLedCiclos;              // Volver el led al estado LOGICO que estaba antes de los pulsos

                    switch (EstadoLedCiclos){               // Y recuperar el estado fisico al instante
                    
                        case LED_APAGADO:

                            if (BuzzerPresent){noTone(PinBuzzer);} // APAGAR
                            digitalWrite(pin, LOW ^ Invertir);      

                        break;

                        case LED_ENCENDIDO:

                            digitalWrite(pin, HIGH ^ Invertir);      // ENCENDER

                        break;

                        case LED_CICLO:

                            if (BuzzerPresent){noTone(PinBuzzer);}  // APAGAR PARA QUE HAGA EL CICO
                            digitalWrite(pin, LOW ^ Invertir);      
                            
                        break;

                        default:
                        break;

                    }

                }
                
             
            }
            
        break;


        case LED_PULSO_ON:

            //Si llevamos Encendidos mas del tiempo encendido
            if ((millis() - CuentaMillisPulso) > TiempoONPulso){

                // Apagar, actualizar el cuentatiempos y el estado y contar un ciclo hecho
                digitalWrite(pin, LOW ^ Invertir);
                CuentaMillisPulso = millis();
                EstadoLed = LED_PULSO_OFF;
                if (NumeroPulsos != 0){ CuentaPulsos++;}
             
            }

            
        break;



        default:
        break;

    
    }



}