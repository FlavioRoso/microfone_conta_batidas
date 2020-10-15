

#define LED 13
#define MICRO 12
#define MAX_BATIDAS 5;

typedef void (*Func)(); 

int ESTADO_MICRO = 0;
int ESTADO_LED = 0;
unsigned long time_ini;
int batidas = 0;


void sendComand(String comand,String data)
{

    comand.concat("->");
    data.concat("\n");
    comand.concat(data);
    Serial.print(comand);
}

void abrePaint(){

  sendComand("SHOW","Abrindo o paint....");
  sendComand("EXEC","mspaint");
  
}

void neverGonnaGiveYouUp(){

  sendComand("SHOW","NEVER GONNA GIVE YOU UP!!!!!!!!!!!!!!!");
  sendComand("EXEC","explorer \"https://www.youtube.com/watch?v=dQw4w9WgXcQ\"");
  
}

uint8_t converteInput(int val)
{
  return val ? HIGH : LOW;
}

void alternaLed()
{
    ESTADO_LED = !ESTADO_LED;
    sendComand("SHOW", ESTADO_LED ? "Acendendo led" : "Apagando led" );
    digitalWrite(LED,converteInput(ESTADO_LED));
    
}

Func funcoesBatidas[MAX_BATIDAS]= {
  
      NULL,
      alternaLed,
      abrePaint,
      NULL,
      neverGonnaGiveYouUp
  
  };

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(MICRO,INPUT);
  Serial.begin(9600);
  ESTADO_MICRO = digitalRead(MICRO);


}




void actionBatidas(int batidas)
{
  
  
  if(funcoesBatidas[batidas-1] != NULL && batidas <= MAX_BATIDAS)
  {
    funcoesBatidas[batidas-1]();
  }
  
}

void ouvirBatidas()
{
    if(!digitalRead(MICRO))
    {
       time_ini = millis();
       
       batidas = 1;
       
       while(millis() < (time_ini + 1500))
       {
        
           
           if(!digitalRead(MICRO) && millis() > (time_ini + 200))
           {
             
              batidas++;
              delay(200);
              
           }
        
       }
    }
}

int execute()
{
  ouvirBatidas();
  if(batidas)
  {
    //Serial.print(batidas);
    //Serial.print("\n");
    actionBatidas(batidas);
    batidas = 0;
  }
}



void loop() {
  
  execute();
  
}
