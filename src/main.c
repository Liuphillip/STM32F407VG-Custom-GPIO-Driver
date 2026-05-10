#include <stdint.h>

volatile uint8_t Flag = 0;

int main(void){
    
    while(1){
        if (Flag) break;
    }
    while(1){
    }
    return 0;
}