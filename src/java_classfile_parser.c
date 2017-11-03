#include "java_classfile_parser/internal/config.h"
#include <java_classfile_parser.h>

/* C.f. https://www.ibm.com/developerworks/aix/library/au-endianc/ */
static const int _java_classfile_parse_bigendian = 1;
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() ( (*(char*)&_java_classfile_parse_bigendian) == 0 )

#ifndef JAVA_CLASSFILE_PARSER_NTRACE
# ifdef JAVA_CLASSFILE_PARSER_LOGGER
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(scope, u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %*s%s=%u '%c', remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), ".", #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %s=%u (not printable), remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %*s%s=%u, remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), ".", #u1, (unsigned int) u1, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U1*]            ->            %*s%s=0%lx, remains %lu", bufferp - u1l, (int) strlen(#scope), ".", #u1p, (unsigned long) u1p, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U2]      0x%04x ->     0x%04x %*s%s=%u, remains %lu", bufferp - 2, (unsigned int) be2, (unsigned int) u22, (int) strlen(#scope), ".", #u2, (unsigned int) u2, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U2*]            ->            %*s%s=0%lx, remains %lu", bufferp - (u2l * 2), (int) strlen(#scope), ".", #u2p, (unsigned long) u2p, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U4]  0x%08lx -> 0x%08lx %*s%s=%lu, remains %lu", bufferp - 4, (unsigned long) be4, (unsigned long) u4, (int) strlen(#scope), ".", #u4, (unsigned long) u4, (unsigned long) lengthl);
#  else
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(scope, u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %*s%s=%u '%c', remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), ".", #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %s=%u (not printable), remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl) fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %*s%s=%u, remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), ".", #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl) fprintf(stderr, "%p[U1*]            ->            %*s%s=0x%lx, remains %lu\n", bufferp - u1l, (int) strlen(#scope), ".", #u1p, (unsigned long) u1p, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl) fprintf(stderr, "%p[U2]      0x%04x ->     0x%04x %*s%s=%u, remains %lu\n", bufferp - 2, (unsigned int) be2, (unsigned int) u2, (int) strlen(#scope), ".", #u2, (unsigned int) u2, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl) fprintf(stderr, "%p[U2*]            ->            %*s%s=0%lx, remains %lu\n", bufferp - (u2l * 2), (int) strlen(#scope), ".", #u2p, (unsigned long) u2p, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl) fprintf(stderr, "%p[U4]  0x%08lx -> 0x%08lx %*s%s=%lu, remains %lu\n", bufferp - 4, (unsigned long) be4, (unsigned long) u4, (int) strlen(#scope), ".", #u4, (unsigned long) u4, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE(scope, msgs) fprintf(stderr, msgs "\n");
#   define __JAVA_CLASSFILE_PARSER_TRACEF(scope, fmts, ...) fprintf(stderr, fmts "\n", __VA_ARGS__);
#  endif
#else
# define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE(scope, msgs)
# define __JAVA_CLASSFILE_PARSER_TRACEF(scope, fmts, ...)
#endif

/* These macros are executed only when current binary is low endian */
/* We do NOT use ntohs and al. because there is no guarantee that our sizeof(u2) is 2*sizeof(u1) etc. */
#define __JAVA_CLASSFILE_PARSER_NTOHS_LE(scope, n) (((((java_classfile_parser_u2_t)(n) & 0x00FF)) << 8) | \
                                                    ((((java_classfile_parser_u2_t)(n) & 0xFF00)) >> 8))

#define __JAVA_CLASSFILE_PARSER_NTOHL_LE(scope, n) (((((java_classfile_parser_u4_t)(n) & 0x000000FF)) << 24) | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0x0000FF00)) << 8)  | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0x00FF0000)) >> 8)  | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0xFF000000)) >> 24))

/* Internal variables of every macro must be unique per macro AND per macro call in case of recursivity */
/* This is why there is always an internal first parameter to every macro with name "scope". */
/* An underscore is prepended to "scope" at every call to any macro */

#define __JAVA_CLASSFILE_PARSER_FREEV(scope, type, onstack)             \
  java_classfile_parser_##type##_t *_##scope##tofreep = &(onstack);     \
  __JAVA_CLASSFILE_PARSER_##type##_freev(_##scope, _##scope##tofreep)


