#include "libs.h"

//=============================================== Variables ===============================================
unsigned long currentFrame;
unsigned long previousFrame;
const long interval = 8; //30ms para 30FPS, 16ms para 60FPS, 8ms para 120FPS 
int Frame_Update = 1;
int Mover_Derecha;
int Mover_Izquierda;
int Disparar_proyectil = 0;
int Flag_New_Position = 0;
int Inicio_Fila1 = 176;
int aleatorio;
int Golpe;
//=========================================================================================================

//================================================ Objetos ================================================
  //Declaramos a los objetos a utilizar
  int Player0_coordenadas[2] = {290,100};
  int Player0_puntaje = 0;
  String Player0_nombre = "JE";
  int Player0_sprite_size[3] = {20,20,1};
  unsigned char *Player0_sprite = Nave_Jugador;
  
  unsigned char *PProyectil_sprite = Proyectil_Player;
  int PProyectil_sprite_size[3] = {12,6,1};
  int PProyectil_coordenadas[2] = {279,100};
  int PProyectil_destinos[2] = {279,100};
  int First_shot = 0;
  
  int Bees_sprite_size[3] = {19,18,1};
  unsigned char *Bees_sprite = Enemigo1;
  int Bees_coordenadas[10] = {200, 100, 200, 100, 200, 100, 200, 100, 200, 100};
  int Bees_destinos[10] = {9, Inicio_Fila1-128, 9,Inicio_Fila1-96, 9, Inicio_Fila1-64, 9,Inicio_Fila1-32, 9,Inicio_Fila1};
  char Bees_estado[5] = {1,1,1,1,1};

  //=========================================================================================================

void setup(){
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSH1), BT1, FALLING);
  attachInterrupt(digitalPinToInterrupt(PUSH2), BT2, FALLING);
  
  LCD_Init();
  LCD_Clear(0x00);

  // Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
  FillRect(0, 0, 320, 240, 0xF4F5F);
  FillRect(8, 8, 304, 224, 0x00000);
  //for(int i; i<19; i++){
    //V_line(8+(16*i), 8, 224, 0xF4F5F);
  //}
  //for(int i; i<7; i++){
    //H_line(8, 8+(32*i), 304, 0xF4F55);
  //}

  LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1], Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0, 0, 0);
  String text2 = String(Player0_puntaje);
  LCD_Print(text2, 1,1,1,0xFFFFF, 0x00000);

}

