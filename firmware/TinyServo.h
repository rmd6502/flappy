#include <stdint.h>

#define NUM_SERVOS 11

class TinyServo
{
  private:
  public:
    TinyServo();
    void attach(uint8_t servoNumber);
    void detach(uint8_t servoNumber);
    void write(uint8_t servoNumber, float angle);
};

extern TinyServo tinyServo;
