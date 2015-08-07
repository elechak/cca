
#include "../bytes.h"
#include "test_header.h"


int main(int argc, char **argv){
    TITLE("BYTES TESTS")

    Bytes subject = NULL;

    START("new")
        subject = bytes_new();
        TEST(subject);
    END

    START("formatted write [ints]")
        int x=0;
        int y=0;
        int z=0;

        bytes_writef(subject, "iii",5,10,15);
        bytes_readf(subject, "iii", &x,&y,&z);
        TEST((x==5) && (y==10) && (z==15))
    END

    bytes_free(subject);


    return 0;
}


