const int start_button = 0;
const int hall_input = 1;
const int led = 2;
const int adc_reference = 3;
const int sck = 4;
const int miso = 5;
const int mosi = 6;
const int speaker = 7;
const int lid_servo = 8;
const int character_servo = 9;
const int roll_servo = 10;

// ISP Header
//           +------+
//MISO/TXD  1| *  * |  Vcc
//           |      |
//SCK/RXD    | *  * |  MOSI
//           |      |
//RESET      | *  * |  GND
//           +------+

// TXD and rXD are from the point of view of the chip,
// So TXD goes to you cable's RXD, and RXD to cable TXD
