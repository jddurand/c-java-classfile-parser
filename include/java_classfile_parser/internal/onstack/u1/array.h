#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_ARRAY_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_ARRAY_H

#include "java_classfile_parser/internal/onstack/free.h"

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
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack); \
          errno = _##scope##save_errno;                                 \
          return NULL;                                                  \
        }                                                               \
        onstack.arrayp = _##scope##p;                                   \
        memcpy(_##scope##p, bufferp, _##scope##arrayl);                 \
        bufferp += _##scope##arrayl;                                    \
        lengthl -= _##scope##arrayl;                                    \
        __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(_##scope, onstack.arrayp, onstack.arrayl, bufferp, lengthl) \
      } else {                                                          \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack); \
        errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                       \
        return NULL;                                                    \
      }                                                                 \
    } else {                                                            \
      onstack.arrayp = NULL;                                            \
    }                                                                   \
  }

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_ARRAY_H */
