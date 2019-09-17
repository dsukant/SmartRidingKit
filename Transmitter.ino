#include <SPI.h>
#include <AIR430BoostFCC.h>

#define ADDRESS_LOCAL    0x02
#define ADDRESS_REMOTE   0x01

#define sensor P2_5

struct sPacket
{
  uint8_t from;          
  uint8_t message[1];    
};

struct sPacket txPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);

  txPacket.from = ADDRESS_LOCAL;
  memset(txPacket.message, 0, sizeof(txPacket.message));

  Serial.begin(9600);

  pinMode(sensor,INPUT);

}

void loop()
{

  if(digitalRead(sensor)==HIGH){
  txPacket.message[0] ='1';
  Radio.transmit(ADDRESS_REMOTE, (unsigned char*)&txPacket, sizeof(txPacket));
  }
  else{
  txPacket.message[0] ='0';
  Radio.transmit(ADDRESS_REMOTE, (unsigned char*)&txPacket, sizeof(txPacket));  
    }

  delay(500);
}
