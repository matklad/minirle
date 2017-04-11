#include "minirle.h"
#include "string.h"
#include "stdio.h"

int rle_encode(uint8_t* src, size_t src_len, uint8_t* dst, size_t dst_len, size_t* bytes_written) {
  uint8_t* src_end = src + src_len;
  uint8_t* dst_end = dst + dst_len;
  uint8_t* d = dst;

  for (uint8_t* s = src; s < src_end;) {
    // Need at least two bytes to write the next block
    if (dst_end - d < 2) return -1;
    
    uint8_t val = *s;
    uint8_t run = 0;
    while (*s == val && s < src_end && run < 255) {
      s++;
      run++;
    }
    *(d++) = run;
    *(d++) = val;
  }
  *bytes_written = d - dst;
  return 0;
}

int rle_decode(uint8_t* src, size_t src_len, uint8_t* dst, size_t dst_len, size_t* bytes_written) {
  // Need an even number of bytes to decode
  if ((src_len & 1) != 0) return -1;
  
  uint8_t* src_end = src + src_len;
  uint8_t* dst_end = dst + dst_len;
  uint8_t* d = dst;

  for (uint8_t* s = src; s < src_end; s += 2) {
    uint8_t run = *s;
    uint8_t val = *(s + 1);
    if (dst_end - d < run) return -1;
    memset(d, val, run);
    d += run;
  }
  *bytes_written = d - dst;
  return 0;
}