void loop(){
  if(Frame_Update == 1){
    //Revisamos si hay un choque entre las naves
    if((PProyectil_coordenadas[0] < (Bees_coordenadas[0]+Bees_sprite_size[0])) && (PProyectil_coordenadas[1] < (Bees_coordenadas[1]+Bees_sprite_size[1])) && (PProyectil_coordenadas[0] > Bees_coordenadas[0]) && (PProyectil_coordenadas[1] > Bees_coordenadas[1])){
      Golpe = 1;
    }
    if((PProyectil_coordenadas[0] < (Bees_coordenadas[2]+Bees_sprite_size[0])) && (PProyectil_coordenadas[1] < (Bees_coordenadas[3]+Bees_sprite_size[1])) && (PProyectil_coordenadas[0] > Bees_coordenadas[2]) && (PProyectil_coordenadas[1] > Bees_coordenadas[3])){
      Golpe = 1;
    }
    if((PProyectil_coordenadas[0] < (Bees_coordenadas[4]+Bees_sprite_size[0])) && (PProyectil_coordenadas[1] < (Bees_coordenadas[5]+Bees_sprite_size[1])) && (PProyectil_coordenadas[0] > Bees_coordenadas[4]) && (PProyectil_coordenadas[1] > Bees_coordenadas[5])){
      Golpe = 1;
    }
    if((PProyectil_coordenadas[0] < (Bees_coordenadas[6]+Bees_sprite_size[0])) && (PProyectil_coordenadas[1] < (Bees_coordenadas[7]+Bees_sprite_size[1])) && (PProyectil_coordenadas[0] > Bees_coordenadas[6]) && (PProyectil_coordenadas[1] > Bees_coordenadas[7])){
      Golpe = 1;
    }
    if((PProyectil_coordenadas[0] < (Bees_coordenadas[8]+Bees_sprite_size[0])) && (PProyectil_coordenadas[1] < (Bees_coordenadas[9]+Bees_sprite_size[1])) && (PProyectil_coordenadas[0] > Bees_coordenadas[8]) && (PProyectil_coordenadas[1] > Bees_coordenadas[9])){
      Golpe = 1;
    }

    if(Golpe == 1){
      Player0_puntaje++;
      String text2 = String(Player0_puntaje);
      LCD_Print(text2, 1,1,1,0xFFFFF, 0x00000);
      FillRect(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], 0x00000);
      First_shot = 0;
      PProyectil_coordenadas[0] = 279;
      PProyectil_coordenadas[1] = 100;
      PProyectil_coordenadas[1] = Player0_coordenadas[1]+(Player0_sprite_size[0]/2)-3;
      PProyectil_destinos[0] = PProyectil_coordenadas[0] - 270;
      First_shot = 1;
      Golpe = 0;
    }
    
      
    if(Flag_New_Position == 300){
      for(int i; i<10; i++){
        aleatorio = rand()%(200-21+1)+21;        
        Bees_destinos[i] = aleatorio;
      }
      Flag_New_Position = 0;
    }

    //Hacemos los calculos de posiciones
    for(int i; i<10; i++){
      Bees_coordenadas[i] = Mover_Sprite(Bees_coordenadas[i],Bees_destinos[i]);
    }

    
        
    PProyectil_coordenadas[0] = Mover_Sprite(PProyectil_coordenadas[0], PProyectil_destinos[0]);
    PProyectil_coordenadas[0] = PProyectil_coordenadas[0] -2;
    
    if(PProyectil_coordenadas[0]<11){
      FillRect(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], 0x00000);
      First_shot = 0;
      PProyectil_coordenadas[0] = 279;
      PProyectil_coordenadas[1] = 100;
    }
    if(First_shot == 0){
      PProyectil_coordenadas[1] = Player0_coordenadas[1]+(Player0_sprite_size[0]/2)-3;
      PProyectil_destinos[0] = PProyectil_coordenadas[0] - 270;
      First_shot = 1;
    }

    Frame_Update = 0;
  }
  
  currentFrame = millis();
  if (currentFrame - previousFrame >= interval) {
    previousFrame = currentFrame;
    //Mandamos todos los Sprites a sus posciones
    for(int i; i<5; i++){
      LCD_Sprite(Bees_coordenadas[2*i],Bees_coordenadas[2*i+1], Bees_sprite_size[0], Bees_sprite_size[1], Bees_sprite, Bees_sprite_size[2], 1,0, 0);  
    }

    LCD_Sprite(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], PProyectil_sprite, PProyectil_sprite_size[2], 0,0, 0);
    
    if(Mover_Derecha == 1){
      for(int frame; frame <8; frame++){
        LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1]-frame, Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0,0, 0);
      }
      Player0_coordenadas[1]= Player0_coordenadas[1] - 8;
      Mover_Derecha = 0;
    }

    if(Mover_Izquierda == 1){
      for(int frame; frame <8; frame++){
        LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1]+frame, Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0,0, 0);
      }
      Player0_coordenadas[1]= Player0_coordenadas[1] + 8;
      Mover_Izquierda = 0;
    }
    
    Flag_New_Position++;
    Frame_Update = 1;
  } 
}

//=============================================== Funciones ===============================================

int Mover_Sprite(int x_inicial, int x_final){

  if(x_inicial < x_final){
    x_inicial++;
  }
  if(x_inicial > x_final){
    x_inicial--;
  }
  return x_inicial;
}

void Eliminar_Proyectil(){
  
}

//=========================================================================================================


//============================================ Interrupciones =============================================
//Funciones de los botones
void BT1() {
  if (Player0_coordenadas[1] > 210){
  }
  else {
    Mover_Izquierda = 1;
  }
}

void BT2() {
  if(Player0_coordenadas[1] < 13){
  }
  else{
    Mover_Derecha = 1;
  }
}
//=========================================================================================================
