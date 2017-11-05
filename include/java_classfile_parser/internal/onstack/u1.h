#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_H

/* Our java_classfile_parser_u1_t is an unsigned char, bufferp is char *, so we can use direct assignment */
#define _JAVA_CLASSFILE_PARSER_U1(scope, type, onstack, endianness, u1, bufferp, lengthl) do { \
    if (lengthl-- > 0) {                                                \
      onstack.u1 = (java_classfile_parser_u1_t) *bufferp++;             \
      __JAVA_CLASSFILE_PARSER_TRACE_U1(_##scope, onstack.u1, onstack.u1, bufferp, lengthl); \
    } else {                                                            \
      __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, type, onstack);   \
      errno = JAVA_CLASSFILE_PARSER_ERR_EFAULT;                         \
      return NULL;                                                      \
    }                                                                   \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_U1_H */
