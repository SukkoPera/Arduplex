#include <Arduplex.h>

Multiplexer multiplexer;

void setup() {
  Serial.begin (9600);
  multiplexer.begin (2, 3, 4, Multiplexer::NO_INHIBIT);
}

void loop() {
  for (int i = 0; i < multiplexer.nPorts; i++) {
    Serial.println (i);
    multiplexer.select (i);
    delay (1000);
  }
}
