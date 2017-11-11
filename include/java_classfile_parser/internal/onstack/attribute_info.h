#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H

/* From a pure parsing point of view, attributes are first scanned as if it was always an unknown attribute */
/* There is a post-processing phase that is putting a "type" on these attributes */
#define _JAVA_CLASSFILE_PARSER_attribute_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, attribute_info, onstack, endianness, attribute_name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, attribute_info, onstack, endianness, attribute_length, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U1_ARRAY(_##scope, attribute_info, onstack, endianness, infop, attribute_length, bufferp, lengthl); \
    onstack.type = JAVA_CLASSFILE_PARSER_ATTRIBUTE_INFO_Unknown;        \
    onstack.u.unknown.infop = onstack.infop;                            \
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

#define _JAVA_CLASSFILE_PARSER_attribute_info_validateb(scope, loaderp, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H */
