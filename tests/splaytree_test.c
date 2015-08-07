

//~ #ifdef REENTRANT
//~ #include "../threading.h"
//~ #endif

#include "../splaytree.h"
#include "test_header.h"

#define ARRAY_LENGTH 1000


inline int getRandom(int limit){
    return  (int)(rand() / (((double)RAND_MAX + 1)/ limit));
}


int comp( int * a, int * b){
    return *b - *a;
}



struct thread_test_data{
    SplayTree tree;
    int passed;
};
typedef struct thread_test_data *  thread_test_data;


void access_test(void * pv){
    thread_test_data data = pv; 
    data->passed = 1;
    
    int c;
    int * pc;
    int count;

    for (count = 0; count <ARRAY_LENGTH * 10; count++){
        c = getRandom(ARRAY_LENGTH);
        pc = splaytree_get(data->tree, &c);
        if ( (! pc) || (*pc != c) ){
            data->passed= 0;
            break;
        }            
    }
}

int main(int argc, char **argv){
    int * pi;
    int c;
    int ia[ARRAY_LENGTH];

    SplayTree subject = NULL;

    for (c=0 ; c<ARRAY_LENGTH ; c++){
        ia[c] = c;
    }

    TITLE("SPLAYTREE TESTS");

    START("splaytree new")
        subject = splaytree_new((Comparator) comp);
        TEST(subject);
    END


    START("insert")
        for (c=0 ; c<ARRAY_LENGTH ; c++){
            splaytree_insert(subject, ia+c);
        }

        TEST(subject->size ==ARRAY_LENGTH);

        for (c=0; c< ARRAY_LENGTH ; c++){
            pi = splaytree_get(subject, &c);
            TEST( *pi ==c );
        }
    END



    START("delete")
        /* delete the value with the key 0 */
        c = 0;
        splaytree_delete(subject, &c);

        /* ensure that the length of the splaytree is decremented */
        TEST(subject->size ==(ARRAY_LENGTH-1));

        /* examine the value with key 1 */
        c = 1;
        pi = splaytree_get(subject, &c);
             
        TEST( *pi == 1 );    
    END



    START("re-insert")
        /* delete the value with the key 0 */
        c = 0;
        splaytree_insert(subject, &c);

        /* ensure that the length of the splaytree is incremented */
        TEST(subject->size ==ARRAY_LENGTH);

        /* examine the value with key 1 */
        c = 0;
        pi = splaytree_get(subject, &c);
             
        TEST( *pi == 0 );    
    END



//~ #ifdef REENTRANT
    //~ START("threading - multiple access")
        //~ thread_test_data  data1 = malloc( sizeof(*data1) );
        //~ thread_test_data  data2 = malloc( sizeof(*data1) );

        //~ data1->tree = data2->tree = subject;

        //~ thread_t thread1 = run_async(access_test, data1);
        //~ thread_t thread2 = run_async(access_test, data2);

        //~ join_async(thread1);
        //~ join_async(thread2);

        //~ TEST( data1->passed );    
        //~ TEST( data2->passed );    
    //~ END
//~ #endif
        
    splaytree_free(subject);






    return 0;
}

