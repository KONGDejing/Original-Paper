
#ifndef _SERIAL_INPUT_H_
#define _SERIAL_INPUT_H_
#include "Arduino.h"


extern const char Flagbuffer[30];
extern bool Crack_success_Flag;
extern char Flaghackbuf[30];

void serial_initial();
void serial_read();


#endif
