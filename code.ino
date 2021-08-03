/* Interfacing I2C 24LC512 EEPROM to Arduino Uno
 *  
 * Hardware Component:
 *  Arduino Uno
 *  24LC512 EEPROM
 *  
 * Hardware Connection:
 *  SDA of Arduino Uno is connected to SDA of EEPROM
 *  SCK of Arduino Uno is connected to SCK of EEPROM
 *  
 *  Author - Sahana B G
 *  Date - 11 May 2021
 */

 // Header file
 #include<Wire.h>

 // Device address for EEPROM when A0,A1,A2 are grounded
 const uint8_t DEVICE_ADDRESS = 0x50;

 // Memory address to store data
 const uint16_t MEMORY_ADDRESS = 0XABEF;

 // Data to store in the above address
 const char DATA[] = "SAHANA";
 const uint8_t LEN = 6;
 
 void setup()
 {
  // Initialize I2C
  Wire.begin();

  // Initialize Serial Monitor
  Serial.begin(9600);
 } 

void loop()
{
  Serial.println("Writing data to EEPROM");
  Serial.print("Address = ");
  Serial.println(MEMORY_ADDRESS,HEX);
  Serial.print("Data =");
  
  uint16_t address = MEMORY_ADDRESS;
  for(int i=0; i<LEN;i++)
  {
    // Write data to EEPROM first 
    write_data_eeprom(DATA[i],address);
    address++;
    Serial.print(DATA[i]);
    delay(10);
  }
  Serial.println(" ");
  
  delay(500);

  // Read back the data
  Serial.println("Reading data from EEPROM");
  Serial.print("Address = ");
  Serial.println(MEMORY_ADDRESS,HEX);
  Serial.print("Data =");

  uint16_t readAddress = MEMORY_ADDRESS;
  for(int i=0;i<LEN;i++)
  {
    char data = read_data_eeprom(readAddress);
    readAddress++;
    Serial.print(data);
    delay(10);
  }
  Serial.println(" ");
}

void write_data_eeprom(char data,uint16_t address)
{
  //Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  // Send higher byte of memory address
  Wire.write((byte)(address>>8));

  // Send lower byte of memory address
  Wire.write((byte)(address & 0x00FF));

  // Send data to be stored
 // Wire.write((byte)DATA);
   Wire.write(data);

  // End the transmission
  Wire.endTransmission(); 
 }

char read_data_eeprom(uint16_t address)
{
 // Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  // Send higher byte of memory address
  Wire.write((byte)(address>>8));

  // Send lower byte of memory address
  Wire.write((byte)(address & 0x00FF));

  // End the transmission
  Wire.endTransmission(); 

  // Request 1 byte
  Wire.requestFrom((byte)DEVICE_ADDRESS,(byte)1);

  // Read the data 
  char receive_data = Wire.read();
  
  // End the transmission
  Wire.endTransmission();

  return receive_data;
}
