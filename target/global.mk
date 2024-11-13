#######################
# Global Make Variables
#######################

override CLANG_CHECK := $(shell ! $(CC) --version 2>/dev/null | grep 'clang' >/dev/null 2>&1; echo $$?)

override IMAGE_NAME = nekos
override KERNEL_NAME = neko.elf


override ISO_IMAGE = $(BUILD_DIR)/$(IMAGE_NAME).iso
override HDD_IMAGE = $(BUILD_DIR)/$(IMAGE_NAME).hdd

override USER_VARIABLE = $(if $(filter $(origin $(1)),default undefined),$(eval override $(1) := $(2)))

override PREFIX = /usr/local

override CC = clang
override AR = ar
override LD = ld

override CFLAGS     := 	-Wall 							\
    			   		-Wextra 						\
    					-std=gnu11 						\
    					-nostdinc						\
    					-ffreestanding 					\
    					-fno-stack-protector 			\
    					-fno-stack-check 				\
    					-fno-lto 						\
    					-fno-PIC 						\
    					-ffunction-sections 			\
   						-fdata-sections 				\
    					-m64 							\
    					-march=x86-64 					\
    					-mno-80387 						\
    					-mno-mmx 						\
    					-mno-sse 						\
    					-mno-sse2 						\
    					-mno-red-zone 					\
    					-mcmodel=kernel 				\
						-g -O2 -pipe

override CPPFLAGS   := 	-I src 							\
						-I src/include					\
    				 	-isystem freestnd-c-hdrs-0bsd 	\
    					$(CPPFLAGS) 					\
    					-MMD							\
    					-MP

override NASMFLAGS  :=  -Wall							\
						-felf64

override LDFLAGS    += 	-nostdlib 						\
    					-static 						\
    					-z max-page-size=0x1000 		\
    					-gc-sections 					\
    					-T linker.ld 					\
    					-m elf_x86_64
