#ifndef _PORT_H_
#define _PORT_H_

#include <driverlib.h>

#define DW1000_RSTn GPIO_PIN3
#define DW1000_RST_PORT GPIO_PORT_P5

void reset_DW1000(void);


#endif
