# IndicadorLed

Libreria para controlar un led y un buzzer en 2 pines.
Sobrecarga de constructor para objeto solo LED o LED + BUZZER
Sobrecarga en funciones PULSO para dar pulsos de LED o LED + BUZZER (usar constructor con Buzzer)
En estados CICLO, ENCDENDIDO o APAGADO no hay TONO

APAGAR Y ENCENDER hace lo que parece (lo apaga o lo enciende permanentemente).
Pulso hace un tren de X pulsos, indicando la duracion de encendido, la de apagado, el numero de pulsos y el TONO del buzzer (opcional)
CICLO hace un ciclo infinito de "trenes de PULSOS", SIN SONIDO, cada X tiempo.

Por tanto normalmente el led estara APAGADO, ENCENDIDO o en CICLO. 

Este estado se puede interrupir con la orden PULSO. Una vez finalizada dicha orden el LED volvera a su ESTADO ANTERIOR

Una orden PULSO mientras se ejecuta otra PULSO la PISA
La orden PULSO comienza con la pausa OFF para diferenciar los sonidos si llegan 2 ordenes seguidas
Tambien hace la pausa al final y tras esta ultima pausa finaliza la orden y vuelve todo a su estado anterior
O sea, 3 pulsos en tiempo es (3*TOFF)+(3*TON)+(1*TOFF) -- ( _|_|_|_ )
Si es importante para el CICLO tener en cuenta estos tiempos, el tiempo de ciclo es el indicado para el ciclo mas esto
Si hay BUZZER se puede dar frecuencia 0 en la orden PULSO para que haga pulsos sin pitar (o usar la funcion sin buzzer, a gusto del consumidor)

Una orden CICLO tambien comienza con la pausa entre ciclos por tanto no es inmediata. Usada en estado CICLO actualiza los parametros.
Una orden CICLO mientras se ejecuta una orden PULSO cancela los PULSOS pendientes.

Author: Diego Maroto - BilbaoMakers 2020 - info@bilbaomakers.org - dmarofer@diegomaroto.net
https://bilbaomakers.org/

Licencia: GNU General Public License v3.0 - https://www.gnu.org/licenses/gpl-3.0.html
