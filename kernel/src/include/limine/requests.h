#ifndef __REQUESTS_H
#define __REQUESTS_H

#include <limine.h>

// Requests
extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_bootloader_info_request bootloader_info_request;
extern volatile struct limine_firmware_type_request firmware_type_request;
extern volatile struct limine_hhdm_request hhdm_request;

#endif // __REQUESTS_H