

#include "../skiparray.h"
#include "test_header.h"
#include <stdio.h>



int main(int argc, char **argv){

    int * pi;
    int c;
    int ia[100];
    SkipArray sa = NULL;
    TITLE("SKIPARRAY TESTS");

    for (c=0 ; c<100 ; c++){
        ia[c] = c;
    }

    sa = skiparray_new();

    /* append/get test */
    printf("\t%-30s", "append");
    passed = 1;

    for (c=0 ; c<100 ; c++){
        skiparray_insert(sa, c, ia+c);
    }

    if (sa->length != 100) passed =0;

    for (c=0; c< sa->length ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != c) passed =0;
    }

    if (passed) printf("... passed\n");
    else printf("... failed\n");


    /* deletion test */
    printf("\t%-30s", "deletion");
    passed=1;

    skiparray_delete(sa,50);
    if (sa->length != 99) passed =0;

    for (c=0; c< 50 ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != c) passed =0;
    }

    for (c=50; c< sa->length ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != c+1)passed =0;
    }

    if (passed) printf("... passed\n");
    else printf("... failed\n");



    /*insert test */
    printf("\t%-30s", "insertion");
    passed = 1;

    for (c=0 ; c<100 ; c++){
        skiparray_insert(sa, 0, ia+c);
    }

    if (sa->length != 199) passed =0;


    for (c=0; c< 100 ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != 99-c) passed =0;
    }

    for (c=100; c< 150 ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != c - 100) passed =0;
    }

    for (c=150; c< sa->length ; c++){
        pi = skiparray_get(sa, c);
        if ( *pi != c-99)passed =0;
    }


    if (passed) printf("... passed\n");
    else printf("... failed\n");

    skiparray_free(sa);


    return 0;
}




