#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U4_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U4_H

/* The compiler will automatically optimize the test on sizeof() */
/* Indeed nothing guarantees that our sizeof(u4) == 4 * sizeof(u1) */
#define _JAVA_CLASSFILE_PARSER_U4_BE(scope, type, onstack, u4, bufferp, lengthl) do { \
    if (lengthl >= 4) {                                                 \
      if (sizeof(java_classfile_parser_u4_t) == 4) {                    \
        memcpy(&(onstack.u4), bufferp, 4);                              \
        bufferp += 4;                                                   \
      } else {                                                          \
        java_classfile_parser_u1_t _##scope##u1[4];                     \
                                                                        \
        _##scope##u1[0] = *bufferp++;                                   \
        _##scope##u1[1] = *bufferp++;                                   \
        _##scope##u1[2] = *bufferp++;                                   \
        _##scope##u1[3] = *bufferp++;                                   \
        onstack.u4 = _##scope##u1[0];                                   \
        onstack.u4 <<= 8;                                               \
        onstack.u4 |= _##scope##u1[1];                                  \
        onstack.u4 <<= 8;                                               \
        onstack.u4 |= _##scope##u1[2];                                  \
        onstack.u4 <<= 8;                                               \
        onstack.u4 |= _##scope##u1[3];                                  \
        onstack.u4 <<= 8;                                               \
      }                                                                 \
      lengthl -= 4;                                                     \
      __JAVA_CLASSFILE_PARSER_TRACE_U4(_##scope, onstack.u4, onstack.u4, bufferp, lengthl); \
    } else {                                                            \
      __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);   \
      errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                         \
      return NULL;                                                      \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_U4_LE(scope, type, onstack, u4, bufferp, lengthl) do { \
    if (lengthl >= 4) {                                                 \
      java_classfile_parser_u4_t _##scope##u4;                          \
      if (sizeof(java_classfile_parser_u4_t) == 4) {                    \
        memcpy(&_##scope##u4, bufferp, 4);                              \
        bufferp += 4;                                                   \
      } else {                                                          \
        java_classfile_parser_u1_t _##scope##u1[4];                     \
                                                                        \
        _##scope##u1[0] = *bufferp++;                                   \
        _##scope##u1[1] = *bufferp++;                                   \
        _##scope##u1[2] = *bufferp++;                                   \
        _##scope##u1[3] = *bufferp++;                                   \
        _##scope##u4 = _##scope##u1[0];                                 \
        _##scope##u4 <<= 8;                                             \
        _##scope##u4 |= _##scope##u1[1];                                \
        _##scope##u4 <<= 8;                                             \
        _##scope##u4 |= _##scope##u1[2];                                \
        _##scope##u4 <<= 8;                                             \
        _##scope##u4 |= _##scope##u1[3];                                \
        _##scope##u4 <<= 8;                                             \
      }                                                                 \
      lengthl -= 4;                                                     \
      onstack.u4 = __JAVA_CLASSFILE_PARSER_NTOHL_LE(_##scope, _##scope##u4); \
      __JAVA_CLASSFILE_PARSER_TRACE_U4(_##scope, onstack.u4, _##scope##u4, bufferp, lengthl); \
    } else {                                                            \
      __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);   \
      errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                         \
      return NULL;                                                      \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_U4(scope, type, onstack, endianness, u4, bufferp, lengthl) \
  _JAVA_CLASSFILE_PARSER_U4_##endianness(_##scope, type, onstack, u4, bufferp, lengthl) 

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U4_H */
