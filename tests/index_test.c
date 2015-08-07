
#include "test_header.h"
#include "../index.h"


int main(int argc, char **argv){

    TITLE("INDEX TESTS");

    Index subject;
    
    START("index new")
        subject = index_new(10);
        TEST(subject);
    END


    START("insert")
        size_t a = index_add(subject , "hello");
        size_t b = index_add(subject , "world");
        size_t c = index_add(subject , "Erik");
        size_t d = index_add(subject , "Lechak");
    
        TEST(  (strcmp( (char *) index_get(subject, a) , "hello") == 0)   );
        TEST(  (strcmp( (char *) index_get(subject, b) , "world") == 0)   );
        TEST(  (strcmp( (char *) index_get(subject, c) , "Erik") == 0)   );
        TEST(  (strcmp( (char *) index_get(subject, d) , "Lechak") == 0)   );
    END


    return 0;
}

