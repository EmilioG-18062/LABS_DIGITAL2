/*Emilio Gordillo, 18062
  Proyecto 4*/
/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
// Librerías
//----------------------------------------------------------------------------------------------------------------
#include <WiFi.h>
#include <WebServer.h>
//----------------------------------------------------------------------------------------------------------------
// Variables
//----------------------------------------------------------------------------------------------------------------
// SSID & Password
const char* ssid = "Nexxt_96EB2B";  // Enter your SSID here
const char* password = "18022000";  //Enter your Password here
 
uint8_t PB[4];
uint8_t Lugares = 0;
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
 
uint8_t LED1pin = 2;
bool LED1status = LOW;

//Variables para el display
uint8_t CP;
uint8_t A=22;
uint8_t B=3;
uint8_t C=21;
uint8_t D=19;
uint8_t E=18;
uint8_t F=33;
uint8_t G=25;

 
//----------------------------------------------------------------------------------------------------------------
// Setup
//----------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);
 
  pinMode(LED1pin, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
 
  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);
 
  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
 
  server.on("/", handle_OnConnect); 
  server.on("/datos", handle_Data); // handler para enviar datos
 
 
  server.onNotFound(handle_NotFound);
 
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

//----------------------------------------------------------------------------------------------------------------
// loop principal
//----------------------------------------------------------------------------------------------------------------
void loop() {
  server.handleClient();          //Inicia servidor
    //Empezar a la lectura del UART
  if (Serial2.available())
    { 
      //Encender led para que reciba los datos por el UART  
      digitalWrite(2, 1);
        //For para leer los 4 bytes
        for (int i = 0; i<=3; i++)
        {
          PB[i] = Serial2.read(); 
          
        }
        CP = 4-(PB[0]+PB[1]+PB[2]+PB[3]);  //Se realiza el calculo de cuantos parqueos hay
    }

    //Apagar led del UART
    digitalWrite(2, 0);       

    switch (CP) { 
        case 4: 
          digitalWrite(A, HIGH);
          digitalWrite(B, HIGH);
          digitalWrite(C, LOW);
          digitalWrite(D, HIGH);
          digitalWrite(E, LOW);
          digitalWrite(F, LOW);
          digitalWrite(G, HIGH);
          break;
          
        case 3: 
          digitalWrite(A, HIGH);
          digitalWrite(B, LOW);
          digitalWrite(C, HIGH);
          digitalWrite(D, HIGH);
          digitalWrite(E, LOW);
          digitalWrite(F, HIGH);
          digitalWrite(G, HIGH);
          break;
          
        case 2: 
          digitalWrite(A, HIGH);
          digitalWrite(B, LOW);
          digitalWrite(C, HIGH);
          digitalWrite(D, HIGH);
          digitalWrite(E, HIGH);
          digitalWrite(F, HIGH);
          digitalWrite(G, LOW);
          break;
          
        case 1: 
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, HIGH);
          digitalWrite(E, LOW);
          digitalWrite(F, LOW);
          digitalWrite(G, HIGH);
          break;
          
        case 0: 
          digitalWrite(A, LOW);
          digitalWrite(B, HIGH);
          digitalWrite(C, HIGH);
          digitalWrite(D, HIGH);
          digitalWrite(E, HIGH);
          digitalWrite(F, HIGH);
          digitalWrite(G, HIGH);
          break;
      }
    
}

//----------------------------------------------------------------------------------------------------------------
// Inicio de Pagina
//----------------------------------------------------------------------------------------------------------------
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}
//----------------------------------------------------------------------------------------------------------------
// Handlers
//----------------------------------------------------------------------------------------------------------------
void handle_Data() {                          //se envia la data y se concatena los datos a enviar
  server.send(200, "application/json", data_json());
}
 
