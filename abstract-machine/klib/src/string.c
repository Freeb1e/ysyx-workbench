#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  //panic("Not implemented");
  char *p = dst;
  while ((*p++ = *src++) != '\0');
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  //panic("Not implemented");
  char *ptrstr = dst;
  while (*ptrstr != '\0') {
    ptrstr++;
  }
  while (*src != '\0') {
    *ptrstr = *src;
    ptrstr++;
    src++;
  }
  *ptrstr = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  //panic("Not implemented");
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  //panic("Not implemented");
  unsigned char *p = (unsigned char *)s;
  for (size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  //panic("Not implemented");
  unsigned char *d = (unsigned char *)out;
  for( size_t i = 0; i < n; i++) {
    d[i] = ((unsigned char *)in)[i];
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  //panic("Not implemented");
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

#endif
