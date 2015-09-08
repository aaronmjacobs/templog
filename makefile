CC=g++
CFLAGS=-Wall -g -O3 -I.
LDFLAGS=-Wall -g -O3
OBJECTS=_test/test_logging.o imp/logging.o
APP=_test/test_logging

DEPS=$(patsubst %.o,%.d, $(OBJECTS))

all: $(APP)

$(APP) : $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

-include $(OBJECTS:.o=.d)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o $*.o
	$(CC) -MM $(CFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	    sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean::
	rm -f $(DEPS)
	rm -f $(OBJECTS)
	rm -f $(APP)

.deps : $(DEPS)
	$(CC) -MM -MF $@
