
#include "../string.h"
#include "test_header.h"



int main(int argc, char **argv){
    TITLE("STRING TESTS");

    char * t1 = "Hello World\n";

    string_t subject = NULL;

    /* new from cstring */
    START("new(cstring)")
        subject = string_new(t1);
        TEST(subject->length == strlen(t1) );
        TEST( strcmp(subject->data, t1)==0 );
        free(subject);
    END


    START("string_new_add")
        string_t a = string_new("abcdefg");
        string_t b = string_new("hijklmnop");
        string_t c = string_new_add(a,b);
        TEST( strcmp(c->data, "abcdefghijklmnop") == 0 );
    END


    START("string_find")
        string_t big    = string_new("abcdefghijkl");
        string_t little = string_new("cd");
        TEST( string_find(big,little) == 4 );
    END


    START("string_formatted")
        string_t formatted    = string_new_formatted("%f", 12.0);
        TEST( memcmp(formatted->data, "12.000000", 6)==0 );
    END



    return 0;
}

