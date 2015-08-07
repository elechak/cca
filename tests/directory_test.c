
#include "../directory.h"
#include "test_header.h"
#include <stdio.h>



int comp( int * a, int * b){
    return *b - *a;
}

int main(int argc, char **argv){
    int * pi;
    int c;
    int ia[100];

    Directory subject = NULL;
    TITLE("DIRECTORY TESTS");

    for (c=0 ; c<100 ; c++){
        ia[c] = c;
    }

    subject = directory_new((Comparator) comp);

    /* append/get test */
    printf("\t%-30s", "insert");
    passed = 1;

    for (c=0 ; c<100 ; c++){
        directory_add(subject, ia+c);
    }

    if (directory_length(subject) != 100) passed =0;

    for (c=0; c< 100 ; c++){
        pi = directory_byIndex(subject, c);
        if ( *pi != c) passed =0;
    }

    if (passed) printf("... passed\n");
    else printf("... failed\n");

    directory_free(subject);

    return 0;
}




//~ int main(int argc, char **argv){
    //~ Directory d = directory_new((Comparator)strcmp);

    //~ directory_add(d , "Erik");
    //~ directory_add(d , "Donna");
    //~ directory_add(d , "Kippy");
    //~ directory_add(d , "Fish");

    //~ printf("<%s>\n", (char * )directory_byKey(d, "Erik"));
    //~ printf("<%s>\n", (char * )directory_byKey(d, "Dog"));
    //~ printf("<%s>\n", (char * )directory_byIndex(d, 2));

    //~ directory_deleteKey(d, "Kippy");
    //~ printf("<%s>\n", (char * )directory_byIndex(d, 2));

    //~ return 0;
//~ }
