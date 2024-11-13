MAKEFLAGS += -rR
.SUFFIXES:

include  ../target/global.mk


# Check if all dependencies are supproted
ifneq ($(shell ( test '$(MAKECMDGOALS)' = clean || test '$(MAKECMDGOALS)' = distclean ); echo $$?),0)
    ifeq ($(shell ( ! test -d freestnd-c-hdrs-0bsd || ! test -d cc-runtime || ! test -f src/limine.h ); echo $$?),0)
        $(error Please run the ./get-deps script first)
    endif
endif


# If the compiler is clang we add the target option
ifeq ($(CLANG_CHECK),1)
    override CC += \
        -target x86_64-unknown-none
endif

# Source Files
override CFILES := $(shell cd src && find -L * -type f -name '*.c' | LC_ALL=C sort)
override ASFILES := $(shell cd src && find -L * -type f -name '*.S' | LC_ALL=C sort)
override NASMFILES := $(shell cd src && find -L * -type f -name '*.asm' | LC_ALL=C sort)

# Object Files and other files
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o))
override OBJ += $(addprefix obj/,$(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

.PHONY: all
all: bin/$(KERNEL_NAME)

cc-runtime/cc-runtime.a: cc-runtime/*
	$(MAKE) -C cc-runtime -f cc-runtime.mk \
		CC="$(CC)" \
		AR="$(AR)" \
		CFLAGS="$(CFLAGS)" \
		CPPFLAGS='-isystem ../freestnd-c-hdrs-0bsd -DCC_RUNTIME_NO_FLOAT'

bin/$(KERNEL_NAME): GNUmakefile linker.ld $(OBJ) cc-runtime/cc-runtime.a
	mkdir -p "$$(dirname $@)"
	$(LD) $(OBJ) cc-runtime/cc-runtime.a $(LDFLAGS) -o $@

-include $(HEADER_DEPS)

obj/%.c.o: src/%.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
obj/%.S.o: src/%.S GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


obj/%.asm.o: src/%.asm GNUmakefile
	mkdir -p "$$(dirname $@)"
	nasm $(NASMFLAGS) $< -o $@


.PHONY: clean
clean:
	rm -rf bin obj cc-runtime

.PHONY: distclean
distclean:
	rm -rf bin* obj* freestnd-c-hdrs-0bsd* cc-runtime* src/limine.h

.PHONY: install
install: all
	install -d "$(DESTDIR)$(PREFIX)/share/$(KERNEL_NAME)"
	install -m 644 bin/$(KERNEL_NAME) "$(DESTDIR)$(PREFIX)/share/$(KERNEL_NAME)/$(KERNEL_NAME)"

.PHONY: uninstall
uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/share/$(KERNEL_NAME)/$(KERNEL_NAME)"
	-rmdir "$(DESTDIR)$(PREFIX)/share/$(KERNEL_NAME)"
