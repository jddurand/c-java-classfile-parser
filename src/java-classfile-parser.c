#include "java-classfile-parser/internal/config.h"
#include <java-classfile-parser.h>

/* C.f. https://www.ibm.com/developerworks/aix/library/au-endianc/ */
static const int _java_classfile_parse_bigendian = 1;
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() ( (*(char*)&_java_classfile_parse_bigendian) == 0 )

#ifndef JAVA_CLASSFILE_PARSER_NTRACE
# ifdef JAVA_CLASSFILE_PARSER_LOGGER
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]       0x%02x ->       0x%02x %s=%u '%c', remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]       0x%02x ->       0x%02x %s=%u (not printable), remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl)
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(u1, be1, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]       0x%02x ->       0x%02x %s=%u, remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(u1p, u1l, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U*]            ->            %s, remains %lu", bufferp - u1l, #u1p, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(u2, be2, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U2]     0x%04x ->     0x%04x %s=%u, remains %lu", bufferp - 2, (unsigned int) be2, (unsigned int) u22, #u2, (unsigned int) u2, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(u4, be4, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U4] 0x%08lx -> 0x%08lx%s=%lu, remains %lu", bufferp - 4, (unsigned long) be4, (unsigned long) u4, #u4, (unsigned long) u4, (unsigned long) lengthl);
#  else
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? fprintf(stderr, "%p[U1]       0x%02x ->       0x%02x %s=%u '%c', remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : fprintf(stderr, "%p[U1]       0x%02x ->       0x%02x %s=%u (not printable), remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(u1, be1, bufferp, lengthl) fprintf(stderr, "%p[U1]       0x%02x ->       0x%02x %s=%u, remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(u1p, u1l, bufferp, lengthl) fprintf(stderr, "%p[U*]            ->            %s, remains %lu\n", bufferp - u1l, #u1p, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(u2, be2, bufferp, lengthl) fprintf(stderr, "%p[U2]     0x%04x ->     0x%04x %s=%u, remains %lu\n", bufferp - 2, (unsigned int) be2, (unsigned int) u2, #u2, (unsigned int) u2, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(u4, be4, bufferp, lengthl) fprintf(stderr, "%p[U4] 0x%08lx -> 0x%08lx %s=%lu, remains %lu\n", bufferp - 4, (unsigned long) be4, (unsigned long) u4, #u4, (unsigned long) u4, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE(msgs) fprintf(stderr, msgs "\n")
#   define __JAVA_CLASSFILE_PARSER_TRACEF(fmts, msgs, ...) fprintf(stderr, fmts "\n", msgs, __VA_ARGS__)
#  endif
#else
# define __JAVA_CLASSFILE_PARSER_TRACE_U1(u1, be1, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(u1p, u1l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2(u2, be2, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U4(u4, be4, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE(msgs)
# define __JAVA_CLASSFILE_PARSER_TRACEF(fmts, msgs)
#endif

/* These macros are executed only when current binary is low endian */
/* We do NOT use ntohs and al. because there is no guarantee that our sizeof(u2) is 2*sizeof(u1) etc. */
#define __JAVA_CLASSFILE_PARSER_NTOHS_LE(n) (((((java_classfile_parser_u2_t)(n) & 0x00FF)) << 8) | \
                                             ((((java_classfile_parser_u2_t)(n) & 0xFF00)) >> 8))

#define __JAVA_CLASSFILE_PARSER_NTOHL_LE(n) (((((java_classfile_parser_u4_t)(n) & 0x000000FF)) << 24) | \
                                             ((((java_classfile_parser_u4_t)(n) & 0x0000FF00)) << 8)  | \
                                             ((((java_classfile_parser_u4_t)(n) & 0x00FF0000)) >> 8)  | \
                                             ((((java_classfile_parser_u4_t)(n) & 0xFF000000)) >> 24))

#define __JAVA_CLASSFILE_PARSER_FREEV(type, onstack)                    \
  java_classfile_parser_##type##_t *_tofreep = &(onstack);              \
  __JAVA_CLASSFILE_PARSER_##type##_freev(_tofreep)                      \


