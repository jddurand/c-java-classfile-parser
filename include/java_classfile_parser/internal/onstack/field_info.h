#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FIELD_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FIELD_INFO_H

#include "java_classfile_parser/internal/onstack/attribute_info.h"

#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PUBLIC
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PRIVATE
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PROTECTED
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_STATIC
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_FINAL
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_VOLATILE
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_TRANSIENT
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_SYNTHETIC
#undef JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_ENUM

#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PUBLIC     0x0001 /* Declared public; may be accessed from outside its package. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PRIVATE    0x0002 /* Declared private; usable only within the defining class. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PROTECTED  0x0004 /* Declared protected; may be accessed within subclasses. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_STATIC     0x0008 /* Declared static. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_FINAL      0x0010 /* Declared final; never directly assigned to after object construction (JLS §17.5). */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_VOLATILE   0x0040 /* Declared volatile; cannot be cached. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_TRANSIENT  0x0080 /* Declared transient; not written or read by a persistent object manager. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_SYNTHETIC  0x1000 /* Declared synthetic; not present in the source code. */
#define JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_ENUM       0x4000 /* Declared as an element of an enum. */

#define _JAVA_CLASSFILE_PARSER_field_info(scope, endianness, onstack, bufferp, lengthl) do { \
    onstack.attributes_count = 0;                                       \
    onstack.attributespp = 0;                                           \
                                                                        \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, name_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, descriptor_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, field_info, onstack, endianness, attributes_count, bufferp, lengthl); \
    if (onstack.attributes_count > 0) {                                 \
      java_classfile_parser_u2_t _##scope##max = onstack.attributes_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.attributespp = (java_classfile_parser_attribute_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_attribute_info_t *)); \
      if (onstack.attributespp == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, field_info, onstack); \
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
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, field_info, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_field_info_freev(scope, p) do {         \
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

#define _JAVA_CLASSFILE_PARSER_field_info_freev(scope, p) do {          \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_field_info_freev(_##scope, p);            \
      free(p);                                                          \
    }                                                                   \
  } while (0)

/* Each field of a class may have at most one of its ACC_PUBLIC, ACC_PRIVATE, and ACC_PROTECTED flags set (JLS §8.3.1), */
/* and must not have both its ACC_FINAL and ACC_VOLATILE flags set (JLS §8.3.1.4).  */
#define _JAVA_CLASSFILE_PARSER_field_info_access_flags_validateb(scope, contexts, classfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", "start with access_flags = 0x%08lx", (unsigned long) p->access_flags); \
                                                                        \
      java_classfile_parser_u2_t _##scope##access_flags = p->access_flags; \
      short _##scope##publicb = ((_##scope##access_flags & JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PUBLIC) == JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PUBLIC) ? 1 : 0; \
      short _##scope##privateb = ((_##scope##access_flags & JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PRIVATE) == JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PRIVATE) ? 1 : 0; \
      short _##scope##protectedb = ((_##scope##access_flags & JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PROTECTED) == JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_PROTECTED) ? 1 : 0; \
      short _##scope##finalb = ((_##scope##access_flags & JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_FINAL) == JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_FINAL) ? 1 : 0; \
      short _##scope##volatileb = ((_##scope##access_flags & JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_VOLATILE) == JAVA_CLASSFILE_PARSER_FIELD_INFO_ACC_VOLATILE) ? 1 : 0; \
                                                                        \
      __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... publicb + privateb + protectedb = %d > 1 ?", (int) (_##scope##publicb + _##scope##privateb + _##scope##protectedb)); \
      if ((_##scope##publicb + _##scope##privateb + _##scope##protectedb) > 1) { \
        errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_FIELD_INFO_ACCESS_FLAGS; \
        return 0;                                                       \
      }                                                                 \
      __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... finalb + volatileb = %d > 1 ?", (int) (_##scope##finalb + _##scope##volatileb)); \
      if ((_##scope##finalb + _##scope##volatileb) > 1) { \
        errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_FIELD_INFO_ACCESS_FLAGS; \
        return 0;                                                       \
      }                                                                 \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_field_info_validateb(scope, classfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, "field_info", "start with p = %p", p); \
    _JAVA_CLASSFILE_PARSER_field_info_access_flags_validateb(_##scope, "field_info", classfilep, p); \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FIELD_INFO_H */
