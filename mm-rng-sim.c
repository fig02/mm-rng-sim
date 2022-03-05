#include <stdio.h>
#include <stdlib.h>

char lotteryCodes[3][3];
char spiderHouseMaskOrder[6];
char spiderHouseMaskString[6];
char bomberCode[5];

unsigned int sRandInt;
unsigned int sRandFloat;

float Rand_ZeroOne(void) {
    sRandInt = (sRandInt * 1664525) + 1013904223;
    sRandFloat = ((sRandInt >> 9) | 0x3F800000);
    return *((float*)&sRandFloat) - 1.0f;
}

short Rand_S16Offset(short base, short range) {
    return (short)(Rand_ZeroOne() * range) + base;
}

void Sram_GenerateRandomSaveFields() {
    lotteryCodes[0][0] = Rand_S16Offset(0, 10);
    lotteryCodes[0][1] = Rand_S16Offset(0, 10);
    lotteryCodes[0][2] = Rand_S16Offset(0, 10);
    lotteryCodes[1][0] = Rand_S16Offset(0, 10);
    lotteryCodes[1][1] = Rand_S16Offset(0, 10);
    lotteryCodes[1][2] = Rand_S16Offset(0, 10);
    lotteryCodes[2][0] = Rand_S16Offset(0, 10);
    lotteryCodes[2][1] = Rand_S16Offset(0, 10);
    lotteryCodes[2][2] = Rand_S16Offset(0, 10);

    char i = 0;
    char prevSpiderDigit = Rand_S16Offset(0, 16) & 3;
    char max = 6;

    while (i != max) {
        char randSpiderDigit = Rand_S16Offset(0, 16) & 3;
        if (prevSpiderDigit != randSpiderDigit) {
            spiderHouseMaskOrder[i] = randSpiderDigit;
            i++;
            prevSpiderDigit = randSpiderDigit;
        }
    }

    char randBombers;

    do {
        randBombers = Rand_S16Offset(0, 6);
    } while (randBombers <= 0 || randBombers >= 6);

    bomberCode[0] = randBombers;

    i = 1;
    while (i != 5) {
        char k = 0;

        do {
            randBombers = Rand_S16Offset(0, 6);
        } while (randBombers <= 0 || randBombers >= 6);

        char index = 0;

        do {
            if (randBombers == bomberCode[index]) {
                k = 1;
            }
            index++;
        } while (index < i);

        if (k == 0) {
            bomberCode[i] = randBombers;
            i++;
        }
    }
}

void convert_spider_code() {
    for (int i = 0; i < 6; i++) {
        char num = spiderHouseMaskOrder[i];
        char col;

        switch (num) {
            case 0:
                col = 'R';
                break;
            case 1:
                col = 'B';
                break;
            case 2:
                col = 'Y';
                break;
            case 3:
                col = 'G';
                break;
        }

        spiderHouseMaskString[i] = col;
    }
}

void main() {
    printf("MM RNG Save Codes Simulator\n");
    printf("\n");

    while (1) {
        printf("Enter a starting seed: ");
        scanf("%8X", &sRandInt);
        Sram_GenerateRandomSaveFields();
        printf("bombers code: %d%d%d%d%d\n", bomberCode[0], bomberCode[1], bomberCode[2], bomberCode[3], bomberCode[4]);
        
        convert_spider_code();
        printf("spider house: %c%c%c%c%c%c\n", spiderHouseMaskString[0], spiderHouseMaskString[1], spiderHouseMaskString[2], 
                                               spiderHouseMaskString[3], spiderHouseMaskString[4], spiderHouseMaskString[5]);

        printf("lottery code: %d%d%d %d%d%d %d%d%d\n", 
                    lotteryCodes[0][0], lotteryCodes[0][1], lotteryCodes[0][2],
                    lotteryCodes[1][0], lotteryCodes[1][1], lotteryCodes[1][2],
                    lotteryCodes[2][0], lotteryCodes[2][1], lotteryCodes[2][2]);

        printf("next seed: %8X\n", sRandInt);
        printf("\n");
    }

}