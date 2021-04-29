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
int Nave_Golpeada;
int anim;
int Reproducir_Disparo = 0;
int Reproducir_Choque = 0;
int Flip_Player = 0;
int Disparos_Enemigos[] = {0,0,0,0,0};
int Actualizar_Contador = 0;
int Start = 0;
//=========================================================================================================

//================================================ Objetos ================================================
  //Declaramos a los objetos a utilizar
  int Player0_coordenadas[2] = {290,100};
  int Player0_destinos[2] = {290, 100};
  int Player0_puntaje = 0;
  String Player0_nombre = "JE";
  int Player0_sprite_size[3] = {20,20,7};
  unsigned char *Player0_sprite = Nave_Jugador;
  int Player0_vidas = 2;
  
  unsigned char *EProyectil_sprite = Proyectil_Player;
  int EProyectil_sprite_size[3] = {12,6,1};
  int EProyectil_coordenadas[10] = {8,8, 8,8, 8,8, 8,8, 8,8};
  int EProyectil_destinos[10] = {8,8, 8,8, 8,8, 8,8, 8,8};
  int EFirst_shot = 1;

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
  
  LCD_Init();
  LCD_Clear(0x00);

  // Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
  //FillRect(0, 0, 320, 240, 0xF4F5F);
  FillRect(8, 8, 304, 224, 0x00000);
  //for(int i; i<19; i++){
    //V_line(8+(16*i), 8, 224, 0xF4F5F);
  //}
  //for(int i; i<7; i++){
    //H_line(8, 8+(32*i), 304, 0xF4F55);
  //}
  
  start_music(melody1, durations1, songLength1);
  
  LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1], Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0, 0, 0);
  
  String text1 = "Score:";
  LCD_Print(text1, 5,1,1,0xFFFFF, 0x00000);

  String text2 = String(Player0_puntaje);
  LCD_Print(text2, 60,1,1,0xFFFFF, 0x00000);

  String text3 = Player0_nombre;
  LCD_Print(text3, 180,1,1,0xFFFFF, 0x00000);

  String text4 = String("Player:");
  LCD_Print(text4, 120,1,1,0xFFFFF, 0x00000);

  String text5 = "Vidas:";
  LCD_Print(text5, 220,1,1,0xFFFFF, 0x00000);
  
  String text6 = String(Player0_vidas);
  LCD_Print(text6, 280,1,1,0xFFFFF, 0x00000);

  String text8 = "Galaga!";
  LCD_Print(text8, 85,90,2,0xFFFFF, 0x00000);
  String text9 = "Presione un boton para comenzar";
  LCD_Print(text9, 25,130,1,0xFFFFF, 0x00000);

}

