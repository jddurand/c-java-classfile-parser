#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H

#define _JAVA_CLASSFILE_PARSER_attribute_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, attribute_info, onstack, endianness, attribute_name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, attribute_info, onstack, endianness, attribute_length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(_##scope, attribute_info, onstack, endianness, infop, attribute_length, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_attribute_info_freev(scope, p) do {     \
    if (p->infop != NULL) {                                             \
      free(p->infop);                                                   \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_attribute_info_freev(scope, p) do {      \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_attribute_info_freev(_##scope, p);        \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H */
