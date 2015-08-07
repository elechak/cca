

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TITLE( NAME )\
    int passed;\
    printf("%s\n", NAME);\
    fflush(stdout);

#define START( NAME ) \
    printf("\t%-30s", NAME);\
    fflush(stdout);\
    passed = 1;

#define END \
    if (passed) {printf("... passed\n");fflush(stdout);}\
    else {printf("... FAILED\n");fflush(stdout);}

#define FAILED passed=0

#define TEST( CONDITION ) \
    if(!(CONDITION) || !passed) FAILED;

#define  DPRINT(...)  printf("%s:%d ",__FILE__, __LINE__);printf(__VA_ARGS__);printf("\n");fflush(stdout);


int passed;

