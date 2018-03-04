#ifndef SERIAL_H
#define SERIAL_H

#include <stm8s.h>

///
/// \brief setUpSerial start serial communication
/// at 9600 Baud Rate
///
void setUpSerial();

void putchar(char c);

#endif // SERIAL_H