//----------------------------------------------------------------------------------------------------------------
// Correr script HTML
//----------------------------------------------------------------------------------------------------------------
String SendHTML(void) {
  String ptr = "<!DOCTYPE html>\n";

  ptr +="<html>\n";
  ptr +="<head>\n";
  ptr +="<style>\n";
  ptr +="table, th, td {\n";
  ptr +="border: 10px solid yellow;\n";
  ptr +="border-collapse: collapse;\n";
   
  ptr +="}\n";
  ptr +="th, td {\n";
  ptr +="\n";
  ptr +="  padding: 100px;\n";
  ptr +="  text-align: center;\n";
 
  ptr +="}\n";
  ptr +="#t01 tr:nth-child(even) {\n";
  ptr +="  background-color: #eee;\n";
  ptr +="}\n";
  ptr +="#t01 tr:nth-child(odd) {\n";
  ptr +=" background-color: #808080;\n";
  ptr +=" padding\n";
  ptr +="}\n";
  ptr +="#t01 th {\n";
  ptr +="  background-color: orange;\n";
  ptr +="  color: orange;\n";
  ptr +="}\n";

  ptr +="t01 {\n";
  ptr +="font-family: \"Univers Condensed\n";
  ptr +="font-size: 500%;\n"; 
  ptr +="\n";
  ptr +="}\n";
  
  ptr +="h2 {\n";
  ptr +="  font-family: \"Brush Script\";\n";
  ptr +="  font-size: 250%;\n";
  ptr +="  font-family: \"Univers Condensed\";\n";
  ptr +="\n";
  ptr +="}\n";
  ptr +="p {\n";
  ptr +="  font-family: \"Univers Condensed\";\n";
  ptr +="  font-size: 180%;\n";
  ptr +="  text-align: center;\n";
  ptr +="}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<body style=\"background-color:#FFA500;\">\n";
  ptr +="\n";
    
  ptr +="<h2 align=\"center\"style=\"color:white\">CONTROL DE PARQUEO</h2>\n";
  ptr +="<p style=\"color:black\"></p>\n";
  ptr +="\n";
  ptr +="<h3 align = center><p style=\"color:white\"> PROYECTO 4 </p></h3>\n";
  ptr +="</body>\n";
  ptr +="<h4 align = center><p style=\"color:white\"> EMILIO GORDILLO </p></h4>\n";
  ptr +="</body>\n";
  ptr +="</html>";

  ptr +="<table id=\"t01\"\n";
  ptr +="\talign=\"center\">\n";
  ptr +="    <td>PARQUEO 01</td>\n";
  ptr +="    <td>PARQUEO 02</td>\n";
  ptr +="    <td>PARQUEO 03</td>\n";
  ptr +="    <td>PARQUEO 04</td>\n";
  ptr +="  </tr> \n";
  ptr +="</table>\n";

  ptr += "<canvas id=\"1\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"2\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"3\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"4\">\n";
  ptr += "</canvas>\n";

  ptr += "<canvas id=\"Cantidad\">\n";
  ptr += "</canvas>\n";
  ptr += "<script>\n";
  
  ptr += "function boton(n_parqueo, valor){\n";
  ptr += "var canvas = document.getElementById(n_parqueo);\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "if (valor == 0){\n";
  ptr += "ctx.fillStyle = \"#3AFF00\";\n";
  ptr += "};\n";
  ptr += "if (valor == 1){\n";
  ptr += "ctx.fillStyle = \"#FF0000\";\n";
  ptr += "};\n";
  ptr += "ctx.fillRect(50,20,50,50);\n";
  ptr += "ctx.fillStyle = \"#FFA500\";\n";
  ptr += "};\n";
  
  ptr += "function ESTACIONAMIENTO(cantidad){\n";
  ptr += "var canvas = document.getElementById(\"Cantidad\");\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "ctx.fillStyle = \"#FFA500\";\n";
  ptr += "ctx.fillRect(0,0,1500,40);\n";
  ptr += "ctx.fillStyle = \"#FFFFFF\";\n";
  ptr += "ctx.font = \"30px Univers Condensed\";\n";
  ptr += "ctx.fillText(\"Parqueos disponibles: \" + cantidad.toString(), 0,30);\n";
  ptr += "};\n";
  
  ptr += "ESTACIONAMIENTO(4);\n";
  ptr += "boton(\"1\", 0);\n";
  ptr += "boton(\"2\", 0);\n";
  ptr += "boton(\"3\", 0);\n";
  ptr += "boton(\"4\", 0);\n";
  ptr += "var sendHttpRequest = function(){\n";
  ptr += "var xhr = new XMLHttpRequest();\n";
  ptr += "xhr.open(\"GET\", \"http://192.168.0.124/datos\");\n";
  ptr += "xhr.responseType = \'json\';\n";
  
  ptr += "xhr.onload = function() {\n";
  ptr += "  console.log(xhr.response);\n";
  ptr += "ESTACIONAMIENTO(xhr.response.lugares);\n";
  ptr += "boton(\"1\", xhr.response.espacio1);\n";
  ptr += "boton(\"2\", xhr.response.espacio2);\n";
  ptr += "boton(\"3\", xhr.response.espacio3);\n";
  ptr += "boton(\"4\", xhr.response.espacio4);\n"; 
  ptr += "};\n";
  ptr += "xhr.send();\n"; 
  ptr += "return xhr.response;\n";
  ptr += "};\n"; 
  ptr += "setInterval(function(){\n";
  ptr += "sendHttpRequest();\n";
  ptr += "},1);\n";
  ptr += "</script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

//----------------------------------------------------------------------------------------------------------------
// Handler not found
//----------------------------------------------------------------------------------------------------------------

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
String data_json(void){
  String dato_json = "{\"espacio1\":";
          dato_json += PB[0];
          dato_json += ",";
          dato_json += "\"espacio2\":";
          dato_json += PB[1];
          dato_json += ",";
          dato_json += "\"espacio3\":";
          dato_json += PB[2];
          dato_json += ",";
          dato_json += "\"espacio4\":";
          dato_json += PB[3];
          dato_json += ",";
          dato_json += "\"lugares\":";
          dato_json += CP;
          dato_json += "}";
  return dato_json;
}
