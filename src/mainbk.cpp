#include <Arduino.h>
#include <SPI.h>
#include "lib\Motors.h"
#include "lib\tof.h"

// #include<Adafruit_NeoPixel.h>

#include "lib\pathfinding\API.h"
#include "./../maze/maze.hpp"
// #include "lib\trueNorth.h"

Motors* motors;

void setup() {
  Serial.begin(9600);
    

  delay(5000);
  
  initialize();
  runMaze('c');
  backTrack();

  // API::turnLeft();
  // API::moveForward();
  // API::moveForward();


}

void loop() {
  
  // timeofflight_instance->readDistance();
  // Serial.println(imu_instance->getHeading());

}