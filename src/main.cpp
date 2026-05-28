#include <Arduino.h>
#include <AS5600.h>

#define POWER_LED 23

// I2C0 pins (Encoder 1)
#define I2C0_SDA 21
#define I2C0_SCL 22

// I2C1 pins (Encoder 2)
#define I2C1_SDA 18
#define I2C1_SCL 19

// Bus speed
#define bus_speed 100000

// Two I2C buses
TwoWire I2C_Bus0 = TwoWire(0);
TwoWire I2C_Bus1 = TwoWire(1);

// AS5600 objects
AS5600 encoder1(&I2C_Bus0);
AS5600 encoder2(&I2C_Bus1);

void setup() {
  // Begin serial communication
  Serial.begin(115200);
  while(!Serial);
  Serial.println("----------------------------");
  Serial.println("Serial communication established");

  // Get board information
  Serial.println("----------------------------");
  Serial.println(ESP.getChipModel());
  Serial.println(ARDUINO_BOARD);
  Serial.println("----------------------------");

  // Turn on power led pin
  pinMode(POWER_LED, OUTPUT);
  delay(200);
  digitalWrite(POWER_LED, HIGH);

  // I2C interfaces initialization
  I2C_Bus0.begin(I2C0_SDA, I2C0_SCL, bus_speed);
  delay(200);
  Serial.println("Bus 0 initialized");
  I2C_Bus1.begin(I2C1_SDA, I2C1_SCL, bus_speed);
  delay(200);
  Serial.println("Bus 1 initialized");
  Serial.println("----------------------------");

  // AS5600 initialization
  encoder1.begin();
  delay(200);
  encoder2.begin();
  delay(200);

  if (encoder1.isConnected()) {
        Serial.println("Encoder 1: CONNECTED");
    } else {
        Serial.println("Encoder 1: ERROR");
    }

    if (encoder2.isConnected()) {
        Serial.println("Encoder 2: CONNECTED");
    } else {
        Serial.println("Encoder 2: ERROR");
    }
  Serial.println("----------------------------");

}

void loop() {
  // The AS5600 has a 12-bit resolution, meaning it reads from 0 to 4095
    uint16_t rawAngle1 = encoder1.readAngle();
    uint16_t rawAngle2 = encoder2.readAngle();

    // Convert the raw 12-bit integer into a 360-degree floating point value
    float degAngle1 = rawAngle1 * (360.0 / 4096.0);
    float degAngle2 = rawAngle2 * (360.0 / 4096.0);

    // Print the results side-by-side
    Serial.print("Joint 1: ");
    Serial.print(degAngle1, 2); // Print with 2 decimal places
    Serial.print("° \t|\t Joint 2: ");
    Serial.print(degAngle2, 2);
    Serial.println("°");

    delay(100);
}