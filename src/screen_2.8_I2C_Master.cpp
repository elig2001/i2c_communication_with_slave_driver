

#include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI
#include <Wire.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>

#include "src/graphics/draw_screen.h"
#include "src/i2c_communication/types.h"
#include "src/i2c_communication/i2c_commuication.h"

//  background light pin
#define ENABLE_SCREEN  \
  pinMode(27, OUTPUT); \
  digitalWrite(27, HIGH);

#define SLAVE_ADDRESS 0x28

static void print_result(uint8_t slave_address, uint8_t length);
static void send_command(uint8_t slave_address, command_id_e command, resource_type_e resource_type, uint8_t length);
static void read_serial_number(uint8_t slave_address);
static bool send_sanity(uint8_t slave_address);

byte dataToSend = 0x42; // Data to send

//-------------- BlueTooth ------------------------------
BluetoothSerial SerialBT;
uint8_t BT_enable;
char DeviceName[30];

uint16_t error;
char errorMessage[256];

TFT_eSPI g_tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h

uint32_t runTime = -99999; // time for next update

uint8_t temp[10];

uint32_t new_serial_number = 0xaaaabbbb;

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");

  Wire.begin();

  // Wire.setTimeOut(0);

  sprintf(DeviceName, "CRUSOE-O2 pressure", 1);
  Serial.println(DeviceName);

  SerialBT.begin(DeviceName); // Bluetooth device name

  // Initialise the screen
  g_tft.init();

  // Ideally set orientation for good viewing angle range because
  // the anti-aliasing effectiveness varies with screen viewing angle
  // g_tft.setRotation();

  g_tft.fillScreen(TFT_BLACK);

  ENABLE_SCREEN

  // delay is here to give my serial monitor time to start
  delay(2000);

  Serial.printf("New Send Sanity result: (%d)\n", i2c_communication__check_connection(SLAVE_ADDRESS));

  if (COMMAND_RESULT__SUCCESS != i2c_communication__read_serial_number(SLAVE_ADDRESS, temp))
  {
    Serial.printf("Read serial number failed\n");
  }

  else

  {
    Serial.printf("Serial number bytes are: \n");
    for (size_t i = 0; i < 4; i++)
    {
      Serial.printf("%d. %d\n", i, temp[i]);
    }
  }

  if (COMMAND_RESULT__SUCCESS != i2c_communication__write_serial_number(SLAVE_ADDRESS, (uint8_t *)&new_serial_number))
  {
    Serial.printf("write failed\n");
  }
  else
  {

    Serial.printf("Write success!\n");

    if (COMMAND_RESULT__SUCCESS != i2c_communication__read_serial_number(SLAVE_ADDRESS, temp))
    {
      Serial.printf("Read serial number failed\n");
    }

    else
    {

      Serial.printf("Serial number bytes are: \n");

      for (size_t i = 0; i < 4; i++)
      {
        Serial.printf("%d. %d\n", i, temp[i]);
      }

    }
  }

}

void loop()
{
}
