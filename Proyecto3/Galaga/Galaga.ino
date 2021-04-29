
#include "libs.h"

//=============================================== Variables ===============================================
unsigned long currentFrame;
unsigned long previousFrame;
const long interval = 16; //30ms para 30FPS, 16ms para 60FPS, 8ms para 120FPS 
int Frame_Update = 1;
int Mover_Derecha;
int Mover_Izquierda;
int Disparar_proyectil = 0;
int First_shot = 0;
int Flag_New_Position = 0;
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
  int PProyectil_coordenadas[2] = {280,100};

  int Bee1_coordenadas[2] = {200, 100};
  int Bee1_destino[2] = {9,9};
  int Bee1_sprite_size[3] = {19,18,1};
  unsigned char *Bee1_sprite = Enemigo1;

  int Bee2_coordenadas[2] = {200, 100};
  int Bee2_destino[2] = {9,136};
  int Bee2_sprite_size[3] = {19,18,1};
  unsigned char *Bee2_sprite = Enemigo1;
  
  int Bee3_coordenadas[2] = {200, 100};
  int Bee3_destino[2] = {9,200};
  int Bee3_sprite_size[3] = {19,18,1};
  unsigned char *Bee3_sprite = Enemigo1;

  int Bee4_coordenadas[2] = {200,100};
  int Bee4_destino[2] = {9, 72};
  int Bee4_sprite_size[3] = {19,18,1};
  unsigned char *Bee4_sprite = Enemigo1;

  int Bee5_coordenadas[2] = {200, 100};
  int Bee5_destino[2] = {24,40};
  int Bee5_sprite_size[3] = {19,18,1};
  unsigned char *Bee5_sprite = Enemigo1;

  int Bee6_coordenadas[2] = {200, 100};
  int Bee6_destino[2] = {24,104};
  int Bee6_sprite_size[3] = {19,18,1};
  unsigned char *Bee6_sprite = Enemigo1;
  
  int Bee7_coordenadas[2] = {200, 100};
  int Bee7_destino[2] = {220,168};
  int Bee7_sprite_size[3] = {19,18,1};
  unsigned char *Bee7_sprite = Enemigo1;



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

}

