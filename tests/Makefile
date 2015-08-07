

CFLAGS= -Wall -g -DREENTRANT


TARGETS = skiparray_test splaytree_test string_test directory_test bytes_test stream_test index_test xml_test pool_test



all: ${TARGETS}


string.o      :
	$(MAKE) -C .. $@

splaytree.o   :
	$(MAKE) -C .. $@

skiparray.o   :
	$(MAKE) -C .. $@

directory.o   :
	$(MAKE) -C .. $@

bytes.o       :
	$(MAKE) -C .. $@

index.o       :
	$(MAKE) -C .. $@
    
pool.o       :
	$(MAKE) -C .. $@
    
    
skiparray_test      :  skiparray_test.c ../skiparray.o
	gcc ${CFLAGS} -o $@ $^
	./$@

splaytree_test      :  splaytree_test.c ../splaytree.o ../threading.o -lpthread
	gcc ${CFLAGS} -o $@ $^
	./$@

string_test      :  string_test.c ../string.o
	gcc ${CFLAGS} -o $@ $^
	./$@

directory_test      :  directory_test.c ../directory.o ../skiparray.o ../splaytree.o ../threading.o -lpthread
	gcc ${CFLAGS} -o $@ $^
	./$@

bytes_test      :  bytes_test.c ../bytes.o
	gcc ${CFLAGS} -o $@ $^
	./$@

stream_test      :  stream_test.c ../stream.o ../string.o
	gcc ${CFLAGS} -o $@ $^
	./$@

xml_test      :  xml_test.c ../xml.o
	gcc ${CFLAGS} -o $@ $^
	./$@

index_test      :  index_test.c ../index.o ../threading.o -lpthread
	gcc ${CFLAGS} -o $@ $^
	./$@

pool_test      :  pool_test.c ../pool.o ../threading.o -lpthread
	gcc ${CFLAGS} -o $@ $^
	./$@


clean:
	rm -f  *.o
	rm -f  ${TARGETS}
	rm -f  gmon.out