#define _JAVA_CLASSFILE_PARSER_CHAR(scope, type, onstack, endianness, u1, bufferp, lengthl) \
  if (lengthl-- > 0) {                                                  \
    onstack.u1 = (java_classfile_parser_u1_t) *bufferp++;               \
    __JAVA_CLASSFILE_PARSER_TRACE_CHAR(_##scope, onstack.u1, onstack.u1, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);           \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

/* Our java_classfile_parser_u1_t is an unsigned char, bufferp is char *, so we can use direct assignment */
#define _JAVA_CLASSFILE_PARSER_U1(scope, type, onstack, endianness, u1, bufferp, lengthl) \
  if (lengthl-- > 0) {                                                  \
    onstack.u1 = (java_classfile_parser_u1_t) *bufferp++;               \
    __JAVA_CLASSFILE_PARSER_TRACE_U1(_##scope, onstack.u1, onstack.u1, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);           \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U1_ARRAY(scope, type, onstack, endianness, arrayp, arrayl, bufferp, lengthl) \
  {                                                                     \
    size_t _##scope##arrayl = onstack.arrayl;                           \
                                                                        \
    if (_##scope##arrayl > 0) {                                         \
      if (lengthl >= _##scope##arrayl) {                                \
        java_classfile_parser_u1_t *_##scope##p;                        \
                                                                        \
        _##scope##p = (java_classfile_parser_u1_t *) malloc(_##scope##arrayl); \
        if (_##scope##p == NULL) {                                      \
          int _##scope##save_errno = errno;                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);       \
          errno = _##scope##save_errno;                                 \
          return NULL;                                                  \
        }                                                               \
        onstack.arrayp = _##scope##p;                                   \
        memcpy(_##scope##p, bufferp, _##scope##arrayl);                 \
        bufferp += _##scope##arrayl;                                    \
        lengthl -= _##scope##arrayl;                                    \
        __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(_##scope, onstack.arrayp, onstack.arrayl, bufferp, lengthl) \
      } else {                                                          \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);         \
        errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                       \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

/* The compiler will automatically optimize the test on sizeof() */
/* Indeed nothing guarantees that our sizeof(u2) == 2 * sizeof(u1) */
#define _JAVA_CLASSFILE_PARSER_U2_BE(scope, type, onstack, u2, bufferp, lengthl) \
  if (lengthl >= 2) {                                                   \
    if (sizeof(java_classfile_parser_u2_t) == 2) {                      \
      memcpy(&(onstack.u2), bufferp, 2);                                \
      bufferp += 2;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _##scope##u1[2];                       \
                                                                        \
      _##scope##u1[0] = *bufferp++;                                     \
      _##scope##u1[1] = *bufferp++;                                     \
      onstack.u2 = _##scope##u1[0];                                     \
      onstack.u2 <<= 8;                                                 \
      onstack.u2 |= _##scope##u1[1];                                    \
    }                                                                   \
    lengthl -= 2;                                                       \
    __JAVA_CLASSFILE_PARSER_TRACE_U2(_##scope, onstack.u2, onstack.u2, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);           \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

/* Notes: U2 counters are always stored in an u2 as per the spec */
#define _JAVA_CLASSFILE_PARSER_U2_ARRAY_BE(scope, type, onstack, arrayp, arrayl, bufferp, lengthl) \
  {                                                                     \
    size_t _##scope##arrayl = onstack.arrayl;                           \
    size_t _##scope##arrayu1l = _##scope##arrayl * 2;                   \
                                                                        \
    if (_##scope##arrayu1l > 0) {                                       \
      if (lengthl >= _##scope##arrayu1l) {                              \
        java_classfile_parser_u2_t *_##scope##p;                        \
                                                                        \
        _##scope##p = (java_classfile_parser_u2_t *) malloc(_##scope##arrayl * sizeof(java_classfile_parser_u2_t)); \
        if (_##scope##p == NULL) {                                      \
          int _##scope##save_errno = errno;                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);       \
          errno = _##scope##save_errno;                                 \
          return NULL;                                                  \
        }                                                               \
        onstack.arrayp = _##scope##p;                                   \
        if (sizeof(java_classfile_parser_u2_t) == 2) {                  \
          memcpy(_##scope##p, bufferp, _##scope##arrayu1l);             \
          bufferp += _##scope##arrayu1l;                                \
        } else {                                                        \
          java_classfile_parser_u1_t _##scope##u1[2];                   \
          java_classfile_parser_u2_t _##scope##i;                       \
                                                                        \
          for (_##scope##i = 0; _##scope##i < _##scope##arrayl; _##scope##i++) { \
            _##scope##u1[0] = *bufferp++;                               \
            _##scope##u1[1] = *bufferp++;                               \
            *_##scope##p = _##scope##u1[0];                             \
            *_##scope##p <<= 8;                                         \
            *_##scope##p++ |= _##scope##u1[1];                          \
          }                                                             \
        }                                                               \
        lengthl -= _##scope##arrayu1l;                                  \
        __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(_##scope, onstack.arrayp, onstack.arrayl, bufferp, lengthl) \
      } else {                                                          \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);       \
        errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                       \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

#define _JAVA_CLASSFILE_PARSER_U2_ARRAY_LE(scope, type, onstack, arrayp, arrayl, bufferp, lengthl) \
  {                                                                     \
    size_t _##scope##arrayl = onstack.arrayl;                           \
    size_t _##scope##arrayu1l = _##scope##arrayl * 2;                   \
                                                                        \
    if (_##scope##arrayu1l > 0) {                                       \
      if (lengthl >= _##scope##arrayu1l) {                              \
        java_classfile_parser_u2_t *_##scope##p;                        \
                                                                        \
        _##scope##p = (java_classfile_parser_u2_t *) malloc(_##scope##arrayl * sizeof(java_classfile_parser_u2_t)); \
        if (_##scope##p == NULL) {                                      \
          int _##scope##save_errno = errno;                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);     \
          errno = _##scope##save_errno;                                 \
          return NULL;                                                  \
        }                                                               \
        onstack.arrayp = _##scope##p;                                   \
        if (sizeof(java_classfile_parser_u2_t) == 2) {                  \
          java_classfile_parser_u2_t _##scope##i;                       \
                                                                        \
          memcpy(_##scope##p, bufferp, _##scope##arrayu1l);             \
                                                                        \
          for (_##scope##i = 0; _##scope##i < _##scope##arrayl; _##scope##i++, _##scope##p++) { \
            *_##scope##p = __JAVA_CLASSFILE_PARSER_NTOHS_LE(_##scope, *_##scope##p); \
          }                                                             \
          bufferp += _##scope##arrayu1l;                                \
        } else {                                                        \
          java_classfile_parser_u1_t _##scope##u1[2];                   \
          java_classfile_parser_u2_t _##scope##i;                       \
                                                                        \
          for (_##scope##i = 0; _##scope##i < _##scope##arrayl; _##scope##i++, _##scope##p++) { \
            _##scope##u1[0] = *bufferp++;                               \
            _##scope##u1[1] = *bufferp++;                               \
            *_##scope##p = _##scope##u1[0];                             \
            *_##scope##p <<= 8;                                         \
            *_##scope##p |= _##scope##u1[1];                            \
            *_##scope##p = __JAVA_CLASSFILE_PARSER_NTOHS_LE(_##scope, *_##scope##p); \
          }                                                             \
        }                                                               \
        lengthl -= _##scope##arrayu1l;                                  \
        __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(_##scope, onstack.arrayp, onstack.arrayl, bufferp, lengthl) \
      } else {                                                          \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);       \
          errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                     \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

#define _JAVA_CLASSFILE_PARSER_U2_LE(scope, type, onstack, u2, bufferp, lengthl) \
  if (lengthl >= 2) {                                                   \
    java_classfile_parser_u2_t _##scope##u2;                            \
    if (sizeof(java_classfile_parser_u2_t) == 2) {                      \
      memcpy(&_##scope##u2, bufferp, 2);                                \
      bufferp += 2;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _##scope##u1[2];                       \
                                                                        \
      _##scope##u1[0] = *bufferp++;                                     \
      _##scope##u1[1] = *bufferp++;                                     \
      _##scope##u2 = _##scope##u1[0];                                   \
      _##scope##u2 <<= 8;                                               \
      _##scope##u2 |= _##scope##u1[1];                                  \
    }                                                                   \
    lengthl -= 2;                                                       \
    onstack.u2 = __JAVA_CLASSFILE_PARSER_NTOHS_LE(_##scope, _##scope##u2);     \
    __JAVA_CLASSFILE_PARSER_TRACE_U2(_##scope, onstack.u2, _##scope##u2, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);           \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U2(scope, type, onstack, endianness, u2, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U2_##endianness(_##scope, type, onstack, u2, bufferp, lengthl) 
#define _JAVA_CLASSFILE_PARSER_U2_ARRAY(scope, type, onstack, endianness, arrayp, arrayl, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U2_ARRAY_##endianness(_##scope, type, onstack, arrayp, arrayl, bufferp, lengthl) 

/* The compiler will automatically optimize the test on sizeof() */
/* Indeed nothing guarantees that our sizeof(u4) == 4 * sizeof(u1) */
#define _JAVA_CLASSFILE_PARSER_U4_BE(scope, type, onstack, u4, bufferp, lengthl) \
  if (lengthl >= 4) {                                                   \
    if (sizeof(java_classfile_parser_u4_t) == 4) {                      \
      memcpy(&(onstack.u4), bufferp, 4);                                \
      bufferp += 4;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _##scope##u1[4];                       \
                                                                        \
      _##scope##u1[0] = *bufferp++;                                     \
      _##scope##u1[1] = *bufferp++;                                     \
      _##scope##u1[2] = *bufferp++;                                     \
      _##scope##u1[3] = *bufferp++;                                     \
      onstack.u4 = _##scope##u1[0];                                     \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _##scope##u1[1];                                    \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _##scope##u1[2];                                    \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _##scope##u1[3];                                    \
      onstack.u4 <<= 8;                                                 \
    }                                                                   \
    lengthl -= 4;                                                       \
    __JAVA_CLASSFILE_PARSER_TRACE_U4(_##scope, onstack.u4, onstack.u4, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);             \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U4_LE(scope, type, onstack, u4, bufferp, lengthl) \
  if (lengthl >= 4) {                                                   \
    java_classfile_parser_u4_t _##scope##u4;                            \
    if (sizeof(java_classfile_parser_u4_t) == 4) {                      \
      memcpy(&_##scope##u4, bufferp, 4);                                \
      bufferp += 4;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _##scope##u1[4];                       \
                                                                        \
      _##scope##u1[0] = *bufferp++;                                     \
      _##scope##u1[1] = *bufferp++;                                     \
      _##scope##u1[2] = *bufferp++;                                     \
      _##scope##u1[3] = *bufferp++;                                     \
      _##scope##u4 = _##scope##u1[0];                                   \
      _##scope##u4 <<= 8;                                               \
      _##scope##u4 |= _##scope##u1[1];                                  \
      _##scope##u4 <<= 8;                                               \
      _##scope##u4 |= _##scope##u1[2];                                  \
      _##scope##u4 <<= 8;                                               \
      _##scope##u4 |= _##scope##u1[3];                                  \
      _##scope##u4 <<= 8;                                               \
    }                                                                   \
    lengthl -= 4;                                                       \
    onstack.u4 = __JAVA_CLASSFILE_PARSER_NTOHL_LE(_##scope, _##scope##u4); \
    __JAVA_CLASSFILE_PARSER_TRACE_U4(_##scope, onstack.u4, _##scope##u4, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(_##scope, type, onstack);             \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U4(scope, type, onstack, endianness, u4, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U4_##endianness(_##scope, type, onstack, u4, bufferp, lengthl) 

/* We have to explicitely initialize all counters to 0 to avoid corruption at freev() phase in case of error */
#define _JAVA_CLASSFILE_PARSER_ClassFile(scope, endianness, onstack, bufferp, lengthl) do { \
    onstack.constant_pool_count = 0;                                    \
    onstack.constant_poolpp = NULL;                                     \
    onstack.interfaces_count = 0;                                       \
    onstack.interfacesp = NULL;                                         \
    onstack.fields_count = 0;                                           \
    onstack.fieldspp = NULL;                                            \
    onstack.methods_count = 0;                                          \
    onstack.methodspp = NULL;                                           \
    onstack.attributes_count = 0;                                       \
    onstack.attributespp = NULL;                                        \
                                                                        \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, ClassFile, onstack, endianness, magic, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, minor_version, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, major_version, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, constant_pool_count, bufferp, lengthl); \
    if (onstack.constant_pool_count > 1) {                              \
      java_classfile_parser_u2_t _##scope##max = onstack.constant_pool_count - 1; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.constant_poolpp = (java_classfile_parser_cp_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_cp_info_t *)); \
      if (onstack.constant_poolpp == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, ClassFile, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      onstack.constant_pool_count = 1;                                  \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++, onstack.constant_pool_count++) { \
        onstack.constant_poolpp[_##scope##i] = _java_classfile_parser_cp_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.constant_poolpp[_##scope##i] == NULL) {             \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i+1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.constant_poolpp[_##scope##j] = NULL;                \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, ClassFile, onstack);  \
          return NULL;                                                  \
        }                                                               \
        switch (onstack.constant_poolpp[_##scope##i]->tag) {            \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:               \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:             \
          if (_##scope##i < (_##scope##max - 1)) {                      \
            onstack.constant_poolpp[++_##scope##i] = NULL;              \
            onstack.constant_pool_count++;;                             \
          }                                                             \
          break;                                                        \
        default:                                                        \
          break;                                                        \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, this_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, super_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, interfaces_count, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2_ARRAY(_##scope, ClassFile, onstack, endianness, interfacesp, interfaces_count, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, fields_count, bufferp, lengthl); \
    if (onstack.fields_count > 0) {                                     \
      java_classfile_parser_u2_t _##scope##max = onstack.fields_count;  \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.fieldspp = (java_classfile_parser_field_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_field_info_t *)); \
      if (onstack.fieldspp == NULL) {                                   \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, ClassFile, onstack);  \
        return NULL;                                                    \
      }                                                                 \
      onstack.fields_count = 0;                                         \
      for (_##scope##i = 0; _##scope##i < _max; _##scope##i++, onstack.fields_count++) { \
        onstack.fieldspp[_##scope##i] = _java_classfile_parser_field_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.fieldspp[_##scope##i] == NULL) {                    \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.fieldspp[_##scope##j] = NULL;                       \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, ClassFile, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_ClassFile_freev(scope, p)               \
  if (p->constant_poolpp != NULL) {                                     \
    if (p->constant_pool_count > 1) {                                   \
      java_classfile_parser_u2_t _##scope##max = p->constant_pool_count - 1; \
      java_classfile_parser_u2_t _##scope##i;                           \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
        _JAVA_CLASSFILE_PARSER_cp_info_freev(_##scope, p->constant_poolpp[_##scope##i]); \
      }                                                                 \
    }                                                                   \
    free(p->constant_poolpp);                                           \
  }                                                                     \
  if (p->interfacesp != NULL) {                                         \
    free(p->interfacesp);                                               \
  }                                                                     \
  if (p->fieldspp != NULL) {                                            \
    if (p->fields_count > 0) {                                          \
      java_classfile_parser_u2_t _##scope##max = p->fields_count;       \
      java_classfile_parser_u2_t _##scope##i;                           \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
        _JAVA_CLASSFILE_PARSER_field_info_freev(_##scope, p->fieldspp[_##scope##i]); \
      }                                                                 \
    }                                                                   \
    free(p->fieldspp);                                                  \
  }

#define _JAVA_CLASSFILE_PARSER_ClassFile_freev(scope, p)                \
  if (p != NULL) {                                                      \
    __JAVA_CLASSFILE_PARSER_ClassFile_freev(_##scope, p)              \
    free(p);                                                            \
  }

#define _JAVA_CLASSFILE_PARSER_cp_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(_##scope, cp_info, onstack, endianness, tag, bufferp, lengthl); \
    switch (onstack.tag) {                                              \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      onstack.u.classInfop = _java_classfile_parser_CONSTANT_Class_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.classInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      onstack.u.fieldrefInfop = _java_classfile_parser_CONSTANT_Fieldref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.fieldrefInfop == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      onstack.u.methodrefInfop = _java_classfile_parser_CONSTANT_Methodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodrefInfop == NULL) {                           \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      onstack.u.interfaceMethodrefInfop = _java_classfile_parser_CONSTANT_InterfaceMethodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.interfaceMethodrefInfop == NULL) {                  \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      onstack.u.stringInfop = _java_classfile_parser_CONSTANT_String_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.stringInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      onstack.u.integerInfop = _java_classfile_parser_CONSTANT_Integer_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.integerInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      onstack.u.floatInfop = _java_classfile_parser_CONSTANT_Float_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.floatInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      onstack.u.longInfop = _java_classfile_parser_CONSTANT_Long_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.longInfop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      onstack.u.doubleInfop = _java_classfile_parser_CONSTANT_Double_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.doubleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      onstack.u.nameAndTypeInfop = _java_classfile_parser_CONSTANT_NameAndType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.nameAndTypeInfop == NULL) {                         \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      onstack.u.utf8Infop = _java_classfile_parser_CONSTANT_Utf8_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.utf8Infop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      onstack.u.methodHandleInfop = _java_classfile_parser_CONSTANT_MethodHandle_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodHandleInfop == NULL) {                        \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      onstack.u.methodTypeInfop = _java_classfile_parser_CONSTANT_MethodType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodTypeInfop == NULL) {                          \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      onstack.u.invokeDynamicInfop = _java_classfile_parser_CONSTANT_InvokeDynamic_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.invokeDynamicInfop == NULL) {                       \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      onstack.u.moduleInfop = _java_classfile_parser_CONSTANT_Module_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.moduleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      onstack.u.packageInfop = _java_classfile_parser_CONSTANT_Package_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.packageInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);    \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    default:                                                            \
      errno = -1;                                                       \
      __JAVA_CLASSFILE_PARSER_FREEV(_##scope, cp_info, onstack);      \
      return NULL;                                                      \
    }                                                                   \
} while (0)

#define __JAVA_CLASSFILE_PARSER_cp_info_freev(scope, p)                 \
    switch (p->tag) {                                                   \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(_##scope, p->u.classInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(_##scope, p->u.fieldrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(_##scope, p->u.methodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(_##scope, p->u.interfaceMethodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(_##scope, p->u.stringInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(_##scope, p->u.integerInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(_##scope, p->u.floatInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(_##scope, p->u.longInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(_##scope, p->u.doubleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(_##scope, p->u.nameAndTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(_##scope, p->u.utf8Infop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(_##scope, p->u.methodHandleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(_##scope, p->u.methodTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(_##scope, p->u.invokeDynamicInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(_##scope, p->u.moduleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(_##scope, p->u.packageInfop); \
      break;                                                            \
    default:                                                            \
      break;                                                            \
    }

#define _JAVA_CLASSFILE_PARSER_cp_info_freev(scope, p) do {             \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_cp_info_freev(_##scope, p)               \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_field_info(scope, endianness, onstack, bufferp, lengthl) do { \
    onstack.attributes_count = 0;                                       \
    onstack.attributespp = 0;                                           \
                                                                        \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, attributes_count, bufferp, lengthl); \
    if (onstack.attributes_count > 0) {                                 \
      java_classfile_parser_u2_t _##scope##max = onstack.attributes_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.attributespp = (java_classfile_parser_attribute_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_attribute_info_t *)); \
      if (onstack.attributespp == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_FREEV(_##scope, field_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.attributes_count = 0;                                     \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++, onstack.attributes_count++) { \
        onstack.attributespp[_##scope##i] = _java_classfile_parser_attribute_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.attributespp[_##scope##i] == NULL) {                \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.attributespp[_##scope##j] = NULL;                   \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_FREEV(_##scope, field_info, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
} while (0)

#define __JAVA_CLASSFILE_PARSER_field_info_freev(scope, p)              \
  if (p->attributespp != NULL) {                                        \
    if (p->attributes_count > 0) {                                      \
      java_classfile_parser_u2_t _##scope##max = p->attributes_count;   \
      java_classfile_parser_u2_t _##scope##i;                           \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
        _JAVA_CLASSFILE_PARSER_attribute_info_freev(_##scope, p->attributespp[_##scope##i]); \
      }                                                                 \
    }                                                                   \
    free(p->attributespp);                                              \
  }

#define _JAVA_CLASSFILE_PARSER_field_info_freev(scope, p) do {          \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_field_info_freev(_##scope, p)           \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_attribute_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, attribute_info, onstack, endianness, attribute_name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, attribute_info, onstack, endianness, attribute_length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(_##scope, attribute_info, onstack, endianness, infop, attribute_length, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_attribute_info_freev(scope, p)          \
  if (p->infop != NULL) {                                               \
    free(p->infop);                                                     \
  }

#define _JAVA_CLASSFILE_PARSER_attribute_info_freev(scope, p) do {      \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_attribute_info_freev(_##scope, p)       \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Class_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(scope, p) do {  \
    if (p != NULL) {                                                \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(_##scope, p)   \
      free(p);                                                      \
    }                                                               \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Fieldref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Fieldref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(scope, p) do { \
    if (p != NULL) {                                                   \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(_##scope, p) \
      free(p);                                                         \
    }                                                                  \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Methodref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Methodref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(_##scope, p) \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InterfaceMethodref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InterfaceMethodref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(_##scope, p) \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_String_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_String_info, onstack, endianness, string_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(scope, p) do { \
    if (p != NULL) {                                                 \
      __JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(_##scope, p)  \
      free(p);                                                       \
    }                                                                \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Integer_info, onstack, endianness, bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(scope, p) do { \
    if (p != NULL) {                                                  \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(_##scope, p) \
      free(p);                                                        \
    }                                                                 \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Float_info, onstack, endianness, bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(scope, p) do {  \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(_##scope, p)   \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Long_info, onstack, endianness, high_bytes, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Long_info, onstack, endianness, low_bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(scope, p) do {   \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(_##scope, p)    \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Double_info, onstack, endianness, high_bytes, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Double_info, onstack, endianness, low_bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(_##scope, p)  \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_NameAndType_info, onstack, endianness, name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_NameAndType_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(_##scope, p) \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Utf8_info, onstack, endianness, length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(_##scope, CONSTANT_Utf8_info, onstack, endianness, bytesp, length, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(scope, p)       \
  if (p->bytesp != NULL) {                                              \
    free(p->bytesp);                                                    \
  }

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(scope, p) do {   \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(_##scope, p)    \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(_##scope, CONSTANT_MethodHandle_info, onstack, endianness, reference_kind, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_MethodHandle_info, onstack, endianness, reference_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(_##scope, p) \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_MethodType_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(scope, p) do {   \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(_##scope, p) \
        free(p);                                                        \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InvokeDynamic_info, onstack, endianness, bootstrap_method_attr_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InvokeDynamic_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(_##scope, p) \
        free(p);                                                        \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Module_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(_##scope, p)   \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Package_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(scope, p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(_##scope, p)  \
      free(p);                                                          \
    }                                                                   \
} while (0)

/* ======================================================================== */
/* EXPORTED FUNCTIONS                                                       */
/* ======================================================================== */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION_EXPORTED(type)                \
  java_classfile_parser_##type##_t *java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    char *dummyp;                                                       \
    size_t dummyl;                                                      \
    return _java_classfile_parser_##type##_newp(bufferp, lengthl, bufferpp != NULL ? bufferpp : &dummyp, lengthlp != NULL ? lengthlp : &dummyl); \
  }                                                                     \
                                                                        \
  void java_classfile_parser_##type##_freev(java_classfile_parser_##type##_t *p) \
  {                                                                     \
    _java_classfile_parser_##type##_freev(p);                           \
  }

/* ======================================================================== */
/* EXPORTED FUNCTIONS PROXIES                                               */
/* ======================================================================== */
/* - "newp" functions that are endianness aware, and their non-endianness aware version */
/* - "freev" function */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION_PROXY(type)                   \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_BE_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    _JAVA_CLASSFILE_PARSER_##type(, BE, type, bufferp, lengthl);        \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_LE_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    _JAVA_CLASSFILE_PARSER_##type(, LE, type, bufferp, lengthl);        \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    if (_JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN()) {                 \
      _JAVA_CLASSFILE_PARSER_##type(, BE, type, bufferp, lengthl);      \
    } else {                                                            \
      _JAVA_CLASSFILE_PARSER_##type(, LE, type, bufferp, lengthl);      \
    }                                                                   \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static void _java_classfile_parser_##type##_freev(java_classfile_parser_##type##_t *p) \
  {                                                                     \
    _JAVA_CLASSFILE_PARSER_##type##_freev(, p);                         \
  }

/* ======================================================================== */
/* FUNCTIONS GENERATOR                                                      */
/* ======================================================================== */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION(type)                 \
  _JAVA_CLASSFILE_GENERATE_FUNCTION_PROXY(type)                 \
  _JAVA_CLASSFILE_GENERATE_FUNCTION_EXPORTED(type)

_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Class_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Fieldref_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Methodref_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_String_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Integer_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Float_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Long_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Double_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_NameAndType_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Utf8_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_MethodHandle_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_MethodType_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_InvokeDynamic_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_InterfaceMethodref_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Module_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(CONSTANT_Package_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(cp_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(attribute_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(field_info)
_JAVA_CLASSFILE_GENERATE_FUNCTION(ClassFile)
