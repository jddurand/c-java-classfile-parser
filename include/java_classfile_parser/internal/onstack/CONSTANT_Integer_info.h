#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTEGER_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTEGER_INFO_H

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, CONSTANT_Integer_info, onstack, endianness, bytes, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(scope, p) do { \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(_##scope, p); \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_validateb(scope, classfilep, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTEGER_INFO_H */
