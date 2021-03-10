EXCLUDED_SCHEMES=
LIBHAL_SRC := \
	common/hal-cortexa.c \
	common/randombytes.c

obj/libpqaxhal.a: $(call objs,$(LIBHAL_SRC))
obj/libpqaxhal-nornd.a: $(call objs,$(filter-out common/randombytes.c,$(LIBHAL_SRC)))

LDLIBS += -lpqaxhal$(if $(NO_RANDOMBYTES),-nornd)
LIBDEPS += obj/libpqaxhal.a obj/libpqaxhal-nornd.a

CFLAGS += -fomit-frame-pointer -march=native -mtune=native


CC ?= gcc
CPP ?= cpp
AR ?= ar
LD ?= $(CC)
OBJCOPY ?= objcopy
SIZE ?= size

LINKDEPS += $(LIBDEPS)