void loop(){

  if(Frame_Update == 1){
    if(Flag_New_Position == 110){
      Bee1_destino[0] = Bee1_sprite_size[0]*random(2,(280/Bee1_sprite_size[0]));
      Bee1_destino[1] = Bee1_sprite_size[1]*random(2,(220/Bee1_sprite_size[1]));
      Bee2_destino[0] = Bee2_sprite_size[0]*random(2,(280/Bee2_sprite_size[0]));
      Bee2_destino[1] = Bee2_sprite_size[1]*random(2,(220/Bee2_sprite_size[1]));
      Bee3_destino[0] = Bee3_sprite_size[0]*random(2,(280/Bee3_sprite_size[0]));
      Bee3_destino[1] = Bee3_sprite_size[1]*random(2,(220/Bee3_sprite_size[1]));
      Bee4_destino[0] = Bee4_sprite_size[0]*random(2,(280/Bee4_sprite_size[0]));
      Bee4_destino[1] = Bee4_sprite_size[1]*random(2,(220/Bee4_sprite_size[1]));
      Bee5_destino[0] = Bee5_sprite_size[0]*random(2,(280/Bee5_sprite_size[0]));
      Bee5_destino[1] = Bee5_sprite_size[1]*random(2,(220/Bee5_sprite_size[1]));
      Bee6_destino[0] = Bee6_sprite_size[0]*random(2,(280/Bee6_sprite_size[0]));
      Bee6_destino[1] = Bee6_sprite_size[1]*random(2,(220/Bee6_sprite_size[1]));
      Bee7_destino[0] = Bee7_sprite_size[0]*random(2,(280/Bee7_sprite_size[0]));
      Bee7_destino[1] = Bee7_sprite_size[1]*random(2,(220/Bee7_sprite_size[1]));
      Flag_New_Position = 0;
    }
    //Hacemos los calculos de posiciones
    Bee1_coordenadas[0] = Mover_Sprite_X(Bee1_coordenadas[0],Bee1_destino[0]);
    Bee1_coordenadas[1] = Mover_Sprite_Y(Bee1_coordenadas[1],Bee1_destino[1]);
    Bee2_coordenadas[0] = Mover_Sprite_X(Bee2_coordenadas[0],Bee2_destino[0]);
    Bee2_coordenadas[1] = Mover_Sprite_Y(Bee2_coordenadas[1],Bee2_destino[1]);
    Bee3_coordenadas[0] = Mover_Sprite_X(Bee3_coordenadas[0],Bee3_destino[0]);
    Bee3_coordenadas[1] = Mover_Sprite_Y(Bee3_coordenadas[1],Bee3_destino[1]);
    Bee4_coordenadas[0] = Mover_Sprite_X(Bee4_coordenadas[0],Bee4_destino[0]);
    Bee4_coordenadas[1] = Mover_Sprite_Y(Bee4_coordenadas[1],Bee4_destino[1]);
    Bee5_coordenadas[0] = Mover_Sprite_X(Bee5_coordenadas[0],Bee5_destino[0]);
    Bee5_coordenadas[1] = Mover_Sprite_Y(Bee5_coordenadas[1],Bee5_destino[1]);
    Bee6_coordenadas[0] = Mover_Sprite_X(Bee6_coordenadas[0],Bee6_destino[0]);
    Bee6_coordenadas[1] = Mover_Sprite_Y(Bee6_coordenadas[1],Bee6_destino[1]);
    Bee7_coordenadas[0] = Mover_Sprite_X(Bee7_coordenadas[0],Bee7_destino[0]);
    Bee7_coordenadas[1] = Mover_Sprite_Y(Bee7_coordenadas[1],Bee7_destino[1]);
    
    Frame_Update = 0;
  }
  currentFrame = millis();
  if (currentFrame - previousFrame >= interval) {  
    // Guardamos el tiempo de la ultima actualizacion de frames
    previousFrame = currentFrame;
 
    //Mandamos todos los Sprites a sus posciones
    LCD_Sprite(Bee1_coordenadas[0],Bee1_coordenadas[1], Bee1_sprite_size[0], Bee1_sprite_size[1], Bee1_sprite, Bee1_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee2_coordenadas[0],Bee2_coordenadas[1], Bee2_sprite_size[0], Bee2_sprite_size[1], Bee2_sprite, Bee2_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee3_coordenadas[0],Bee3_coordenadas[1], Bee3_sprite_size[0], Bee3_sprite_size[1], Bee3_sprite, Bee3_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee4_coordenadas[0],Bee4_coordenadas[1], Bee4_sprite_size[0], Bee4_sprite_size[1], Bee4_sprite, Bee4_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee5_coordenadas[0],Bee5_coordenadas[1], Bee5_sprite_size[0], Bee5_sprite_size[1], Bee5_sprite, Bee5_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee6_coordenadas[0],Bee6_coordenadas[1], Bee6_sprite_size[0], Bee6_sprite_size[1], Bee6_sprite, Bee6_sprite_size[2], 1,0, 0);
    LCD_Sprite(Bee7_coordenadas[0],Bee7_coordenadas[1], Bee7_sprite_size[0], Bee7_sprite_size[1], Bee7_sprite, Bee7_sprite_size[2], 1,0, 0);

    if(Mover_Derecha == 1){
      //for(int frame; frame <8; frame++){
        //LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1]-frame, Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0,0, 0);
      //}
      Player0_coordenadas[1]= Player0_coordenadas[1] - 8;
      Mover_Derecha = 0;
    }

    if(Mover_Izquierda == 1){
      //for(int frame; frame <8; frame++){
        //LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1]+frame, Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0,0, 0);
      //}
      Player0_coordenadas[1]= Player0_coordenadas[1] + 8;
      Mover_Izquierda = 0;
    }

    if(Disparar_proyectil == 1){
      if(First_shot == 0){
        PProyectil_coordenadas[1] = Player0_coordenadas[1]+(Player0_sprite_size[0]/2)-1;
      }
      for(int frame; frame<8; frame++){
        LCD_Sprite(PProyectil_coordenadas[0]-frame, PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], PProyectil_sprite, PProyectil_sprite_size[2], 0,0, 0);
      }
      PProyectil_coordenadas[0] = PProyectil_coordenadas[0]-8;
      First_shot = 1;
      if(PProyectil_coordenadas[0]<16){
        PProyectil_coordenadas[0] = PProyectil_coordenadas[0]+PProyectil_sprite_size[0];
        for(int frame; frame<PProyectil_sprite_size[0]; frame++){
          V_line(PProyectil_coordenadas[0]-frame, PProyectil_coordenadas[1], PProyectil_sprite_size[0], 0x00000);
        }
        Disparar_proyectil = 0;
        First_shot = 0;
        PProyectil_coordenadas[0] = 278;
        PProyectil_coordenadas[1] = 100;
      }
    }
    Flag_New_Position++;
    Frame_Update = 1;
  }
}

//=============================================== Funciones ===============================================

int Mover_Sprite_X(int x_inicial, int x_final){

  if(x_inicial < x_final){
    x_inicial++;
  }
  if(x_inicial > x_final){
    x_inicial--;
  }
  return x_inicial;
}

int Mover_Sprite_Y(int y_inicial, int y_final){

  if(y_inicial < y_final){
    y_inicial++;
  }
  if(y_inicial > y_final){
    y_inicial--;
  }
  return y_inicial;
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
  Disparar_proyectil = 1;
}

void BT2() {
  if(Player0_coordenadas[1] < 13){
  }
  else{
    Mover_Derecha = 1;
  }
  Disparar_proyectil = 1;
}
//=========================================================================================================
