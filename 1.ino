#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>

const char* ssid = "A30";
const char* password = "15121472";
MDNSResponder mdns;

ESP8266WebServer server(80);

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4

       

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>ESP8266 Demo</title></head>" \
                "<body>" \
                  "<h1>Hello from ESP8266, you can send NEC encoded IR" \
                      "signals from here!</h1>" \                                     
                      "<p><a href=\"ir?code=CD364887\">Send left hand up</a></p>" \           
                  "<p><a href=\"ir?code=DE3AD379\">Send right hand up</a></p>" \
                  "<p><a href=\"ir?code=744F598C\">Send Left Hand Down</a></p>" \
                  "<p><a href=\"ir?code=FC055B44\">Send Right Hand Down</a></p>" \
                  "<p><a href=\"ir?code=714F54D5\">Send Left Hand In</a></p>" \
                  "<p><a href=\"ir?code=F905568D\">Send Right Hand In</a></p>" \
                  "<p><a href=\"ir?code=5A872050\">Send Left Hand Out</a></p>" \
                  "<p><a href=\"ir?code=6B267EBA\">Send Right Hand Out</a></p>" \
                  "<p><a href=\"ir?code=59871EBF\">Send Tilt Left</a></p>" \
                  "<p><a href=\"ir?code=6A267D29\">Send Tilt Right</a></p>" \
                  "<p><a href=\"ir?code=806D9980\">Send Move Forward</a></p>" \
                  "<p><a href=\"ir?code=7F6D97EF\">Move Backward</a></p>" \
                  "<p><a href=\"ir?code=E13AD830\">Send turn right</a></p>" \
                  "<p><a href=\"ir?code=CC3646F2\">Send turn left</a></p>" \
                  "<p><a href=\"ir?code=8239B38\">Send stop</a></p>" \
                  "<p><a href=\"ir?code=FDD80FB6\">Send R>> </a></p>" \
                  "<p><a href=\"ir?code=FCD80E25\">Send L>> </a></p>" \
                  "<p><a href=\"ir?code=1685CBA\">Send S>> </a></p>" \
                  "<p><a href=\"ir?code=73EC692C\">Send P </a></p>" \
                  "<p><a href=\"ir?code=70EC6475\">Send <<P>> </a></p>" \
                  "<p><a href=\"ir?code=8F4434CF\">Send Right thumbs up </a></p>" \
                  "<p><a href=\"ir?code=A4EA2959\">Send left thumbs up </a></p>" \        
                  "<p><a href=\"ir?code=A90EB64E\">Send Right pick up</a></p>" \
                  "<p><a href=\"ir?code=3566219E\">Send Left pick up </a></p>" \
                  "<p><a href=\"ir?code=AA0EB7E3\">Send Right lean forward</a></p>" \
                  "<p><a href=\"ir?code=36662333\">Send Left lean forward</a></p>" \
                  "<p><a href=\"ir?code=1C950C98\">Send Right throw </a></p>" \
                  "<p><a href=\"ir?code=31D5D49A\">Send left throw </a></p>" \
                  "<p><a href=\"ir?code=1B950B07\">Send Listen </a></p>" \
                  "<p><a href=\"ir?code=30D5D309\">Send Sleep </a></p>" \
                  "<p><a href=\"ir?code=41846192\">Send Step </a></p>" \
                  "<p><a href=\"ir?code=8E44333A\">Send Right turn step </a></p>" \
                  "<p><a href=\"ir?code=A7EA2E10\">Send Left turn step </a></p>" \
                  "<p><a href=\"ir?code=40846001\">Send back step </a></p>" \
                  "<p><a href=\"ir?code=B52CF642\">Send Reset </a></p>" \
                  "<p><a href=\"ir?code=95FA735D\">Send left </a></p>" \
                  "<p><a href=\"ir?code=96FA74EE\">Send Right </a></p>" \
                  "<p><a href=\"ir?code=9A8AC1F2\">Send Sonic </a></p>" \
                  "<p><a href=\"ir?code=D0ECE64\">Send Execute </a></p>" \
                  "<p><a href=\"ir?code=A0EC9AD\">Send Wakeup </a></p>" \
                  "<p><a href=\"ir?code=678E250D\">Send Right sweep </a></p>" \                
                  "<p><a href=\"ir?code=56899A1B\">Send left sweep</a></p>" \
                  "<p><a href=\"ir?code=8558ACD8\">Send Talk back </a></p>" \
                  "<p><a href=\"ir?code=FDA2AB20\">Send High five</a></p>" \
                  "<p><a href=\"ir?code=8258A821\">Send Right strike 1 </a></p>" \
                  "<p><a href=\"ir?code=FAA2A669\">Send left strike 1 </a></p>" \
                  "<p><a href=\"ir?code=F479D04E\">Send whistle</a></p>" \
                  "<p><a href=\"ir?code=E3DA71E4\">Send Burp </a></p>" \
                  "<p><a href=\"ir?code=F379CEBD\">Send right strike 2 </a></p>" \
                  "<p><a href=\"ir?code=E2DA7053\">Send left strike 2 </a></p>" \
                  "<p><a href=\"ir?code=9C0EB14\">Send bulldozer </a></p>" \
                  "<p><a href=\"ir?code=8C0E983\">Send OOps </a></p>" \
                  "<p><a href=\"ir?code=6A8E29C4\">Send right strike 3 </a></p>" \
                  "<p><a href=\"ir?code=55899886\">Send left strike 3 </a></p>" \
                  "<p><a href=\"ir?code=9176ECCC\">Send roar </a></p>" \
                  "<p><a href=\"ir?code=872B614A\">Send demo 1 </a></p>" \
                  "<p><a href=\"ir?code=862B5FB9\">Send demo 2 </a></p>" \
                  "<p><a href=\"ir?code=8ABBAE4E\">Send dance </a></p>" \
                  "<p><a href=\"ir?code=FD3FBAC0\">Send all demo </a></p>" \
                  "<p><a href=\"ir?code=FA3FB609\">Send power off </a></p>" \

                 
                                   
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 16);
       Serial.println(code);
      
     if(code==3442886791){
      uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CD364887 Left Hand Up"); break;}
       if(code==3728397177){
     uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up"); break;}
      if(code==1951357324){
      uint16_t  rawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("744F598C Left Hand Down"); break;}
       if(code==4228209476){
       uint16_t    rawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down"); break;}
      
       if(code==1901024469 ){
      uint16_t rawData[17] = {7250,3350, 950,850, 900,900, 950,850, 950,850, 950,3400, 900,900, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("714F54D5 Left Hand In"); break;}
      if(code==4177876621 ){
      uint16_t  rawData[17] = {7150,3400, 950,850, 950,850, 950,850, 950,3400, 900,3400, 900,900, 900,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("F905568D Right Hand In"); break;}
      if(code== 1518805072 ){
       uint16_t  rawData[17] = {7250,3400, 900,850, 1000,850, 950,850, 950,900, 900,900, 950,3350, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("5A872050 Left Hand Out"); break;}
      if(code==1797684922 ){
        uint16_t  rawData[17] = {7200,3400, 900,900, 900,900, 950,900, 900,3350, 950,850, 900,3450, 900,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6B267EBA Right Hand Out"); break;}
      if(code==1502027455 ){
      uint16_t rawData[17] = {7200,3400, 900,950, 850,950, 900,900, 900,900, 950,850, 950,3400, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("59871EBF Tilt Left"); break;}
      if(code==1780907305 ){
      uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 950,3350, 1000,850, 950,3350, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6A267D29 Tilt Right"); break;}
      if(code==2154666368 ){
      uint16_t  rawData[17] = {7250,3300, 1000,850, 950,850, 950,850, 950,850, 950,3350, 1000,3300, 1000,800, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("806D9980 Move Forward"); break;}
      
      if(code==2137888751){
      uint16_t  rawData[17] = {7200,3400, 950,850, 950,850, 950,900, 900,900, 900,3400, 950,3350, 950,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("7F6D97EF Move Backward"); break;}
      if(code==3778730032){
 
      uint16_t  rawData[17] = {7250,3350, 1000,850, 950,850, 950,850, 950,3350, 950,850, 1000,850, 950,850, 950};     
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("E13AD830 Turn Right"); break;}
      if(code==3426109170 ){
       uint16_t rawData[17] = {7250,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,800, 1000}; 
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CC3646F2 Turn Left"); break;}
      if(code==136551224){
      uint16_t  rawData[17] = {7250,3350, 900,900, 950,850, 950,850, 950,3400, 950,3350, 950,3350, 950,850, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("8239B38   Stop"); break;}
      if(code==4258795446){
        uint16_t rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDD80FB6 R >>"); break;
        }
      if(code==4242017829){
        uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,3300, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FCD80E25 L >>"); break;}
       if(code==23616698){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,850, 950,3350, 950,850, 950,3350, 1000,800, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1685CBA     S >>"); break;}
       if(code==1944873260){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,900, 950,3300, 1000,850, 950,850, 1000,850, 950,850, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("73EC692C P"); break;}
      if(code==1894540405){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,800, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("70EC6475 <<P>> "); break;}
      if(code==2403611855){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3400, 950,850, 1000,3300, 1000,850, 950,850, 950,3400, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8F4434CF Right Thumbs Up"); break;}
      if(code==2766809433){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A4EA2959 Left Thumbs Up"); break;}
      if(code==2836313678){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,850, 950,3350, 1000,3300, 1000,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A90EB64E Right Pick Up"); break;}
      if(code==895885726){
        uint16_t rawData[17] = {7250,3400, 900,900, 950,3350, 1000,850, 900,900, 950,3350, 1000,850, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("3566219E   Left Pick Up"); break;}
      if(code==2853091299){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3350, 1000,850, 950,3350, 1000,3300, 1000,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("AA0EB7E3 Righ Lean Forward"); break;}
      if(code==912663347){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 900,900, 900,3400, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("36662333   Left Lean Forward"); break;}
      if(code==479530136){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3350, 1000,800, 1000,3350, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1C950C98   Right Throw"); break;}
      if(code==836097178){
        uint16_t rawData[17] = {7200,3400, 950,850, 950,3400, 950,850, 950,850, 950,900, 900,3400, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("31D5D49A   Left Throw"); break;}
      if(code==462752519){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3350, 950,850, 950,3400, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1B950B07   Listen"); break;}
      if(code==819319561){
        uint16_t  rawData[17] = {7250,3350, 1000,850, 950,3350, 950,850, 1000,850, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("30D5D309   Sleep"); break;}
      if(code==1099194770){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step"); break;}
      if(code==2386834234){
        uint16_t rawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8E44333A Right Turn Step"); break;}
      if(code==2817142288){
        uint16_t rawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step"); break;}
      if(code==1082417153){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("40846001 Back Step"); break;}
      if(code==3039622722){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,3350, 950,850, 950,3350, 950,3350, 1000,3300, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("B52CF642 Reset"); break;}
      if(code==2516218717){
        uint16_t  rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,3300, 1000,800, 1000,850, 1000,3300, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("95FA735D Left"); break;} 
      if(code==2532996334){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1050,800, 1000,800, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("96FA74EE Right"); break;   }                  
      if(code==2592784882){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,3300, 1000,850, 950,3350, 950,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9A8AC1F2 Sonic"); break;     }                  
     if(code==219074148){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 950,3350, 1000,800, 1000,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("D0ECE64   Execute"); break;}                  
     if(code==168741293){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1000,850, 1000,800, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A0EC9AD   Wake Up"); break; }                  
     if(code==1737368845){
        uint16_t rawData[17] = {7200,3400, 950,3350, 1000,800, 1000,850, 950,3350, 1000,800, 1000,850, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("678E250 Right Sweep"); break;       }                  
    if(code==1451858459){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,850, 950,850, 950,850, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("56899A1B Left Sweep"); break; }                  
    if(code==2237181144){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,850, 1000,3350, 950,3350, 950,900, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8558ACD8 Talk Back"); break; }                  
    if(code==4255296288){
        uint16_t rawData[17] = {7300,3300, 1000,3350, 950,850, 950,850, 1000,850, 1000,3300, 1000,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDA2AB20 High Five"); break; }                  
    if(code==2186848289){
        uint16_t rawData[17] = {7250,3400, 950,3350, 950,850, 1000,850, 950,3350, 950,3400, 900,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8258A821 Right Strike 1 "); break;}                  
    if(code==4204963433){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 900,900, 950,850, 1000,3350, 950,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FAA2A669 Left Strike 1"); break; }                  
    if(code==4101623886){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 1000,850, 950,3300, 1000,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F479D04E Whistle"); break; }                  
    if(code==3822744036){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,850, 950,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E3DA71E4 Burp"); break; }                  
    if(code==4084846269){
        uint16_t rawData[17] = {7300,3350, 950,3350, 950,900, 950,850, 950,3350, 1000,850, 950,3350, 950,3400, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F379CEBD Right Strike 2"); break; }                  
    if(code==3805966419){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,800, 950,900, 950,850, 950,3350, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E2DA7053 Left strike 2"); break;}                  
    if(code==163638036){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,900, 950,850, 950,3350, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9C0EB14   Bulldozer"); break; }                  
    if(code==146860419){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8C0E983   Oops"); break; }                  
   if(code==1787701700){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("6A8E29C4 Right Strike 3"); break; }                  
   if(code==1435080838){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 950,850, 1000,850, 950,850, 1000,800, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("55899886 Left strike 3"); break; }   
   if(code==2440490188){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,800, 950,3400, 950,3350, 950,3400, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9176ECCC Roar"); break; }   
   if(code==2267767114){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("872B614A Demo 1"); break; }  
   if(code==2250989497){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,3300, 1000,850, 950,850, 950,3350, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("862B5FB9 Demo 2"); break; }
   if(code==2327555662){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3350, 950,850, 1000,3300, 1050,800, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8ABBAE4E Dance"); break;}            
   if(code==4248812224){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,800, 1000,3350, 1000,800, 1000,850, 950,850, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FD3FBAC0 All Demo"); break; }   
   if(code==4198479369){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FA3FB609 Power OFF"); break;   }                                                                                                                                                              
      

      
       }
  
    
    }
  
  handleRoot();
  }

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

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

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  
}
