#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "displaytask.hpp"
#include <TaskScheduler.h>

ESP8266WebServer server(80);


namespace {

Scheduler                  taskScheduler;
Tasks::DisplayTask         dispayTask;
}

void handleRoot();

void setup()
{
   Serial.begin(9600);

   server.on("/", handleRoot);


   WiFi.softAP("AP", "AP-password");

    taskScheduler.addTask( dispayTask );
    dispayTask.enable();


   Serial.println(F("Setup completed"));
   Serial.println(WiFi.softAPIP());

   server.begin();
}

void loop()
{
   server.handleClient();
   taskScheduler.execute();
}

void handleRoot()
{
    if (server.hasArg("text")){
        String s = server.arg("text");
        dispayTask.setText(s.c_str());
        Serial.println(s);
        server.send(200, "text/plain", "Got it!"); 
    }
    else
    {
        Serial.println("No text provided");
        server.send(200, "text/plain", "No text provided!"); 
    }
}
