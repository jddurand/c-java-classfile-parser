#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_ARRAY_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_ARRAY_H

#include "java_classfile_parser/internal/onstack/free.h"

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
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);       \
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
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);       \
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
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);     \
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
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);       \
          errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                     \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

#define _JAVA_CLASSFILE_PARSER_U2_ARRAY(scope, type, onstack, endianness, arrayp, arrayl, bufferp, lengthl) _JAVA_CLASSFILE_PARSER_U2_ARRAY_##endianness(_##scope, type, onstack, arrayp, arrayl, bufferp, lengthl) 

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U2_ARRAY_H */
