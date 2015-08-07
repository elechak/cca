
#include "../stream.h"
#include "../string.h"
#include "test_header.h"


int main(int argc, char **argv){
    TITLE("STREAM TEST")

    Stream s = NULL;
    string_t st = NULL;
    string_t st2 = NULL;

    s = stream_open_mem();
    st = string_new("Hello World");
    stream_write(s, st);
    free(st);
    
    st = stream_read(s, 128);
    string_fprint(st, stdout);
    free(st);
    stream_close(s);



    s = stream_open_mem();
    st = string_new("a123a45aa6789a0a");
    stream_write(s, st);
    free(st);
    printf("\n");
    st2 = string_new("a");
    st = stream_readbreak(s, st2);
    string_fprint(st, stdout);
    free(st);
    st = stream_readbreak(s, st2);
    string_fprint(st, stdout);
    free(st);
    st = stream_readbreak(s, st2);
    string_fprint(st, stdout);
    free(st);
    st = stream_readbreak(s, st2);
    string_fprint(st, stdout);
    free(st);
    stream_close(s);

    passed = 1;

    s = stream_open_file("data", "r", 666);
    st = stream_read(s, 4000);
    printf("   %p  \n", st);
    string_fprint(st, stdout);
    printf("\n");

    stream_close(s);



    return 0;
}


