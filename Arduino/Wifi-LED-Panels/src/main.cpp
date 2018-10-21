#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "displaytask.hpp"
#include <TaskScheduler.h>

ESP8266WebServer server(80);


namespace {

Scheduler                  taskScheduler;
Tasks::DisplayTask         displayTask;
}

void handleRoot();

void setup()
{
   Serial.begin(9600);

   server.on("/", handleRoot);


   WiFi.softAP("AP", "AP-password");

    taskScheduler.addTask( displayTask );
    displayTask.enable();


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
        displayTask.setText(s.c_str());
        Serial.println(s);
        server.send(200, "text/plain", "Got it!"); 
    }
    if (server.hasArg("font")){
        int s = server.arg("font").toInt();
        switch (s)
        {
            case 0:
            displayTask.setFont(Tasks::DisplayTask::FONT7x5);
            break;
            case 1:
            displayTask.setFont(Tasks::DisplayTask::FONT8x8);
            break;
            default:
            break;
        }
        Serial.println(s);
        server.send(200, "text/plain", "Got it!");
    }
    if (server.hasArg("speed")){
        int s = server.arg("speed").toInt();
        displayTask.setSpeed(s);
        Serial.println(s);
        server.send(200, "text/plain", "Got it!");
    }
    if (server.hasArg("snake")){
        int s = server.arg("snake").toInt();
        displayTask.setSnakeDir(s);
        server.send(200, "text/plain", "Got it!");
    }
}
