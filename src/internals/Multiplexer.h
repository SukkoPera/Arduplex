/* The CD4051B device is a single 8-channel multiplexer having three binary
 * control inputs, A, B, and C, and an inhibit input. The three binary signals
 * select 1 of 8 channels to be turned on, and connect one of the 8 inputs to
 * the output.
 *
 * This device can also be used as a demultiplexer.
 *
 * Full datasheet is available at: http://www.ti.com/lit/ds/symlink/cd4051b.pdf
 *
 * Wiring:
 * Choose 3 Arduino pins and connect them to the address pins (9, 10 and 11) of
 * the CD4051. You can also connect pin 6 if you want to be able to inhibit and
 * uninhibit the chip at will. Otherwise connect it to GND.
 */
class Multiplexer {
public:
  static const byte NO_INHIBIT = 255;
  static const byte MAX_ADDRESS_BITS = 4;
  byte nAddressBits;
  byte nPorts;

private:
  byte pins[MAX_ADDRESS_BITS];
  byte inhibitPin;

  void init () {
    nPorts = 1 << nAddressBits;

    for (byte i = 0; i < nAddressBits; i++) {
      pinMode (pins[i], OUTPUT);
    }

    if (inhibitPin != 255) {
      pinMode (inhibitPin, OUTPUT);
      inhibit (true);
    }
  }

public:
  /* If inhibit pin is not passed, chip will always be considered uninhibited.
   * If it is passed, it will be inhibited by default.
   *
   * This constructor is suitable for devices with 3 address bits, such
   * as CD4051, for instance.
   */
  void begin (byte a1Pin, byte a2Pin, byte a3Pin, byte _inhibitPin) {
    pins[0] = a1Pin;
    pins[1] = a2Pin;
    pins[2] = a3Pin;
    inhibitPin = _inhibitPin;
    nAddressBits = 3;

    init ();
  }

  /* This constructor is suitable for devices with 4 address bits, such
   * as CD4067, for instance.
   */
  void begin (byte a1Pin, byte a2Pin, byte a3Pin, byte a4Pin, byte _inhibitPin) {
    pins[0] = a1Pin;
    pins[1] = a2Pin;
    pins[2] = a3Pin;
    pins[3] = a4Pin;
    inhibitPin = _inhibitPin;
    nAddressBits = 4;

    init ();
  }

  boolean select (byte port) {
    if (port < nPorts) {
      for (byte i = 0; i < nAddressBits; i++) {
        digitalWrite (pins[i], !!(port & (1 << i)));
      }

      return true;
    } else {
      return false;
    }
  }

  // This will have no effect if _inhibitPin is not passed
  void inhibit (boolean doOrDont) {
    if (inhibitPin != 255)
      digitalWrite (inhibitPin, doOrDont);
  }
};
