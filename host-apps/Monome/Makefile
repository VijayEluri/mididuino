MIDICTRL_LIBS = Monome GUI MidiTools
HOST_LIBS = 

include ../../makefiles/Host.mk

all: monometest monometest2

monometest: $(OBJS) MonomeTrigPage.o MonomeRouting.o MonomeHost.o \
				MonomeStraightPage.o \
				MonomeMidiPage.o monometest.host.o
	$(CLDCXX) $(CLDFLAGS) -o $@ $^ $(LIBS)

monometest2: $(OBJS) MonomeHost.o monometest2.host.o
	$(CLDCXX) $(CLDFLAGS) -o $@ $^ $(LIBS)

clean:
	- rm -f *.o monometest

