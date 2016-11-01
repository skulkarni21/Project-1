#include "MKL25Z4.h"
#include "circbuff.h"
#include "LED.h"
#include "log.h"

#define MAX_SIZE_DATA 2

typedef enum Cmds_t{
	LED_RED = 0x01,
	LED_BLUE = 0x02,
	LED_GREEN = 0x03
}Cmds;

typedef struct CI_Msg_t{
	Cmds command;
	uint8_t length;
	uint8_t data[MAX_SIZE_DATA];
	uint8_t checksum;
}CI_Msg;

void Decode_CI_Msg(CI_Msg* msg);
void Read_CI_Msg(CI_Msg*msg);