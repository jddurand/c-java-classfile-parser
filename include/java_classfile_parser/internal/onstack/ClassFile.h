#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H

#include "java_classfile_parser/internal/onstack/cp_info.h"
#include "java_classfile_parser/internal/onstack/field_info.h"
#include "java_classfile_parser/internal/onstack/method_info.h"
#include "java_classfile_parser/internal/onstack/attribute_info.h"

/* We have to explicitely initialize all counters to 0 to avoid corruption at freev() phase in case of error */
/* The spec says that the constant_pool table is indexed from 1 to constant_pool_count - 1. This means that */
/* index 0 is unsable. So that array is: [0,1,...constant_pool_count - 1] i.e. constant_pool_count elements */
#define _JAVA_CLASSFILE_PARSER_ClassFile(scope, endianness, onstack, bufferp, lengthl) do { \
    onstack.constant_pool_count = 0;                                    \
    onstack.constant_poolpp = NULL;                                     \
    onstack.interfaces_count = 0;                                       \
    onstack.interfacesp = NULL;                                         \
    onstack.fields_count = 0;                                           \
    onstack.fieldspp = NULL;                                            \
    onstack.methods_count = 0;                                          \
    onstack.methodspp = NULL;                                           \
    onstack.attributes_count = 0;                                       \
    onstack.attributespp = NULL;                                        \
                                                                        \
    _JAVA_CLASSFILE_PARSER_U4(_##scope, ClassFile, onstack, endianness, magic, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, minor_version, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, major_version, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, constant_pool_count, bufferp, lengthl); \
    if (onstack.constant_pool_count > 1) {                              \
      java_classfile_parser_u2_t _##scope##max = onstack.constant_pool_count - 1; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.constant_poolpp = (java_classfile_parser_cp_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_cp_info_t *)); \
      if (onstack.constant_poolpp == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.constant_pool_count = 1;                                  \
      for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++, onstack.constant_pool_count++) { \
        onstack.constant_poolpp[_##scope##i] = _java_classfile_parser_cp_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.constant_poolpp[_##scope##i] == NULL) {             \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i+1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.constant_poolpp[_##scope##j] = NULL;                \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
          return NULL;                                                  \
        }                                                               \
        switch (onstack.constant_poolpp[_##scope##i]->tag) {            \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:               \
        case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:             \
          if (_##scope##i < (_##scope##max - 1)) {                      \
            onstack.constant_poolpp[++_##scope##i] = NULL;              \
            onstack.constant_pool_count++;;                             \
          }                                                             \
          break;                                                        \
        default:                                                        \
          break;                                                        \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, access_flags, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, this_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, super_class, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, interfaces_count, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2_ARRAY(_##scope, ClassFile, onstack, endianness, interfacesp, interfaces_count, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, fields_count, bufferp, lengthl); \
    if (onstack.fields_count > 0) {                                     \
      java_classfile_parser_u2_t _##scope##max = onstack.fields_count;  \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.fieldspp = (java_classfile_parser_field_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_field_info_t *)); \
      if (onstack.fieldspp == NULL) {                                   \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.fields_count = 0;                                         \
      for (_##scope##i = 0; _##scope##i < _max; _##scope##i++, onstack.fields_count++) { \
        onstack.fieldspp[_##scope##i] = _java_classfile_parser_field_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.fieldspp[_##scope##i] == NULL) {                    \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.fieldspp[_##scope##j] = NULL;                       \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, methods_count, bufferp, lengthl); \
    if (onstack.methods_count > 0) {                                    \
      java_classfile_parser_u2_t _##scope##max = onstack.methods_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.methodspp = (java_classfile_parser_method_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_method_info_t *)); \
      if (onstack.methodspp == NULL) {                                  \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.methods_count = 0;                                        \
      for (_##scope##i = 0; _##scope##i < _max; _##scope##i++, onstack.methods_count++) { \
        onstack.methodspp[_##scope##i] = _java_classfile_parser_method_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.methodspp[_##scope##i] == NULL) {                   \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.methodspp[_##scope##j] = NULL;                      \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ClassFile, onstack, endianness, attributes_count, bufferp, lengthl); \
    if (onstack.attributes_count > 0) {                                 \
      java_classfile_parser_u2_t _##scope##max = onstack.attributes_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.attributespp = (java_classfile_parser_attribute_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_attribute_info_t *)); \
      if (onstack.attributespp == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.attributes_count = 0;                                     \
      for (_##scope##i = 0; _##scope##i < _max; _##scope##i++, onstack.attributes_count++) { \
        onstack.attributespp[_##scope##i] = _java_classfile_parser_attribute_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
        if (onstack.attributespp[_##scope##i] == NULL) {                \
          java_classfile_parser_u2_t _##scope##j;                       \
                                                                        \
          for (_##scope##j = _##scope##i + 1; _##scope##j < _##scope##max; _##scope##j++) { \
            onstack.attributespp[_##scope##j] = NULL;                   \
          }                                                             \
          __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
          return NULL;                                                  \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_ClassFile_freev(scope, p) do {          \
    if (p->constant_poolpp != NULL) {                                   \
      if (p->constant_pool_count > 1) {                                 \
        java_classfile_parser_u2_t _##scope##max = p->constant_pool_count - 1; \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
          _java_classfile_parser_cp_info_freev(p->constant_poolpp[_##scope##i]); \
        }                                                               \
      }                                                                 \
      free(p->constant_poolpp);                                         \
    }                                                                   \
    if (p->interfacesp != NULL) {                                       \
      free(p->interfacesp);                                             \
    }                                                                   \
    if (p->fieldspp != NULL) {                                          \
      if (p->fields_count > 0) {                                        \
        java_classfile_parser_u2_t _##scope##max = p->fields_count;     \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
          _java_classfile_parser_field_info_freev(p->fieldspp[_##scope##i]); \
        }                                                               \
      }                                                                 \
      free(p->fieldspp);                                                \
    }                                                                   \
    if (p->methodspp != NULL) {                                         \
      if (p->methods_count > 0) {                                       \
        java_classfile_parser_u2_t _##scope##max = p->methods_count;    \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
          _java_classfile_parser_method_info_freev(p->methodspp[_##scope##i]); \
        }                                                               \
      }                                                                 \
      free(p->methodspp);                                               \
    }                                                                   \
    if (p->attributespp != NULL) {                                      \
      if (p->attributes_count > 0) {                                    \
        java_classfile_parser_u2_t _##scope##max = p->attributes_count; \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 0; _##scope##i < _##scope##max; _##scope##i++) { \
          _java_classfile_parser_attribute_info_freev(p->attributespp[_##scope##i]); \
        }                                                               \
      }                                                                 \
      free(p->attributespp);                                            \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_freev(scope, p) do {           \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_ClassFile_freev(_##scope, p);             \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(classfilep, p) do { \
    if (p->magic != 0xCAFEBABE) {                                       \
      errno = JAVA_CLASSFILE_PARSER_ERR_INVALID_CLASSFILE_MAGIC;        \
      return 0;                                                         \
    }                                                                   \
  } while (0)

/* Version check is done only if this software is compiled min and max version providers:
   - JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN
   - JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX

   These are inclusive limits.

   For example: -DJAVA_CLASSFILE_PARSER_JNI_VERSION_MIN=xxxmin -DJAVA_CLASSFILE_PARSER_JNI_VERSION_MAX=xxxmax
*/

#if defined(JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN) && defined(JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX)
/* We make a float out of major_version and minor_version and compares */
#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(classfilep, p) do { \
    float minf = (float) JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN;         \
    float maxf = (float) JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX;         \
    float f = (p->major_version * 1.0) + (p->minor_version / 10.);      \
                                                                        \
    if ((f < minf) || (f > maxf)) {                                     \
      errno = JAVA_CLASSFILE_PARSER_ERR_INVALID_CLASSFILE_UNSUPPORTED;  \
      return 0;                                                         \
    }                                                                   \
  } while (0)
#else
#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(classfilep, p) do { \
  } while (0)
#endif

#define _JAVA_CLASSFILE_PARSER_ClassFile_validateb(classfilep, p) do {  \
    _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(classfilep, p);    \
    _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(classfilep, p);  \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H */
