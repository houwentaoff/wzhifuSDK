default:all

ifneq ($(PC), 1)

ifneq (buildroot, $(findstring buildroot, $(CC)))
#all:tips_warning 
all:tips lib
else
all:tips lib test1 test2 test_pay
endif

else
all:tips lib test1 test2 test_pay
endif

tips:
	-@echo  "\033[32m Building wx_api ... \033[0m"
tips_warning:
	-@echo  "\033[5;41;32m You don't need to compile wx module  ... \033[0m"

ifneq ($(PC), 1)

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../../
endif

include ../env.mk

endif


ifneq (buildroot, $(findstring buildroot, $(CC)))
INC:=-I/usr/include/python2.7 -I../../App/third_party/include
else
INC:=-I../../env/buildroot-2016.05-rc2/output/staging/usr/include/python2.7
endif

LD:= -lpython2.7 -lmxml

CFLAGS+=$(INC) -DWX_PAY 

ifeq ($(PC), 1)
CFLAGS+= -DPYTHON_IMPLEMENT
endif

ifneq (buildroot, $(findstring buildroot, $(CC)))
else
CFLAGS+= -DPYTHON_IMPLEMENT
endif
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
	-@$(RM) *.o test1 test2 *.pyc test_pay test_time test_xml *.a
.PHONY:clean
