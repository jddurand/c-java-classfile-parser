#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_UTF8_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_UTF8_INFO_H

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_Utf8_info, onstack, endianness, length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(_##scope, CONSTANT_Utf8_info, onstack, endianness, bytesp, length, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(scope, p) do { \
    if (p->bytesp != NULL) {                                            \
      free(p->bytesp);                                                  \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(scope, p) do {  \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(_##scope, p);    \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_UTF8_INFO_H */
