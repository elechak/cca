

CC=gcc

LIBNAME = cca
OBJS= string.o skiparray.o splaytree.o directory.o bytes.o dynlib.o stream.o files.o threading.o xml.o index.o pool.o

print-%:
	@echo $* = $($*)

win-%:
	$(MAKE) WIN=1 $*


ifdef WIN
RM=del
else
RM=rm -f
endif


all: ${OBJS} test

static:lib$(LIBNAME).a test

dynamic:lib$(LIBNAME).so test

lib$(LIBNAME).a: $(OBJS)
	ar rcsv lib$(LIBNAME).a $(OBJS)

lib$(LIBNAME).so: $(OBJS)
	${CC} $(OBJS) -o $@ -Wall -fPIC -shared 

$(LIBNAME).dll: $(OBJS)
	${CC} $(OBJS) -o $@ -Wall -shared -lwsock32

%.o : %.c %.h
	$(CC) ${CFLAGS} -c -fPIC $<

test:
	$(MAKE) -C tests

clean:
	$(RM) lib$(LIBNAME).a
	$(RM) lib$(LIBNAME).so
	$(RM) $(OBJS)
	$(RM) gmon.out
	$(RM) cca.dll
	$(MAKE) -C tests clean



