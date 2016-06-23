default:all

all:test1 test2 test_pay

ifneq ($(PC), 1)

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../../
endif

include ../env.mk

endif


ifneq (buildroot, $(findstring buildroot, $(CC)))
INC:=-I/usr/include/python2.7
else
INC:=-I../../env/buildroot-2016.05-rc2/output/staging/usr/include/python2.7
endif

LD:= -lpython2.7 -lmxml

CFLAGS+=$(INC) -DWX_PAY
LDFLAGS+=$(LD)


test1:test1.o 
	$(CC) $^ -o $@ $(LD)
test2:test2.o
	$(CC) $^ -o $@ $(LD)
test_pay:test_pay.o wx_api.o
	$(CC) $^ -o $@ $(LD)
test_time:test_time.o
	$(CC) $^ -o $@ $(LD)
test_xml:test_xml.o
	$(CC) $^ -o $@ -lmxml

lib:wx_api.o
	$(AR) rucs libwx_api.a $^ 

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o test1 test2 *.pyc test_pay test_time test_xml
.PHONY:clean
