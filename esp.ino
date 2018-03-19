#include<SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "esp_ap";       //   SSID 
char pass[] = "12345678";    // паролааа

WiFiServer server(80);

char buff[]="F\n";
char buff1[]="S\n";
char buff2[]="R\n";
char buff3[]="B\n";
char buff4[]="L\n";

String request = "";

void setup() {
 Serial.begin(115200); 
 SPI.begin();  

 WiFi.mode(WIFI_AP);         
 WiFi.softAP(ssid, pass);  
 IPAddress myIP = WiFi.softAPIP(); 
 Serial.print("HotSpt IP:");
 Serial.println(myIP);
 
  
 server.begin();              
 Serial.println("HTTP server started");
}

void loop() {


  WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    request = client.readStringUntil('\n');

    if( request.indexOf("FORWARD") > 0 )  
    { 
      
      for(int i=0; i<sizeof buff; i++)  
      {
        SPI.transfer(buff[i]);
      }
      delay(1000); 
    }
    else if( request.indexOf("STOP") > 0 ) 
    { 
      for(int i=0; i<sizeof buff1; i++) 
      {
        SPI.transfer(buff1[i]);
      }
      delay(1000);  
    }
    else if( request.indexOf("RIGHT") > 0 ) 
    { 
      for(int i=0; i<sizeof buff2; i++) 
      {
        SPI.transfer(buff2[i]);
      }
      delay(1000);   
    }
    else if( request.indexOf("BACKWARD") > 0 ) 
    { 
      for(int i=0; i<sizeof buff3; i++) 
        SPI.transfer(buff3[i]);
      delay(1000);   
    }

    else if( request.indexOf("LEFT") > 0 ) 
    { 
      for(int i=0; i<sizeof buff4; i++)  
        SPI.transfer(buff4[i]);
      delay(1000);   
    }

  client.flush();

  client.print(F(  
    "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'/>"
    "<meta charset='utf-8'>"
    "<style>"
    "body {font-size:140%;}"
    "#main {display: table; margin: auto;  padding: 0 10px 0 10px; }"
    "h2 {text-align:center; } "
    ".button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} "
    ".button1 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    ".button2 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    ".button3 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    ".button4 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    "</style>"
    "<title>Walkin Robot Control</title>"
    "</head>"
    "<body>"
    "<div id='main'><h2>WALKING ROBOT</h2>"
    "<form id='F1' action='FORWARD'><input class='button' type='submit' value='MOVE FORWARD' ></form><br>"
    "<form id='F4' action='BACKWARD'><input class='button3' type='submit' value='BACKWARD' ></form><br>"
    "<form id='F3' action='RIGHT'><input class='button2' type='submit' value='RIGHT' ></form><br>"
    "<form id='F5' action='LEFT'><input class='button4' type='submit' value='LEFT' ></form><br>"
    "<form id='F2' action='STOP'><input class='button1' type='submit' value='STOP' ></form><br>"
    "</div>"
    "</body>"
    "</html>"
    ));   

 
    delay(5);
}

