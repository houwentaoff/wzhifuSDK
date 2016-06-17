default:all
all:test1 test2

INC:=-I/usr/include/python2.7
LD:= -lpython2.7

CFLAGS+=$(INC)
LDFLAGS+=$(LD)

test1:test1.o 
	$(CC) $^ -o $@ $(LD)
test2:test2.o
	$(CC) $^ -o $@ $(LD)
test_pay:test_pay.o wx_api.o
	$(CC) $^ -o $@ $(LD)
test_time:test_time.o
	$(CC) $^ -o $@ $(LD)

%.o:%.c
	$(CC) -g -c $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o test1 test2 *.pyc test_pay test_time
.PHONY:clean
