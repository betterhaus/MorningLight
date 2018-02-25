#include "../Haussteuerung/RCSwitch.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SYSTEMCODE  "11011"
#define ROT         "01"
#define BLAU        "11"
#define GRUEN       "10"
#define ALLEFARBEN  "00"



int main(void){
    int PIN = 0;
    char sWert[8];
    char buffer[100];

    if (wiringPiSetup () == -1) return 1;

    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);
    printf("Init done\n");

    for(int i = 1; i < 255; i++){
        int bit = 0;
        for (int j = 0; j < 8; j++){
            bit =  i >> j;
            if (bit & 1)
                sWert[7-j]='1';
            else
                sWert[7-j]='0';
        }
        sprintf(buffer, "%s %s %s", SYSTEMCODE,ALLEFARBEN, sWert);
        printf("Sending: %s\n", buffer);
        mySwitch.send(buffer);
        memset(buffer, 0, sizeof(char)*100);
        usleep(2000000);
    }
}

