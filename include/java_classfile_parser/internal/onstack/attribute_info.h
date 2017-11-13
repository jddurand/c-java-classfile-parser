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

#define _JAVA_CLASSFILE_PARSER_attribute_info_validate_module_modeb(scope, classfilep, p) do { \
    short _##scope##have_Moduleb = 0;                                   \
    java_classfile_parser_u2_t _##scope##i;                             \
                                                                        \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, "attribute", "..... Module mode"); \
    for (_##scope##i = 0; _##scope##i < classfilep->attributes_count; _##scope##i++) { \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_attribute_info_validateb(scope, classfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, "attribute", "start with attributes_count = %u, attributespp = %p", (unsigned long) classfilep->attributes_count, p); \
    if ((classfilep->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      _JAVA_CLASSFILE_PARSER_attribute_info_validate_module_modeb(scope, classfilep, p); \
    } else {                                                            \
    }                                                                   \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_ATTRIBUTE_INFO_H */
