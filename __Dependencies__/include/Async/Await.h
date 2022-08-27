
#define AwaitChange(value) 	while(value) {__asm volatile ("nop"); }