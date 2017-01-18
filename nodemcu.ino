#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <ESP8266WebServer.h>

// Wifi name & password
const char* ssid = "*****;
const char* password = "*****";

bool state = 0;

ESP8266WebServer server(80); //Create a Web server


void setup(void){
  pinMode(D1, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/ledON", [](){
    digitalWrite(D1,HIGH);
    server.send(200,"text/plain", "Encendiendo LED");
  });
  server.on("/ledOFF", [](){
    digitalWrite(D1,LOW);
    server.send(200,"text/plain", "Apagando LED");
  });

  //Si no encuentra dirección
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop(void){
  server.handleClient();
  delay(1000);
}

/*-------------------------------------------------------
  --------------------- FUNCTIONS -----------------------
  -------------------------------------------------------*/

void handleRoot() {
  server.send(200,"text/HTML", "<p>Hola mundo!</p><ul><il>/ledON: encender</il><il>/ledOF: apagar</li></ul>");
}

void ledON() {
  digitalWrite(D1,HIGH);
  server.send(200,"text/plain", "Encendiendo LED");
}

void ledOFF() {
  digitalWrite(D1,LOW);
  server.send(200,"text/plain", "Apagando LED");
}

void handleNotFound(){

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri(); //Mostrar dirección que no funciona
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; //Mostrando argumentos
  }
  server.send(404, "text/plain", message);

}
