#include <cassert>
#include <cstddef>
#include "formats/arc/npa_archive/npa_filter_chaos_head.h"

__attribute__((const))
uint32_t npa_chaos_head_file_name_filter(uint32_t key1, uint32_t key2)
{
    return key1 * key2;
}

void npa_chaos_head_filter_init(NpaFilter &filter)
{
    filter.permutation =
        (unsigned char*)
        "\xF1\x71\x80\x19\x17\x01\x74\x7D\x90\x47\xF9\x68\xDE\xB4\x24\x40"
        "\x73\x9E\x5B\x38\x4C\x3A\x2A\x0D\x2E\xB9\x5C\xE9\xCE\xE8\x3E\x39"
        "\xA2\xF8\xA8\x5E\x1D\x1B\xD3\x23\xCB\x9B\xB0\xD5\x59\xF0\x3B\x09"
        "\x4D\xE4\x4A\x30\x7F\x89\x44\xA0\x7A\x3C\xEE\x0E\x66\xBF\xC9\x46"
        "\x77\x21\x86\x78\x6E\x8E\xE6\x99\x33\x2B\x0C\xEA\x42\x85\xD2\x8F"
        "\x5F\x94\xDA\xAC\x76\xB7\x51\xBA\x0B\xD4\x91\x28\x72\xAE\xE7\xD6"
        "\xBD\x53\xA3\x4F\x9D\xC5\xCC\x5D\x18\x96\x02\xA5\xC2\x63\xF4\x00"
        "\x6B\xEB\x79\x95\x83\xA7\x8C\x9A\xAB\x8A\x4E\xD7\xDB\xCA\x62\x27"
        "\x0A\xD1\xDD\x48\xC6\x88\xB6\xA9\x41\x10\xFE\x55\xE0\xD9\x06\x29"
        "\x65\x6A\xED\xE5\x98\x52\xFF\x8D\x43\xF6\xA4\xCF\xA6\xF2\x97\x13"
        "\x12\x04\xFD\x25\x81\x87\xEF\x2F\x6C\x84\x2C\xAA\xA1\xAF\x36\xCD"
        "\x92\x0F\x2D\x67\x45\xE2\x64\xB3\x20\x50\x4B\xF3\x7B\x1F\x1C\x03"
        "\xC4\xC1\x16\x61\x6F\xC7\xBE\x05\xAD\x22\x34\xB2\x54\x37\xF7\xD0"
        "\xFA\x60\x8B\x14\x08\xBC\xEC\xBB\x26\x9C\x57\x32\x5A\x3F\x35\x6D"
        "\xC8\xC3\x69\x7C\x31\x58\xE3\x75\xD8\xE1\xC0\x9F\x11\xB5\x93\x56"
        "\xF5\x1E\xB1\x1A\x70\x3D\xFB\x82\xDC\xDF\x7E\x07\x15\x49\xFC\xB8";
    filter.data_key = 0x87654321;
    filter.file_name_key = &npa_chaos_head_file_name_filter;
}