void loop(){

  Menu();
  
  //Revisamos los botones para comprabar si hay que mover la nave
  if(digitalRead(PUSH1) == 0){
    if (Player0_coordenadas[1] > 210){
    }
    else {
      Player0_destinos[1] = Player0_coordenadas[1]+2;
    }
  }
  if(digitalRead(PUSH2) == 0){
    if(Player0_coordenadas[1] < 13){
    }
    else{
      Player0_destinos[1] = Player0_coordenadas[1]-2;
    }
  }

  //Hacemos los calculos para el siguiente frame
  if(Frame_Update == 1){
    if(Flag_New_Position == 150){
      for(int i; i<5; i++){
        if(Disparos_Enemigos[i] == 0){
          EProyectil_coordenadas[2*i] = Bees_coordenadas[2*i];
          EProyectil_coordenadas[2*i+1] = Bees_coordenadas[2*i+1]+10;
          EProyectil_destinos[2*i] = Player0_coordenadas[0]+1;
          EProyectil_destinos[2*i+1] = Bees_coordenadas[2*i+1];
          Disparos_Enemigos[i] = 1;
        }
      }
    }

    if(Flag_New_Position == 300){
      //Hacemos los calculos de posiciones para los enemigos
      for(int i; i<10; i++){
        aleatorio = rand()%(200-21+1)+21;        
        Bees_destinos[i] = aleatorio;
      }
      Flag_New_Position = 0;
    }
    
    for(int i; i<5; i++){
      //Revisamos si hay un choque entre las naves y el proyectil
      if(((PProyectil_coordenadas[0]+3) < (Bees_coordenadas[2*i]+Bees_sprite_size[0])) && ((PProyectil_coordenadas[1]) < (Bees_coordenadas[2*i+1]+Bees_sprite_size[1])) && ((PProyectil_coordenadas[0]+3) > Bees_coordenadas[2*i]) && ((PProyectil_coordenadas[1]) > Bees_coordenadas[2*i+1])){
        Golpe = 1;
        Nave_Golpeada = 2*i;
      }
      //Revisamos si hay un choque entre las nave del jugador y los proyectiles
      if(((EProyectil_coordenadas[2*i]+12) > (Player0_coordenadas[0])) && ((EProyectil_coordenadas[2*i+1]+3) > Player0_coordenadas[1]) && ((EProyectil_coordenadas[2*i]+12) < (Player0_coordenadas[0]+20)) && ((EProyectil_coordenadas[2*i+1]+3) < (Player0_coordenadas[1]+20))){
          Player0_vidas--;
          Actualizar_Contador = 1;
          FillRect(EProyectil_coordenadas[2*i], EProyectil_coordenadas[2*i+1], EProyectil_sprite_size[0], EProyectil_sprite_size[1], 0x0000);
          EProyectil_coordenadas[2*i+1] = Bees_coordenadas[2*i+1]+5;
          EProyectil_coordenadas[2*i] = Bees_coordenadas[2*i]+20;      
          Disparos_Enemigos[i] = 0;
        }
      //Revisamos si el Proyectil enemigo llego al limite del mapa
      if(EProyectil_coordenadas[2*i] == Player0_coordenadas[0]){
        FillRect(EProyectil_coordenadas[2*i], EProyectil_coordenadas[2*i+1], EProyectil_sprite_size[0], EProyectil_sprite_size[1], 0x0000);
        EProyectil_coordenadas[2*i+1] = Bees_coordenadas[2*i+1]+5;
        EProyectil_coordenadas[2*i] = Bees_coordenadas[2*i]+20;       
        Disparos_Enemigos[i] = 0;
      }
    }
    
    //Revisamos si el proyectil impacta para regresarlo a su posicion inicial
    if(Golpe == 1){
      Player0_puntaje++;
      Actualizar_Contador = 1;
      FillRect(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], 0x00000);
      FillRect(Bees_coordenadas[Nave_Golpeada], Bees_coordenadas[Nave_Golpeada+1], Bees_sprite_size[0], Bees_sprite_size[1], 0x00000);
      Bees_coordenadas[Nave_Golpeada] = 8;
      Bees_coordenadas[Nave_Golpeada+1] = rand()%(200-21+1)+21;
      PProyectil_coordenadas[0] = 279;
      PProyectil_coordenadas[1] = 100;
      PProyectil_coordenadas[1] = Player0_coordenadas[1]+(Player0_sprite_size[0]/2)-3;
      PProyectil_destinos[0] = PProyectil_coordenadas[0] - 270;
      Reproducir_Disparo = 1;
      Reproducir_Choque = 1;
      First_shot = 1;
      Golpe = 0;
    }

    //Movemos a los enemigos
    for(int i; i<10; i++){
      Bees_coordenadas[i] = Mover_Sprite(Bees_coordenadas[i],Bees_destinos[i]);
    }

    //Movemos al jugador
    Player0_coordenadas[1] = Mover_Sprite(Player0_coordenadas[1],Player0_destinos[1]);

    //Movemos el proyectil
    PProyectil_coordenadas[0] = Mover_Sprite(PProyectil_coordenadas[0], PProyectil_destinos[0]);
    PProyectil_coordenadas[0] = PProyectil_coordenadas[0] -2;

    //Movemos el proyectil enemigo
    for(int i; i<5; i++){
      if( Disparos_Enemigos[i] == 1){
        EProyectil_coordenadas[2*i] = Mover_Sprite(EProyectil_coordenadas[2*i], EProyectil_destinos[2*i]);
      }
    }

    //Revisamos si el Proyectil llego al limite del mapa
    if(PProyectil_coordenadas[0]<11){
      FillRect(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], 0x00000);
      First_shot = 0;
      PProyectil_coordenadas[0] = 279;
      PProyectil_coordenadas[1] = 100;
      
    }

    
    
    //Revisamos si el proyectil esta en la posicion inicial
    if(First_shot == 0){
      PProyectil_coordenadas[1] = Player0_coordenadas[1]+(Player0_sprite_size[0]/2)-3;
      PProyectil_destinos[0] = PProyectil_coordenadas[0] - 270;
      Reproducir_Disparo = 1;
      First_shot = 1;
    }

    //Revisamos si hay un choque entre las naves
    for(int i; i<5; i++){
      for(int j; j<5; j++){
        if(((Bees_coordenadas[2*i]) < (Bees_coordenadas[2*j]+Bees_sprite_size[0])) && ((Bees_coordenadas[2*i+1]) < (Bees_coordenadas[2*j+1]+Bees_sprite_size[1])) && ( j != i)){      
          aleatorio = rand()%(200-21+1)+21;        
          Bees_destinos[i] = aleatorio;
        }
        if(((Bees_coordenadas[2*i]+Bees_sprite_size[0]) > (Bees_coordenadas[2*j])) && ((Bees_coordenadas[2*i+1]) < (Bees_coordenadas[2*j+1]+Bees_sprite_size[1])) && ( j != i)){      
          aleatorio = rand()%(200-21+1)+21;        
          Bees_destinos[i] = aleatorio;
        }
        if(((Bees_coordenadas[2*i+1]+Bees_sprite_size[1]) > (Bees_coordenadas[2*j+1])) && ((Bees_coordenadas[2*i]) < Bees_coordenadas[2*j]+Bees_sprite_size[0]) && ( j != i)){      
          aleatorio = rand()%(200-21+1)+21;        
          Bees_destinos[i] = aleatorio;
        }
        if(((Bees_coordenadas[2*i]+Bees_sprite_size[0]) > (Bees_coordenadas[2*j])) &&  ((Bees_coordenadas[2*i+1]+Bees_sprite_size[1]) > (Bees_coordenadas[2*j+1])) && ( j != i)){      
          aleatorio = rand()%(200-21+1)+21;        
          Bees_destinos[i] = aleatorio;
        }
      }
    }

    if(Actualizar_Contador == 1){
      String text6 = String(Player0_vidas);
      LCD_Print(text6, 280,1,1,0xFFFFF, 0x00000); 

      String text2 = String(Player0_puntaje);
      LCD_Print(text2, 60,1,1,0xFFFFF, 0x00000);
      Actualizar_Contador = 0;
    }
    
    Frame_Update = 0;
  }
  
  currentFrame = millis();
  if (currentFrame - previousFrame >= interval) {
    previousFrame = currentFrame;
    //Mandamos todos los sprites de los enemigos a sus posciones
    for(int i; i<5; i++){
      LCD_Sprite(Bees_coordenadas[2*i],Bees_coordenadas[2*i+1], Bees_sprite_size[0], Bees_sprite_size[1], Bees_sprite, Bees_sprite_size[2], 1,0, 0);  
    }
    if(Reproducir_Choque == 1){
      start_music(melody3, durations3, songLength3);
      Reproducir_Choque = 0;
    }
    
    //Movemos el sprite del proyectil
    LCD_Sprite(PProyectil_coordenadas[0], PProyectil_coordenadas[1], PProyectil_sprite_size[0], PProyectil_sprite_size[1], PProyectil_sprite, PProyectil_sprite_size[2], 0,0, 0);
    //Reproducimos el sonido del disparo
    if(Reproducir_Disparo == 1){
      start_music(melody2, durations2, songLength2);
      Reproducir_Disparo = 0;
    }

    //Movemos el sprite del proyectil del enemigo
    for(int i; i<5; i++){
      if(Disparos_Enemigos[i] == 1){
        LCD_Sprite(EProyectil_coordenadas[2*i], EProyectil_coordenadas[2*i+1], EProyectil_sprite_size[0], EProyectil_sprite_size[1], EProyectil_sprite, EProyectil_sprite_size[2], 0,1, 0);
      }
    }
      
    //Movemos el sprite del jugador
    LCD_Sprite(Player0_coordenadas[0], Player0_coordenadas[1], Player0_sprite_size[0], Player0_sprite_size[1], Player0_sprite, Player0_sprite_size[2], 0, 0, 0);

    Flag_New_Position++;
    Frame_Update = 1;
  }

  Terminar_Juego();
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

void start_music(int melody1[], int durations1[], int songLength1){
  musica(melody1, durations1, songLength1);
  //delay(100);
};

void Menu(){
  while(Start == 0){
    //Revisamos los botones para comprabar si hay que mover la nave
    if(digitalRead(PUSH1) == 0){
      Start = 1;
      FillRect(15, 30, 300, 180, 0x00000);
      break;
    }
    if(digitalRead(PUSH2) == 0){
      Start = 1;
      FillRect(15, 30, 300, 180, 0x00000);
      break;
    }
  }
}

void Terminar_Juego(){
  while( Player0_vidas == 0){
    String text7 = "Has Muerto";
    LCD_Print(text7, 80,100,2,0xFFFFF, 0x00000);
  }
}
//=========================================================================================================
