#include <limine.h>
#include <limine/requests.h>

__attribute__((
    used,
    section(".limine_requests"))) volatile struct limine_framebuffer_request
    framebuffer_request = {.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

__attribute__((
    used,
    section(".limine_requests"))) volatile struct limine_bootloader_info_request
    bootloader_info_request = {.id = LIMINE_BOOTLOADER_INFO_REQUEST,
                               .revision = 0};

__attribute__((
    used,
    section(".limine_requests"))) volatile struct limine_firmware_type_request
    firmware_type_request = {.id = LIMINE_FIRMWARE_TYPE_REQUEST, .revision = 0};

__attribute__((used,
               section(".limine_requests"))) volatile struct limine_hhdm_request
    hhdm_request = {.id = LIMINE_HHDM_REQUEST, .revision = 0};