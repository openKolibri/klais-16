#ifndef _SEG_MAP_H
#define _SEG_MAP_H

// List of refrence desegnators in each segment
static unsigned char segA[] = {1, 2, 3, 4, 9, 10, 11, 12};
static unsigned char segB[] = {5, 6, 7, 8, 13, 14, 15, 16};
static unsigned char segC[] = {23, 24, 39, 32, 47, 40, 48};
static unsigned char segD[] = {71, 72, 79, 80, 95, 88, 96};
static unsigned char segE[] = {109, 110, 111, 103, 117, 118, 119};
static unsigned char segF[] = {105, 106, 107, 108, 113, 114, 115, 116};
static unsigned char segG[] = {65, 66, 73, 82, 81, 90, 89, 97, 98};
static unsigned char segH[] = {17, 18, 25, 34, 33, 42, 41};
static unsigned char segK[] = {19, 27, 26, 28, 35, 43, 51};
static unsigned char segM[] = {21, 20, 29, 36, 44, 45};
static unsigned char segN[] = {22, 30, 31, 37, 38, 46, 54};
static unsigned char segP[] = {56, 64, 55, 63, 53, 61};
static unsigned char segR[] = {62, 70, 77, 78, 86, 87, 94, 102};
static unsigned char segS[] = {68, 69, 76, 85, 92, 93, 100, 101};
static unsigned char segT[] = {59, 67, 75, 74, 84, 83, 91, 99};
static unsigned char segU[] = {49, 57, 50, 58, 52, 60};
static unsigned char segDP[] = {120, 104, 112};
static unsigned char segUL[] = {121, 122, 123, 124, 125, 126, 127, 128};

static unsigned char * segments[] = {segA,  segB,  segC,  segD,  segE,  segF,  segG,  segH,  segK,  segM,  segN,  segP,  segR,  segS,  segT,  segU,  segDP,  segUL};
static uint8_t segmentElements[] = {8, 8, 7, 7, 7, 8, 9, 7, 7, 6, 7, 6, 8, 8, 8, 6, 3, 8};

// Diode number to grid and seg
// GRID = ((REF-1) / 8) + 1
// SEG = (REF-1) % 8;

#endif /* _SEG_MAP_H */