#define _JAVA_CLASSFILE_PARSER_CHAR(type, onstack, endianness, u1, bufferp, lengthl) \
  if (lengthl-- > 0) {                                                  \
    onstack.u1 = (java_classfile_parser_u1_t) *bufferp++;               \
    __JAVA_CLASSFILE_PARSER_TRACE_CHAR(onstack.u1, onstack.u1, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

/* Our java_classfile_parser_u1_t is an unsigned char, bufferp is char *, so we can use direct assignment */
#define _JAVA_CLASSFILE_PARSER_U1(type, onstack, endianness, u1, bufferp, lengthl) \
  if (lengthl-- > 0) {                                                  \
    onstack.u1 = (java_classfile_parser_u1_t) *bufferp++;               \
    __JAVA_CLASSFILE_PARSER_TRACE_U1(onstack.u1, onstack.u1, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U1_ARRAY(type, onstack, endianness, arrayp, arrayl, bufferp, lengthl) \
  {                                                                     \
    size_t _arrayl = onstack.arrayl;                                    \
                                                                        \
    if (_arrayl > 0) {                                                  \
      if (lengthl >= _arrayl) {                                         \
        java_classfile_parser_u1_t *_p;                                 \
                                                                        \
        _p = (java_classfile_parser_u1_t *) malloc(_arrayl);            \
        if (_p == NULL) {                                               \
          int _save_errno = errno;                                      \
          __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                 \
          errno = _save_errno;                                          \
          return NULL;                                                  \
        }                                                               \
        memcpy(_p, bufferp, _arrayl);                                   \
        onstack.arrayp = _p;                                            \
        bufferp += _arrayl;                                             \
        lengthl -= _arrayl;                                             \
        __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(onstack.arrayp, onstack.arrayl, bufferp, lengthl) \
      } else {                                                          \
          __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                 \
          errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                     \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

/* The compiler will automatically optimize the test on sizeof() */
/* Indeed nothing guarantees that our sizeof(u2) == 2 * sizeof(u1) */
#define _JAVA_CLASSFILE_PARSER_U2_BE(type, onstack, u2, bufferp, lengthl) \
  if (lengthl >= 2) {                                                   \
    if (sizeof(java_classfile_parser_u2_t) == 2) {                      \
      memcpy(&(onstack.u2), bufferp, 2);                                \
      bufferp += 2;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _u1[2];                                \
                                                                        \
      _u1[0] = *bufferp++;                                              \
      _u1[1] = *bufferp++;                                              \
      onstack.u2 = _u1[0];                                              \
      onstack.u2 <<= 8;                                                 \
      onstack.u2 |= _u1[1];                                             \
    }                                                                   \
    lengthl -= 2;                                                       \
    __JAVA_CLASSFILE_PARSER_TRACE_U2(onstack.u2, onstack.u2, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U2_LE(type, onstack, u2, bufferp, lengthl) \
  if (lengthl >= 2) {                                                   \
    java_classfile_parser_u2_t _u2;                                     \
    if (sizeof(java_classfile_parser_u2_t) == 2) {                      \
      memcpy(&_u2, bufferp, 2);                                         \
      onstack.u2 = __JAVA_CLASSFILE_PARSER_NTOHS_LE(_u2);               \
      bufferp += 2;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _u1[2];                                \
                                                                        \
      _u1[0] = *bufferp++;                                              \
      _u1[1] = *bufferp++;                                              \
      onstack.u2 = _u1[0];                                              \
      onstack.u2 <<= 8;                                                 \
      onstack.u2 |= _u1[1];                                             \
    }                                                                   \
    lengthl -= 2;                                                       \
    __JAVA_CLASSFILE_PARSER_TRACE_U2(onstack.u2, _u2, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U2(type, onstack, endianness, u2, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U2_##endianness(type, onstack, u2, bufferp, lengthl) 

/* The compiler will automatically optimize the test on sizeof() */
/* Indeed nothing guarantees that our sizeof(u4) == 4 * sizeof(u1) */
#define _JAVA_CLASSFILE_PARSER_U4_BE(type, onstack, u4, bufferp, lengthl) \
  if (lengthl >= 4) {                                                   \
    if (sizeof(java_classfile_parser_u4_t) == 4) {                      \
      memcpy(&(onstack.u4), bufferp, 4);                                \
      bufferp += 4;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _u1[4];                                \
                                                                        \
      _u1[0] = *bufferp++;                                              \
      _u1[1] = *bufferp++;                                              \
      _u1[2] = *bufferp++;                                              \
      _u1[3] = *bufferp++;                                              \
      onstack.u4 = _u1[0];                                              \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[1];                                             \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[2];                                             \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[3];                                             \
      onstack.u4 <<= 8;                                                 \
    }                                                                   \
    lengthl -= 4;                                                       \
    __JAVA_CLASSFILE_PARSER_TRACE_U4(onstack.u4, onstack.u4, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U4_LE(type, onstack, u4, bufferp, lengthl) \
  if (lengthl >= 4) {                                                   \
    java_classfile_parser_u4_t _u4;                                     \
    if (sizeof(java_classfile_parser_u4_t) == 4) {                      \
      memcpy(&_u4, bufferp, 4);                                         \
      bufferp += 4;                                                     \
    } else {                                                            \
      java_classfile_parser_u1_t _u1[4];                                \
                                                                        \
      _u1[0] = *bufferp++;                                              \
      _u1[1] = *bufferp++;                                              \
      _u1[2] = *bufferp++;                                              \
      _u1[3] = *bufferp++;                                              \
      onstack.u4 = _u1[0];                                              \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[1];                                             \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[2];                                             \
      onstack.u4 <<= 8;                                                 \
      onstack.u4 |= _u1[3];                                             \
      onstack.u4 <<= 8;                                                 \
    }                                                                   \
    lengthl -= 4;                                                       \
    onstack.u4 = __JAVA_CLASSFILE_PARSER_NTOHL_LE(_u4);               \
    __JAVA_CLASSFILE_PARSER_TRACE_U4(onstack.u4, _u4, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_FREEV(type, onstack);                       \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U4(type, onstack, endianness, u4, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U4_##endianness(type, onstack, u4, bufferp, lengthl) 

/* We have to explicitely initialize all counters to 0 to avoid corruption at freev() phase in case of error */
#define _JAVA_CLASSFILE_PARSER_ClassFile(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(ClassFile, onstack, endianness, magic, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, minor_version, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, major_version, bufferp, lengthl); \
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
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, constant_pool_count, bufferp, lengthl); \
    if (onstack.constant_pool_count > 1) {                              \
      java_classfile_parser_u2_t _max = onstack.constant_pool_count - 1; \
      java_classfile_parser_u2_t _i;                                    \
                                                                        \
      onstack.constant_poolpp = (java_classfile_parser_cp_info_t **) malloc(_max * sizeof(java_classfile_parser_cp_info_t *)); \
      if (onstack.constant_poolpp == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_FREEV(ClassFile, onstack);              \
        return NULL;                                                    \
      }                                                                 \
      for (_i = 0; _i < _max; _i++) {                                   \
        onstack.constant_poolpp[_i] = _java_classfile_parser_cp_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.constant_poolpp[_i] == NULL) {                      \
          __JAVA_CLASSFILE_PARSER_FREEV(ClassFile, onstack);            \
          return NULL;                                                  \
        }                                                               \
        switch (onstack.constant_poolpp[_i]->tag) {                     \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:               \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:             \
          if (_i < (_max - 1)) {                                        \
            onstack.constant_poolpp[++_i] = NULL;                       \
          }                                                             \
          break;                                                        \
        default:                                                        \
          break;                                                        \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, this_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, super_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(ClassFile, onstack, endianness, interfaces_count, bufferp, lengthl); \
    if (onstack.interfaces_count > 0) {                                 \
      java_classfile_parser_u2_t _max = onstack.interfaces_count;       \
      onstack.interfacesp = (java_classfile_parser_u2_t *) malloc(_max * sizeof(java_classfile_parser_u2_t)); \
      if (onstack.interfacesp == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_FREEV(ClassFile, onstack);              \
        return NULL;                                                    \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_ClassFile_freev(p)                      \
  if (p->constant_poolpp != NULL) {                                     \
    if (p->constant_pool_count > 1) {                                   \
      java_classfile_parser_u2_t _max = p->constant_pool_count - 1;     \
      java_classfile_parser_u2_t _i;                                    \
      for (_i = 0; _i < _max; _i++) {                                   \
        _JAVA_CLASSFILE_PARSER_cp_info_freev(p->constant_poolpp[_i]);   \
      }                                                                 \
    }                                                                   \
    free(p->constant_poolpp);                                           \
  }                                                                     \
  if (p->interfacesp != NULL) {                                         \
    free(p->interfacesp);                                               \
  }

#define _JAVA_CLASSFILE_PARSER_ClassFile_freev(allocated)               \
  if (allocated != NULL) {                                              \
    __JAVA_CLASSFILE_PARSER_ClassFile_freev(allocated)                  \
    free(allocated);                                                    \
  }

#define _JAVA_CLASSFILE_PARSER_cp_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(cp_info, onstack, endianness, tag, bufferp, lengthl); \
    switch (onstack.tag) {                                              \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      onstack.u.classInfop = _java_classfile_parser_CONSTANT_Class_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.classInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      onstack.u.fieldrefInfop = _java_classfile_parser_CONSTANT_Fieldref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.fieldrefInfop == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      onstack.u.methodrefInfop = _java_classfile_parser_CONSTANT_Methodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodrefInfop == NULL) {                           \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      onstack.u.interfaceMethodrefInfop = _java_classfile_parser_CONSTANT_InterfaceMethodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.interfaceMethodrefInfop == NULL) {                  \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      onstack.u.stringInfop = _java_classfile_parser_CONSTANT_String_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.stringInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      onstack.u.integerInfop = _java_classfile_parser_CONSTANT_Integer_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.integerInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      onstack.u.floatInfop = _java_classfile_parser_CONSTANT_Float_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.floatInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      onstack.u.longInfop = _java_classfile_parser_CONSTANT_Long_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.longInfop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      onstack.u.doubleInfop = _java_classfile_parser_CONSTANT_Double_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.doubleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      onstack.u.nameAndTypeInfop = _java_classfile_parser_CONSTANT_NameAndType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.nameAndTypeInfop == NULL) {                         \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      onstack.u.utf8Infop = _java_classfile_parser_CONSTANT_Utf8_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.utf8Infop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      onstack.u.methodHandleInfop = _java_classfile_parser_CONSTANT_MethodHandle_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodHandleInfop == NULL) {                        \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      onstack.u.methodTypeInfop = _java_classfile_parser_CONSTANT_MethodType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodTypeInfop == NULL) {                          \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      onstack.u.invokeDynamicInfop = _java_classfile_parser_CONSTANT_InvokeDynamic_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.invokeDynamicInfop == NULL) {                       \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      onstack.u.moduleInfop = _java_classfile_parser_CONSTANT_Module_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.moduleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      onstack.u.packageInfop = _java_classfile_parser_CONSTANT_Package_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.packageInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    default:                                                            \
      errno = -1;                                                       \
      __JAVA_CLASSFILE_PARSER_FREEV(cp_info, onstack);                  \
      return NULL;                                                      \
    }                                                                   \
} while (0)

#define __JAVA_CLASSFILE_PARSER_cp_info_freev(p)                        \
    switch (p->tag) {                                                   \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(p->u.classInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(p->u.fieldrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(p->u.methodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(p->u.interfaceMethodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(p->u.stringInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(p->u.integerInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(p->u.floatInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(p->u.longInfop);  \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(p->u.doubleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(p->u.nameAndTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(p->u.utf8Infop);  \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(p->u.methodHandleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(p->u.methodTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(p->u.invokeDynamicInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(p->u.moduleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(p->u.packageInfop); \
      break;                                                            \
    default:                                                            \
      break;                                                            \
    }

#define _JAVA_CLASSFILE_PARSER_cp_info_freev(p) do {                    \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_cp_info_freev(p)                          \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Class_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(p) do {    \
    if (p != NULL) {                                                \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(p)          \
      free(p);                                                      \
    }                                                               \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Fieldref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Fieldref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(p) do {    \
    if (p != NULL) {                                                   \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(p)          \
      free(p);                                                         \
    }                                                                  \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Methodref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Methodref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(p) do {    \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(p)          \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_InterfaceMethodref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_InterfaceMethodref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(p) \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_String_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_String_info, onstack, endianness, string_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(p) do {    \
    if (p != NULL) {                                                 \
      __JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(p)          \
      free(p);                                                       \
    }                                                                \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Integer_info, onstack, endianness, bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(p) do {    \
    if (p != NULL) {                                                  \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(p)          \
      free(p);                                                       \
    }                                                                 \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Float_info, onstack, endianness, bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(p) do {        \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(p)              \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Long_info, onstack, endianness, high_bytes, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Long_info, onstack, endianness, low_bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(p) do {         \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(p)               \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Double_info, onstack, endianness, high_bytes, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(CONSTANT_Double_info, onstack, endianness, low_bytes, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(p) do {       \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(p)             \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_NameAndType_info, onstack, endianness, name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_NameAndType_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(p) do {  \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(p)        \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Utf8_info, onstack, endianness, length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(CONSTANT_Utf8_info, onstack, endianness, bytesp, length, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(p)             \
  if (p->bytesp != NULL) {                                              \
    free(p->bytesp);                                                    \
  }

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(p) do {         \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(p)               \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(CONSTANT_MethodHandle_info, onstack, endianness, reference_kind, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_MethodHandle_info, onstack, endianness, reference_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(p)       \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_MethodType_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(p) do {   \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(p)         \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_InvokeDynamic_info, onstack, endianness, bootstrap_method_attr_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_InvokeDynamic_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(p)      \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Module_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(p) do {       \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(p)             \
      free(p);                                                          \
    }                                                                   \
} while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info(endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(CONSTANT_Package_info, onstack, endianness, name_index, bufferp, lengthl); \
} while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(p) /* No op */

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(p) do {      \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(p)            \
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
    _JAVA_CLASSFILE_PARSER_##type(BE, type, bufferp, lengthl);          \
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
    _JAVA_CLASSFILE_PARSER_##type(LE, type, bufferp, lengthl);          \
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
      _JAVA_CLASSFILE_PARSER_##type(BE, type, bufferp, lengthl);        \
    } else {                                                            \
      _JAVA_CLASSFILE_PARSER_##type(LE, type, bufferp, lengthl);        \
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
    _JAVA_CLASSFILE_PARSER_##type##_freev(p);                           \
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
_JAVA_CLASSFILE_GENERATE_FUNCTION(ClassFile)
