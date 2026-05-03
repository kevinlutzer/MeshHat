#include <RadioLib.h>
#include <SPI.h>

static constexpr uint8_t NSS = 5;  // GPIO4  – SPI0 RX
static constexpr uint8_t DIO1 = 1;  // GPIO5  – SPI0 TX
static constexpr uint8_t NRST = 3;   // GPIO6  – SPI0 SCK
static constexpr uint8_t BUSY = 2;   // GPIO7  – chip-select (active LOW)

static constexpr uint8_t RF_PIN_MISO = 4;  // GPIO4  – SPI0 RX
static constexpr uint8_t RF_PIN_MOSI = 7;  // GPIO5  – SPI0 TX
static constexpr uint8_t RF_PIN_SCK = 6;   // GPIO6  – SPI0 SCK

SX1262 radio = new Module(NSS, DIO1, NRST, BUSY);

// save transmission states between loops
int transmissionState = RADIOLIB_ERR_NONE;

// flag to indicate transmission or reception state
bool transmitFlag = false;

// flag to indicate that a packet was sent or received
volatile bool operationDone = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial1.setRX(pin_size_t pin);
  Serial1.setTX(pin_size_t pin);

  delay(4000);

  SPI.setMISO(RF_PIN_MISO);
  SPI.setMOSI(RF_PIN_MOSI);
  SPI.setSCK(RF_PIN_SCK);   

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  // send the first packet on this node
  Serial.print(F("[SX1262] Sending first packet ... "));
  transmissionState = radio.startTransmit("Hello World!");
  transmitFlag = true;

  // start listening for LoRa packets on this node
  Serial.print(F("[SX1262] Starting to listen ... "));
  state = radio.startReceive();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

}

// the loop function runs over and over again forever
void loop() {
  Serial.printf("What the heck %d\n", radio.randomByte());
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second
}
