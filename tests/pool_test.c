

#ifdef REENTRANT
#include "../threading.h"
#endif

#include "../pool.h"
#include "test_header.h"


int alloced_data = 0;

struct Data{
    int x;
};
typedef struct Data * Data;
    

void * alloc(){
    Data self = malloc( sizeof(*self) );
    alloced_data++;
    return self;
}

void dealloc(void * vp){
    alloced_data--;
    free(vp);
}



int main(int argc, char **argv){

    TITLE("POOL TESTS");

    START("pool new")
        // create the pool with a capacity of 5
        Pool pool = pool_new(5, alloc, dealloc);
        TEST( pool );
    END


    START("pool_get")
        // this should create several instances of the Data type
        Data a = pool_get(pool);
            a->x = 1;
            TEST(alloced_data == 1)
        Data b = pool_get(pool);
            b->x = 2;
            TEST(alloced_data == 2)
        Data c = pool_get(pool);
            c->x = 3;
            TEST(alloced_data == 3)
        Data d = pool_get(pool);
            d->x = 4;
            TEST(alloced_data == 4)
        Data e = pool_get(pool);
            e->x = 5;
            TEST(alloced_data == 5)
        Data f = pool_get(pool);
            f->x = 6;
            TEST(alloced_data == 6)
        Data g = pool_get(pool);
            g->x = 7;
            TEST(alloced_data == 7)
    
        TEST(a && (a->x=1));
        TEST(b && (a->x=2));
        TEST(c && (a->x=3));
        TEST(d && (a->x=4));
        TEST(e && (a->x=5));
        TEST(f && (a->x=6));
        TEST(g && (a->x=7));
    END


    START("pool store")
        pool_store(pool,a);
            TEST(alloced_data == 7)
        pool_store(pool,b);
            TEST(alloced_data == 7)
        pool_store(pool,c);
            TEST(alloced_data == 7)
        pool_store(pool,d);
            TEST(alloced_data == 7)
        pool_store(pool,e);
            TEST(alloced_data == 7)
        pool_store(pool,f);
            TEST(alloced_data == 6)
        pool_store(pool,g);
            TEST(alloced_data == 5)
    END



    START("pool_get 2")
        // this should create several instances of the Data type
        a = pool_get(pool);
            a->x = 1;
            TEST(alloced_data == 5)
        b = pool_get(pool);
            b->x = 2;
            TEST(alloced_data == 5)
        c = pool_get(pool);
            c->x = 3;
            TEST(alloced_data == 5)
        d = pool_get(pool);
            d->x = 4;
            TEST(alloced_data == 5)
        e = pool_get(pool);
            e->x = 5;
            TEST(alloced_data == 5)
        f = pool_get(pool);
            f->x = 6;
            TEST(alloced_data == 6)
        g = pool_get(pool);
            g->x = 7;
            TEST(alloced_data == 7)
    
        TEST(a && (a->x=1));
        TEST(b && (a->x=2));
        TEST(c && (a->x=3));
        TEST(d && (a->x=4));
        TEST(e && (a->x=5));
        TEST(f && (a->x=6));
        TEST(g && (a->x=7));
    END


    START("pool store 2")
        pool_store(pool,a);
            TEST(alloced_data == 7)
        pool_store(pool,b);
            TEST(alloced_data == 7)
        pool_store(pool,c);
            TEST(alloced_data == 7)
        pool_store(pool,d);
            TEST(alloced_data == 7)
        pool_store(pool,e);
            TEST(alloced_data == 7)
        pool_store(pool,f);
            TEST(alloced_data == 6)
        pool_store(pool,g);
            TEST(alloced_data == 5)
    END



    START("pool_free")
        pool_free(pool);
        TEST(alloced_data == 0)
    END





#ifdef REENTRANT
#endif

    return 0;
}

