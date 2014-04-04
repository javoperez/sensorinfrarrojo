// MEDIDOR DE CENTIMETROS Y VELOCIDAD; Por Javier Perez el 29 de Junio del 2013.
// Sensor Sharp  2y0a02 

const int analogInPin = A0;  // SENSOR IR

//LEDS
int led1 = 2;
int led2 =3;
int led3= 4; 


int sensorValue = 0;        // Valor Leido Sensor
int centimetros = 0;        // Valor convertido a Centímetros
int velocidad=0;
int time= 0;  //Tiempo en Segundos


void setup() {
  // inicializa conexión serie a 9600 bps:
  Serial.begin(9600); 
 pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);   
   pinMode(led3, OUTPUT);    
}

void loop() {
  
  time= time+1;
  int PROMEDIO_1=0;
  int suma=0;
  int PROMEDIO_2=0;

  //******************************************
  // Lee el SENSOR y lo guarda los primeros 250 mS
     for (int i = 0; i < 250; ++i)
  {   sensorValue = analogRead(analogInPin);           
  // Conversión a centímetros
 centimetros = 0.0002*sensorValue*sensorValue -(0.2693*sensorValue) + 91.19305;
 
   delay(1);
    
    suma= suma+centimetros;
   
  }

  PROMEDIO_1= suma/250;

  //******************************************
  suma=0; //Reinicializa la cuenta

// Lee el sensor y guarda de 250mS a 500 mS en PROMEDIO 2
       for (int i = 0; i < 250; ++i)
  {   sensorValue = analogRead(analogInPin);           
  // Conversión a centímetros
 centimetros = 0.0002*sensorValue*sensorValue -(0.2693*sensorValue) + 91.19305;
 
   delay(1);
    
    suma= suma+centimetros;
   
  }

  PROMEDIO_2= suma/250;

  velocidad= (PROMEDIO_2 - PROMEDIO_1)*2;
   

       // Imprime por el UART
 //SENSOR  
 //CENTIMETROS
  Serial.print("\t Centimetros= ");      
  Serial.println((PROMEDIO_1 + PROMEDIO_2)/2);
  // TIEMPO
   Serial.print("\t TIEMPO= ");      
  Serial.println(time);   
    Serial.print("\t Velocidad= ");      
  Serial.println(velocidad);     

if(velocidad  <= -20|| velocidad >= 20)
{
  digitalWrite(led1, HIGH);   // PRENDE FLASH CAMARA.
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(2000);  
  digitalWrite(led1,LOW); 
  digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);//APAGA FLASH CAMARA.
  
  }   
   delay(500);      


}
//y = 0.0002x2 - 0.2693x + 91.19305 <<<== Formula obtenida por interpolacion lineal

// X= Voltaje, Y = Centimetros
