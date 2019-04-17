static byte mymac[] = { 
  0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

static void gotPinged (byte* ptr) {
  //ether.printIp(">>> ping from: ", ptr);
}


byte Ethernet::buffer[700];
static uint32_t timer;

boolean config_ethernet(){

  Serial.println("\n[pings]");
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0){
    Serial.println(F("Failed to access Ethernet controller"));
    return 0;
  }
  if (!ether.dhcpSetup()){
    Serial.println(F("DHCP failed"));
    return 0;
  }
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.parseIp(ether.hisip, "177.91.187.200");
  ether.printIp("SRV: ", ether.hisip);
  ether.registerPingCallback(gotPinged);

  timer = -9999999;
  Serial.println();
  return 1;
}


boolean ping() {
  int tempo = 200;
  while (tempo != 0) {
    word len = ether.packetReceive();
    word pos = ether.packetLoop(len);
    if (len > 0 && ether.packetLoopIcmpCheckReply(ether.hisip)) {
      flag_ping = 1;
      return 1;
    }
    if (millis() - timer >= 100) {
      timer = millis();
      ether.clientIcmpRequest(ether.hisip);
    }
    tempo--;
    delay(1);
  }
  flag_ping = 0;
  return 0;
}


void EN_PING(){
  if (!efeito_nota)
 if (millis() - t_ping >= 500){
    Serial.println("ping.......");
    digitalWrite(ENABLE,!ping());
    t_ping = millis(); 
  } 
}
