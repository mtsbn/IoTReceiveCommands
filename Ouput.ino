
void sLog(String message, bool line) {
  #ifdef DEBUG
    line ? Serial.println(message) : Serial.print(message);
  #endif
}


void initOutput () {
  //Output ports, defined by default for nodemcu v2. Alter for others boards
  //pinMode(16, OUTPUT); //D0
  //pinMode(5, OUTPUT);  //D1
  //pinMode(4, OUTPUT);  //D2
  //pinMode(0, OUTPUT);  //D3
  //pinMode(2, OUTPUT);  //D4
  pinMode(14, OUTPUT); //D5
  pinMode(12, OUTPUT); //D6
  //pinMode(13, OUTPUT); //D7
  //pinMode(15, OUTPUT); //D8
  //pinMode(3, OUTPUT);  //D9
  //pinMode(1, OUTPUT);  //D10
}

void initSerial() {
  Serial.begin(115200);
  sLog("");
}
