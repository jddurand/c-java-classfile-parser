#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_METHOD_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_METHOD_INFO_H

#include "java_classfile_parser/internal/onstack/attribute_info.h"

#define _JAVA_CLASSFILE_PARSER_method_info(scope, endianness, onstack, bufferp, lengthl) do { \
    onstack.attributes_count = 0;                                       \
    onstack.attributespp = 0;                                           \
                                                                        \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, method_info, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, method_info, onstack, endianness, name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, method_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, method_info, onstack, endianness, attributes_count, bufferp, lengthl); \
    if (onstack.attributes_count > 0) {                                 \
      java_classfile_parser_u2_t _##scope##max = onstack.attributes_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.attributespp = (java_classfile_parser_attribute_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_attribute_info_t *)); \
      if (onstack.attributespp == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, method_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.attributes_count = 0;                                     \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++, onstack.attributes_count++) { \
        onstack.attributespp[_##scope##i] = _java_classfile_parser_attribute_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.attributespp[_##scope##i] == NULL) {                \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.attributespp[_##scope##j] = NULL;                   \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, method_info, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_method_info_freev(scope, p) do {        \
    if (p->attributespp != NULL) {                                      \
      if (p->attributes_count > 0) {                                    \
        java_classfile_parser_u2_t _##scope##max = p->attributes_count; \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
          _JAVA_CLASSFILE_PARSER_attribute_info_freev(_##scope, p->attributespp[_##scope##i]); \
        }                                                               \
      }                                                                 \
      free(p->attributespp);                                            \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_method_info_freev(scope, p) do {         \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_method_info_freev(_##scope, p);           \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_method_info_validateb(scope, classfilep, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_METHOD_INFO_H */
