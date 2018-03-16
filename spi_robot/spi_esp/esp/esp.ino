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


String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} .button1 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} { padding:10px 10px 10p</style><title>LED Control</title></head><body><div id='main'><h2>WALKING ROBOT</h2>";
String html_2 = "<form id='F1' action='FORWARD'><input class='button' type='submit' value='move forward' ></form><br>";
String html_3 = "<form id='F1' action='STOP'><input class='button1' type='submit' value='STOP' ></form><br>";
String html_4 = "</div></body></html>";
//String html_5 = "<form id='F1' action='RIGHT'><input class='button2' type='submit' value='TURN RIGHT' ></form><br>";
////String html_6 = "<form id='F1' action='BACKWARD'><input class='button3' type='submit' value='TURN RIGHT' ></form><br>";
////String html_7 = "<form id='F1' action='LEFT'><input class='button4' type='submit' value='TURN RIGHT' ></form><br>";


String request = "";

void setup() {
 Serial.begin(9600); /* begin serial with 9600 baud */
 SPI.begin();  /* begin SPI */

 WiFi.mode(WIFI_AP);         
 WiFi.softAP(ssid, pass);  
 IPAddress myIP = WiFi.softAPIP(); 
 Serial.print("HotSpt IP:");
 Serial.println(myIP);
 
  
 server.begin();              
 Serial.println("HTTP server started");
}

void loop() {
//  String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} .button1 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} .button2 { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>LED Control</title></head><body><div id='main'><h2>WALKING ROBOT</h2>";
//String html_2 = "<form id='F1' action='FORWARD'><input class='button' type='submit' value='move forward' ></form><br>";
//String html_3 = "<form id='F1' action='STOP'><input class='button1' type='submit' value='STOP' ></form><br>";
//String html_4 = "</div></body></html>";
//String html_5 = "<form id='F1' action='RIGHT'><input class='button2' type='submit' value='TURN RIGHT' ></form><br>";
//String html_6 = "<form id='F1' action='BACKWARD'><input class='button3' type='submit' value='TURN RIGHT' ></form><br>";
//String html_7 = "<form id='F1' action='LEFT'><input class='button4' type='submit' value='TURN RIGHT' ></form><br>";


  WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    request = client.readStringUntil('\n');
 
    if( request.indexOf("FORWARD") > 0 )  
    { 
      for(int i=0; i<sizeof buff; i++)  /* transfer buff data per second */
        SPI.transfer(buff[i]);
      delay(1000); 
    }
    else if( request.indexOf("STOP") > 0 ) 
    { 
      for(int i=0; i<sizeof buff1; i++)  /* transfer buff data per second */
        SPI.transfer(buff1[i]);
      delay(1000);  
    }
//    else if( request.indexOf("RIGHT") > 0 ) 
//    { 
//      for(int i=0; i<sizeof buff2; i++)  /* transfer buff data per second */
//        SPI.transfer(buff2[i]);
//      delay(1000);   
//    }
//    else if( request.indexOf("BACKWARD") > 0 ) 
//    { 
//      for(int i=0; i<sizeof buff3; i++)  /* transfer buff data per second */
//        SPI.transfer(buff3[i]);
//      delay(1000);   
//      //html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='Turn on the LED' ></form><br>";
//    }

//    else if( request.indexOf("LEFT") > 0 ) 
//    { 
//      for(int i=0; i<sizeof buff4; i++)  /* transfer buff data per second */
//        SPI.transfer(buff4[i]);
//      delay(1000);   
//      //html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='Turn on the LED' ></form><br>";
//    }

  client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
    //client.print( html_6 );
    //client.print( html_5);
    //client.print( html_7);
    client.print( html_3);
    client.print( html_4);
 
    delay(5);
 //for(int i=0; i<sizeof buff; i++)  /* transfer buff data per second */
  //SPI.transfer(buff[i]);
 //delay(1000);  
}
