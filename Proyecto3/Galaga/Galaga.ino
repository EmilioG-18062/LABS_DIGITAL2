
#include "libs.h"

//La posicion de la nave menos el tamaño de la bala menos 1
int x_proyectil = 294;
int x_proyectil_pasado;

// Crear clase de Proyectil con sus coordenadas
class Proyectil {
  public:
    int coordenada_x;
    int coordenada_y;     
};

int jugador_y = 100;
int jugador_y_anterior;
int Mover_Derecha = 0;
int Mover_Izquierda = 0;
int delay_Proyectil = 0;
int Mover_Proyectil = 0;
int proyectil_x = 294;
int proyectil_x_pasado = 294;
int proyectil_y = 0;
int Puntaje = 0;
int Nave_Golpeada = 0;
int Enemigo_x = 25;
int Enemigo_y = 120;
int Enemigo_x_anterior = 100;
int Enemigo_y_anterior = 100;

//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void Proyectil_Movimiento();

//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");

  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSH1), BT1, FALLING);
  attachInterrupt(digitalPinToInterrupt(PUSH2), BT2, FALLING); 

  LCD_Init();
  LCD_Clear(0x00);

  // Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
  FillRect(0, 0, 319, 206, 0x0000);
  
  // Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, fontsize, color, background) 
  String text1 = "Galaga!";
  LCD_Print(text1, 100, 100, 2, 0xffff, 0x0000);
  String text2 = "Points";
  LCD_Print(text2, 4, 0, 1, 0xffff, 0x0000);
  String text3 = String(Puntaje, DEC);
  LCD_Print(text3, 10, 10, 1, 0xffff, 0x0000);

  LCD_Sprite(300, jugador_y, 16, 32, mario,8, 1,0, 1);   
}

//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  
  if(Mover_Derecha == 1){
    for (int i = 0; i<16; i++){
      LCD_Sprite(300, jugador_y+i, 16, 32, mario,8, 1,0, 1);
      H_line(300, jugador_y_anterior+i, 16, 0x00000);
    }
    jugador_y_anterior = jugador_y;
    jugador_y = jugador_y + 16;
    Mover_Derecha = 0;
  }
  if(Mover_Izquierda == 1){
    for (int i = 0; i<16; i++){
      LCD_Sprite(300, jugador_y-i, 16, 32, mario,8, 1,0, 1);
      H_line(300, jugador_y_anterior-i, 16, 0x00000);
    }
    jugador_y_anterior = jugador_y;
    jugador_y = jugador_y - 16;
    Mover_Izquierda = 0;
  }
  
  if(Nave_Golpeada == 1){
    FillRect(Enemigo_x, Enemigo_y, 32, 32, 0x00000);
    Nave_Golpeada = 12;
    Enemigo_y = 300;
    Enemigo_x = 206;
  }
  if(Nave_Golpeada == 0){
    Enemigo_y = random(40,200);
    Enemigo_x = random(1,200);
    LCD_Bitmap(Enemigo_x, Enemigo_y, 32, 32, prueba); 
    FillRect(Enemigo_x_anterior, Enemigo_y_anterior, 32, 32, 0x00000);
    Enemigo_x_anterior = Enemigo_x; 
    Enemigo_y_anterior = Enemigo_y;
  }
  
  if(Mover_Proyectil == 1){
    if (proyectil_x == 294){
      FillRect(proyectil_x, proyectil_y, 4, 4, 0xfffff);
      x_proyectil_pasado = proyectil_x;
      proyectil_x = x_proyectil_pasado - 4;
    }
    else if (proyectil_x < 294 && proyectil_x > 20){
      FillRect(proyectil_x, proyectil_y, 4, 4, 0xfffff);
      FillRect(x_proyectil_pasado, proyectil_y, 4, 4, 0x00000);
      x_proyectil_pasado = proyectil_x;
      proyectil_x = x_proyectil_pasado - 4;
    }
    else{
      FillRect(proyectil_x+4, proyectil_y, 4, 4, 0x00000);
      Mover_Proyectil = 0;
      proyectil_x = 294;
    }
  }

  if(proyectil_x>=Enemigo_x && proyectil_x<=Enemigo_x+32){
    if(proyectil_y>=Enemigo_y && proyectil_y<=Enemigo_y+32){
      Puntaje++;
      String text3 = String(Puntaje, DEC);
      LCD_Print(text3, 10, 10, 1, 0xffff, 0x0000);
      FillRect(proyectil_x+4, proyectil_y, 4, 4, 0x00000);
      Mover_Proyectil = 0;
      proyectil_x = 294;
      Nave_Golpeada = 1;
    }
  }
  
  
}
//Funciones de los botones
void BT1() {
  if(jugador_y > 200){
  }
  else{
    Mover_Derecha = 1;
  }  
}

void BT2(){
  //if(jugador_y < 10){
  //}
  //else{
    //Mover_Izquierda = 1;
  //}
  if(Mover_Proyectil == 0){
    proyectil_y = jugador_y;
  }
  Mover_Proyectil = 1;
}

//***************************************************************************************************************************************
// Función para mover los proyectiles
//***************************************************************************************************************************************
void Proyectil_Movimiento(int proyectil_x, int proyectil_y){
  
}
