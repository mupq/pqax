SYMCRYPTO_SRC = \
	mupq/common/sp800-185.c \
	mupq/common/nistseedexpander.c \
	common/fips202.c \
	common/fips202x2.c \
	mupq/pqclean/common/aes.c \
	mupq/pqclean/common/sha2.c
       

obj/libsymcrypto.a: $(call objs,$(SYMCRYPTO_SRC))

obj/libsymcrypto-hashprof.a: CPPFLAGS+=-DPROFILE_HASHING
obj/libsymcrypto-hashprof.a: $(call hashprofobjs,$(SYMCRYPTO_SRC))

LDLIBS += -lsymcrypto$(if $(PROFILE_HASHING),-hashprof)
LIBDEPS += obj/libsymcrypto.a obj/libsymcrypto-hashprof.a

