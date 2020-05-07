
int ledRojo = 9;
int timbreRojo = 250;
int ledAmarillo = 8;
int timbreAmarillo = 300;
int ledAzul = 7;
int timbreAzul = 350;
int ledVerde = 6;
int timbreVerde = 400;
int buzzer = 5;

const int botonRojo = 13;
const int botonAmarillo = 12;
const int botonAzul= 3;
const int botonVerde = 2;

const int nivelMax = 20;
int secuencia[nivelMax];
int secuenciaUsuario[nivelMax];
int timbres[]= {timbreRojo,timbreAmarillo,timbreAzul,timbreVerde};
int btnPresionado[] = {botonRojo,botonAmarillo,botonAzul,botonVerde};

int nivelActual = 1;


void setup() {
  pinMode(ledRojo,OUTPUT);
  pinMode(ledAmarillo,OUTPUT);
  pinMode(ledAzul,OUTPUT);
  pinMode(ledVerde,OUTPUT);

  pinMode(botonRojo,INPUT);
  pinMode(botonAmarillo,INPUT);
  pinMode(botonVerde,INPUT);
  pinMode(botonAzul,INPUT);

  

  Serial.begin(9600);

}

void loop() {
  if(nivelActual == 1)
  {
    generaSecuencia();
    imprimirSecuencia();
    mostrarSecuencia();
    verificarSecuencia();
  }
  if(nivelActual !=0)
  {
    mostrarSecuencia();
    verificarSecuencia();
  }
  
}
void generaSecuencia(){
   randomSeed(millis());
   for(int i = 0; i < nivelMax; i++){
      secuencia[i] = random(6,10);
   }

}

void mostrarSecuencia()
{
  for(int i = 0; i < nivelActual; i++)
  {
    digitalWrite(secuencia[i],HIGH);
    tone(buzzer,timbres[secuencia[i]-6],100);
    delay(500);
    digitalWrite(secuencia[i],LOW);
    delay(500);
  }
}

void verificarSecuencia()
{
  int btnOn = 0;
  int flag = 0;
  
    
    for(int i = 0; i <nivelActual; i++)
    {
    flag = 0;
    while(flag == 0)
    {
      while(flag == 0)
    {
    
      for(int on = 0; on < 4; on++)
      {
        if(digitalRead(btnPresionado[on]) == HIGH)
        {
          btnOn = btnPresionado[on];
          flag = 1;
          
        }
      }
    }
      switch(btnOn)
      {
        case botonRojo: // El usuario Presiona el boton Rojo
        {
          tone(buzzer,timbres[3],100);
          delay(500);
          flag++;
          secuenciaUsuario[i] = ledRojo;
          Serial.println(secuenciaUsuario[i]);
          if(secuenciaUsuario[i] != secuencia[i])
          {
            secuenciaIncorrecta();
            return;
          }
          break;
          
        }
        case botonAmarillo: // El usuario Presiona el boton Amarillo
        {
          tone(buzzer,timbres[2],100);
          delay(500);
          flag++;
          secuenciaUsuario[i] = ledAmarillo;
          Serial.println(secuenciaUsuario[i]);
          if(secuenciaUsuario[i] != secuencia[i])
          {
            secuenciaIncorrecta();
            return;
          }
          break;
        }
        case botonAzul:// El usuario Presiona el boton Azul
        {
          tone(buzzer,timbres[1],100);
          delay(500);
          flag++;
          secuenciaUsuario[i] = ledAzul;
          Serial.println(secuenciaUsuario[i]);
          if(secuenciaUsuario[i] != secuencia[i])
          {
            secuenciaIncorrecta();
            return;
          }
          break;
        }
        case botonVerde:   // El usuario Presiona el boton Verde
        {
          tone(buzzer,timbres[0],100);
          delay(500);
          flag++;
          secuenciaUsuario[i] = ledVerde;
          Serial.println(secuenciaUsuario[i]);
          if(secuenciaUsuario[i] != secuencia[i])
          {
            secuenciaIncorrecta();
            return;
          }
          break;
        }
        
      }
    }
  }
  secuenciaCorrecta();
}

void secuenciaCorrecta() //el usuario asierta la secuencia completa y aumenta variable nivelActual
{
  if(nivelActual < nivelMax)
  {
    delay(500);
    tone(5,800,150);
    delay(100);
    tone(5,900,150);
    delay(100);
    tone(5,1000,150);
    nivelActual++;
    delay(500);
  }
}

void secuenciaIncorrecta() // el usuario ingresa secuencia incorrecta - nivelActual = 0 para interrumpir proceso
{
  tone(5,300,150);
  delay(100);
  tone(5,200,150);
  delay(100);
  tone(5,100,150);
  nivelActual = 0;
}

void imprimirSecuencia()
{
  for(int p = 0; p < nivelMax; p++)
   {
      Serial.print(secuencia[p]);
      
   }
  Serial.println();
}


//******************************************//
void pruebita()
{
  //Serial.println(digitalRead(botonRojo));
  if(digitalRead(botonRojo) == HIGH)
  {
    tone(buzzer,700,100);
    delay(500);
  }
    
}
