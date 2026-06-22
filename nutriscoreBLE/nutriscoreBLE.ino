#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define GREEN_LED_PIN D0  // Define the pin connected to the green LED
#define RED_LED_PIN D2    // Define the pin connected to the red LED
#define BLUE_LED_PIN D4   // Define the pin connected to the blue LED
#define BUTTON_PIN D5     // Define the pin connected to the push button

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *pServer = NULL;
BLEAdvertising *pAdvertising = NULL;

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Received RGB command: ");
      Serial.println(value);
      Serial.println("*********");

      // Parse the received RGB value (e.g., "255,0,0" for red, "0,255,0" for green)
      int r, g, b;
      if (sscanf(value.c_str(), "%d,%d,%d", &r, &g, &b) == 3) {
        // Constrain values to valid range 0-255
        r = constrain(r, 0, 255);
        g = constrain(g, 0, 255);
        b = constrain(b, 0, 255);

        // Set the LED colors
        analogWrite(RED_LED_PIN, r);   // Set red LED brightness
        analogWrite(GREEN_LED_PIN, g); // Set green LED brightness
        analogWrite(BLUE_LED_PIN, b);  // Set blue LED brightness
        
        // Log what color we set
        if (r > 0 && g == 0 && b == 0) {
          Serial.println("Setting LED to RED");
        } else if (r == 0 && g > 0 && b == 0) {
          Serial.println("Setting LED to GREEN");
        } else if (r > 0 && g > 0 && b == 0) {
          Serial.println("Setting LED to YELLOW");
        } else if (r == 0 && g == 0 && b > 0) {
          Serial.println("Setting LED to BLUE");
        } else if (r == 0 && g == 0 && b == 0) {
          Serial.println("Turning LED OFF");
        }
      } else {
        Serial.println("Invalid RGB format. Expected 'R,G,B'.");
        Serial.print("Received: ");
        Serial.println(value);
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE RGB LED Controller...");

  // Initialize the LED pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Initialize the button pin

  // Set initial state to off
  analogWrite(GREEN_LED_PIN, 0);
  analogWrite(RED_LED_PIN, 0);
  analogWrite(BLUE_LED_PIN, 0);

  // Initialize BLE
  BLEDevice::init("Nutriscore");
  pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Set an initial value
  pCharacteristic->setValue("RGB LED Controller Ready");
  pService->start();

  // Start advertising
  pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
  
  Serial.println("BLE Advertising started");
  Serial.println("Device Name: Nutri Score");
  Serial.println("Waiting for RGB commands...");
  
  // Blink all LEDs to show device is ready
  analogWrite(RED_LED_PIN, 255);
  delay(300);
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 255);
  delay(300);
  analogWrite(GREEN_LED_PIN, 0);
  analogWrite(BLUE_LED_PIN, 255);
  delay(300);
  analogWrite(BLUE_LED_PIN, 0);
  Serial.println("Ready!");
}

void loop() {
  // Check if device is connected, if not, restart advertising
  if (pServer->getConnectedCount() == 0) {
    static unsigned long lastAdvertisingTime = 0;
    if (millis() - lastAdvertisingTime > 5000) { // Check every 5 seconds
      Serial.println("No devices connected, restarting advertising...");
      pAdvertising->start();
      lastAdvertisingTime = millis();
    }
  }
  
  // Optional: Check button press for testing
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("Button pressed - Testing all colors");
      // Test sequence
      analogWrite(RED_LED_PIN, 255);
      analogWrite(GREEN_LED_PIN, 0);
      analogWrite(BLUE_LED_PIN, 0);
      delay(1000);
      analogWrite(RED_LED_PIN, 0);
      analogWrite(GREEN_LED_PIN, 255);
      analogWrite(BLUE_LED_PIN, 0);
      delay(1000);
      analogWrite(RED_LED_PIN, 0);
      analogWrite(GREEN_LED_PIN, 0);
      analogWrite(BLUE_LED_PIN, 255);
      delay(1000);
      analogWrite(RED_LED_PIN, 0);
      analogWrite(GREEN_LED_PIN, 0);
      analogWrite(BLUE_LED_PIN, 0);
      while (digitalRead(BUTTON_PIN) == LOW); // Wait for button release
    }
  }
  
  delay(100); // Small delay to prevent watchdog issues
}
