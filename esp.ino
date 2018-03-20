#include<SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "esp_ap";       //   SSID 
char pass[] = "12345678";    // паролааа

WiFiServer server(80);

char buff0[]="F\n";
char buff1[]="Q\n";
char buff2[]="B\n";
char buff3[]="W\n";
char buff4[]="L\n";
char buff5[]="E\n";
char buff6[]="R\n";
char buff7[]="T\n";
char buff8[]="S\n";


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

    if( request.indexOf("FORWARD_S") > 0 )  
    { 
      
      for(int i=0; i<sizeof buff0; i++)  
      {
        SPI.transfer(buff0[i]);
      }
      delay(1000); 
    }
    else if( request.indexOf("FORWARD_F") > 0 ) 
    { 
      for(int i=0; i<sizeof buff1; i++) 
      {
        SPI.transfer(buff1[i]);
      }
      delay(1000);  
    }


    else if( request.indexOf("BACKWARD_S") > 0 ) 
    { 
      for(int i=0; i<sizeof buff2; i++) 
        SPI.transfer(buff2[i]);
      delay(1000);   
    }
    else if( request.indexOf("BACKWARD_F") > 0 ) 
    { 
      for(int i=0; i<sizeof buff3; i++) 
        SPI.transfer(buff3[i]);
      delay(1000);   
    }


    else if( request.indexOf("LEFT_S") > 0 ) 
    { 
      for(int i=0; i<sizeof buff4; i++)  
        SPI.transfer(buff4[i]);
      delay(1000);   
    }
    else if( request.indexOf("LEFT_F") > 0 ) 
    { 
      for(int i=0; i<sizeof buff5; i++)  
        SPI.transfer(buff5[i]);
      delay(1000);   
    }


    else if( request.indexOf("RIGHT_S") > 0 ) 
    { 
      for(int i=0; i<sizeof buff6; i++) 
      {
        SPI.transfer(buff6[i]);
      }
      delay(1000);   
    }
    else if( request.indexOf("RIGHT_F") > 0 ) 
    { 
      for(int i=0; i<sizeof buff7; i++) 
      {
        SPI.transfer(buff7[i]);
      }
      delay(1000);   
    }

    
    else if( request.indexOf("STOP") > 0 ) 
    { 
      for(int i=0; i<sizeof buff8; i++) 
      {
        SPI.transfer(buff8[i]);
      }
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
    ".button5 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} "
    ".button6 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    ".button7 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    ".button8 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}"
    "</style>"
    "<title>Walkin Robot Control</title>"
    "</head>"
    "<body>"
    "<div id='main'><h2>WALKING ROBOT</h2>"
    "<form id='F1' action='FORWARD_S'><input class='button' type='submit' value='MOVE FORWARD SLOWLY' ></form><br>"
    "<form id='F2' action='FORWARD_F'><input class='button1' type='submit' value='MOVE FORWARD FAST' ></form><br>"
    "<form id='F3' action='BACKWARD_S'><input class='button2' type='submit' value='MOVE BACKWARD SLOWLY' ></form><br>"
    "<form id='F4' action='BACKWARD_F'><input class='button3' type='submit' value='MOVE BACKWARD FAST' ></form><br>"
    "<form id='F5' action='LEFT_S'><input class='button4' type='submit' value='MOVE LEFT SLOWLY' ></form><br>"
    "<form id='F6' action='LEFT_F'><input class='button5' type='submit' value='MOVE LEFT FAST' ></form><br>"
    "<form id='F7' action='RIGHT_S'><input class='button6' type='submit' value='MOVE RIGHT SLOWLY' ></form><br>"
    "<form id='F8' action='RIGHT_F'><input class='button7' type='submit' value='MOVE RIGHT FAST' ></form><br>"
    "<form id='F9' action='STOP'><input class='button8' type='submit' value='STOP' ></form><br>"
    "</div>"
    "</body>"
    "</html>"
    ));   

 
    delay(5);
}

