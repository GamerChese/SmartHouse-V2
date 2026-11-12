#include "counter.h"

unsigned long tiempoInicial = 0;
bool contando = false;

void startCounter(){
    tiempoInicial = millis();
    contando = true;
}

bool isCounterDone(unsigned long ms){
    if (!contando){
        return false;
    } 

    if(millis() - tiempoInicial >= ms){
        contando = false;
        return true;
    }
    return false;
}