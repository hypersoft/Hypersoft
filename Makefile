bin ?= bin
lib ?= lib
inc ?= inc

home ?= .
destination ?= .
mode ?= debug

ifeq (debug, $(mode))
	build.mode = -g3
endif

build.bin = $(destination)/$(bin)
build.lib = $(destination)/$(lib)
build.inc = $(destination)/$(inc)

build.src = $(home)/src
build.pkg = $(home)/pkg
build.tool = $(home)/tool

build.trash =

void != \
[ -e $(build.bin) ] || mkdir -p $(build.bin); \
[ -e $(build.lib) ] || mkdir -p $(build.lib); \
[ -e $(build.inc) ] || mkdir -p $(build.inc); \
echo >&2;

all: headers HyperVariant HyperStack HyperTable exam dasms

build.headers = $(shell echo $(build.inc)/Hyper{Variant,Stack,Table,soft}.h)
build.headers += $(build.inc)/utfx.h

build.objects = $(shell echo $(build.bin)/Hyper{Variant,Stack,Table}.o)
build.objects += $(build.bin)/exam.o $(build.bin)/utfx.o

build.dasms = $(build.objects:%.o=%.o.s) $(build.bin)/exam.e.s
build.dependencies = $(build.objects:%.o=%.d)
build.asms = $(build.objects:%.o=%.s)

build.trash += $(build.headers) $(build.objects) $(build.asms) $(build.dasms) \
	$(build.dependencies) $(build.bin)/exam

headers: $(build.headers)
dasms: $(build.dasms)
asms: $(build.asms)

HyperVariant: $(build.bin)/HyperVariant.o
HyperStack: $(build.bin)/HyperStack.o
HyperTable: $(build.bin)/HyperTable.o

CFLAGS += -Wpedantic -std=iso9899:2011 $(build.mode) 
#-O3 -MMD \
#	-faggressive-loop-optimizations -fkeep-inline-functions

ifeq (triston, $(USER))
#	CFLAGS +=  -march=atom -mtune=atom -fomit-frame-pointer -mssse3 -mieee-fp \
#		-mfpmath=sse -fexcess-precision=fast -mpush-args -mhard-float 
else
	CFLAGS += -march=`uname -m` -mtune=generic 
endif

CFLAGS += -fPIC -I"$(build.inc)"

$(build.bin)/%.i: $(build.src)/%.c
	$(COMPILE.c) -E -masm=intel $< > $@

$(build.bin)/%.s: $(build.src)/%.c
	$(COMPILE.c) -S -masm=intel -o $@ $<
	@echo

$(build.bin)/exam.e.s: $(build.bin)/exam
	@$(build.tool)/mkdasm $^ $@ 

$(build.bin)/%.o.s: $(build.bin)/%.o
	@$(build.tool)/mkdasm $^ $@ 

$(build.inc)/%.h: $(build.src)/%.h
	cp $^ $@;
	@echo

$(build.bin)/%.o: $(build.src)/%.c $(build.src)/%.h
	$(COMPILE.c) -o $@ $<
	@echo

$(build.bin)/%.o: $(build.src)/%.c
	$(COMPILE.c) -o $@ $<
	@echo

exam: $(build.objects)
	$(LINK.c) -o $(build.bin)/exam $^ -lc
	@echo

clean:
	@$(RM) -vr $(build.trash)
	@echo

.DEFAULT_GOAL = all
.PHONY: clean HyperVariant HyperStack HyperTable asms dasms

-include $(build.dependencies)
