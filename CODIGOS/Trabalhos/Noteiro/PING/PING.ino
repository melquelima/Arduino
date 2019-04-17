#include <EtherCard.h>
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

static void gotPinged (byte* ptr) {
  //ether.printIp(">>> ping from: ", ptr);
}

void setup () {
  Serial.begin(9600);
  Serial.println("\n[pings]");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.parseIp(ether.hisip, "177.91.187.200");
  ether.printIp("SRV: ", ether.hisip);
  ether.registerPingCallback(gotPinged);

  timer = -9999999;
  Serial.println();
}

void loop () {
  while (1) {
    Serial.println(ping());
  }
}


boolean ping() {
  int tempo = 3000;
  while (tempo != 0) {
    word len = ether.packetReceive();
    word pos = ether.packetLoop(len);
    if (len > 0 && ether.packetLoopIcmpCheckReply(ether.hisip)) {
      return 1;
    }
    if (millis() - timer >= 100) {
      timer = millis();
      ether.clientIcmpRequest(ether.hisip);
    }
    tempo--;
    delay(1);
  }
  return 0;
}
