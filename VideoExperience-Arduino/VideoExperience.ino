#include <SoftwareSerial.h>

/*
 * VideoExperience-Arduino
 * Código que permite la ejecución de "acciones" en respuesta
 * a los comandos que indica el VideoExperience App
 * By Carlos Chavez Laguna

 *Formato de comando b#i-#de. eg: b1-1000e
 *donde #i: es el nivel de intensidad 1,2,3.
 *donde #d: es la duración en milisegundos.
*/

#define MOTOR_A_PIN 5
#define BLUETOOTH_RX 10
#define BLUETOOTH_TX 11

int mIntensityList[]={90,130,250};
SoftwareSerial mBluetooth(BLUETOOTH_RX,BLUETOOTH_TX);

void setup() {
  pinMode(MOTOR_A_PIN,OUTPUT);
  //pinMode(MOTOR_b_PIN,OUTPUT);
  Serial.begin(9600);
  mBluetooth.begin(9600);  

 Serial.println("--VideoExperience-Arduino--");

}


String aux;
int intensityPos;
int duration;
void loop() {
   
   //cuando llegue una secuencia de bytes via bluetooth
  if(mBluetooth.available()){
		char c= mBluetooth.read();

		if(c=='b'){ //comienzo de comando
			aux="";
		}
		else if(c=='-'){ //intensidad (obtenido)
			intensityPos=aux.toInt();
			aux="";
		}
		else if(c=='e'){//duración (obtenido)
			duration=aux.toInt();			
			//final de lectura de comando (comando completo)
			performActionVibration();
			
			//resultado final de la recolección
			Serial.print("Intensidad: ");
			Serial.println(intensityPos);
			Serial.print("Duration: ");
			Serial.println(duration);
		}else{
			aux+=c;
		}

  } 
    
  delay(10);
}

void performActionVibration(){
	analogWrite(MOTOR_A_PIN,mIntensityList[intensityPos-1]);
	delay(duration);
	analogWrite(MOTOR_A_PIN,0);
}
