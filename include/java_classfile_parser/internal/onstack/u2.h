#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_H

#include "java_classfile_parser/internal/onstack/free.h"

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
    __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);     \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
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
    onstack.u2 = __JAVA_CLASSFILE_PARSER_NTOHS_LE(_##scope, _##scope##u2); \
    __JAVA_CLASSFILE_PARSER_TRACE_U2(_##scope, onstack.u2, _##scope##u2, bufferp, lengthl) \
  } else {                                                              \
    __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);     \
    errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                           \
    return NULL;                                                        \
  }

#define _JAVA_CLASSFILE_PARSER_U2(scope, type, onstack, endianness, u2, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U2_##endianness(_##scope, type, onstack, u2, bufferp, lengthl) 

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_H */
