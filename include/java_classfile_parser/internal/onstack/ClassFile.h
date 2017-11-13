#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H

#include "java_classfile_parser/internal/onstack/cp_info.h"
#include "java_classfile_parser/internal/onstack/field_info.h"
#include "java_classfile_parser/internal/onstack/method_info.h"
#include "java_classfile_parser/internal/onstack/attribute_info.h"

#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_PUBLIC
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SUPER
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SYNTHETIC
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ANNOTATION
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ENUM
#undef JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE

#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_PUBLIC      0x0001 /* Declared public; may be accessed from outside its package. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL       0x0010 /* Declared final; no subclasses allowed. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SUPER       0x0020 /* Treat superclass methods specially when invoked by the invokespecial instruction. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE   0x0200 /* Is an interface, not a class. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT    0x0400 /* Declared abstract; must not be instantiated. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SYNTHETIC   0x1000 /* Declared synthetic; not present in the source code. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ANNOTATION  0x2000 /* Declared as an annotation type. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ENUM        0x4000 /* Declared as an enum type. */
#define JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE      0x8000 /* Is a module, not a class or interface. */

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
      java_classfile_parser_u2_t _##scope##max = onstack.constant_pool_count; \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
      onstack.constant_poolpp = (java_classfile_parser_cp_info_t **) malloc(_##scope##max * sizeof(java_classfile_parser_cp_info_t *)); \
      if (onstack.constant_poolpp == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, ClassFile, onstack); \
        return NULL;                                                    \
      }                                                                 \
      onstack.constant_poolpp[0] = NULL;                                \
      onstack.constant_pool_count = 1;                                  \
      for (_##scope##i = 1; _##scope##i < _##scope##max; _##scope##i++, onstack.constant_pool_count++) { \
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
        onstack.fieldspp[_##scope##i]->classfilep = &onstack;           \
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
        onstack.methodspp[_##scope##i]->classfilep = &onstack;          \
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
        onstack.attributespp[_##scope##i]->classfilep = &onstack;          \
      }                                                                 \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_ClassFile_freev(scope, p) do {          \
    if (p->constant_poolpp != NULL) {                                   \
      if (p->constant_pool_count > 1) {                                 \
        java_classfile_parser_u2_t _##scope##max = p->constant_pool_count; \
        java_classfile_parser_u2_t _##scope##i;                         \
        for (_##scope##i = 1; _##scope##i < _##scope##max; _##scope##i++) { \
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

/* ******************************************************************* */
/*                             Validation                              */
/* Most of the validation is splitted in two modes:                    */
/* - Module mode                                                       */
/* - Non-mModule mode                                                  */
/*   The later is sometimes splitted in two sub-modes:                 */
/*   + Interface mode                                                  */
/*   + Class mode                                                      */
/* ******************************************************************* */

/* If module:
   -  no other flag in the access_flags item may be set
   - major_version, minor_version: >= 53.0 (i.e. Java SE 9 and above)
   - this_class: module-info
   - super_class, interfaces_count, fields_count, methods_count: zero
   - attributes: One Module attribute must be present. Except for Module, ModulePackages, ModuleMainClass, InnerClasses, SourceFile, SourceDebugExtension, RuntimeVisibleAnnotations, and RuntimeInvisibleAnnotations, none of the pre-defined attributes may appear:
     * ConstantValue
     * Code
     * StackMapTable
     * Exceptions
     * BootstrapMethods
     * InnerClasses
     * EnclosingMethod
     * Synthetic
     * Signature
     * SourceFile
     * LineNumberTable
     * LocalVariableTable
     * LocalVariableTypeTable
     * SourceDebugExtension
     * Deprecated
     * RuntimeVisibleAnnotations
     * RuntimeInvisibleAnnotations
     * RuntimeVisibleParameterAnnotations
     * RuntimeInvisibleParameterAnnotations
     * RuntimeVisibleTypeAnnotations
     * RuntimeInvisibleTypeAnnotations
     * AnnotationDefault
     * MethodParameters
     * Module
     * ModulePackages
     * ModuleMainClass
   Else:
   - An interface is distinguished by the ACC_INTERFACE flag being set. If the ACC_INTERFACE flag is not set, this class file defines a class, not an interface or module.
   - If the ACC_INTERFACE flag is set, the ACC_ABSTRACT flag must also be set, and the ACC_FINAL, ACC_SUPER, ACC_ENUM, and ACC_MODULE flags set must not be set.
   - If the ACC_INTERFACE flag is not set, any of the other flags in Table 4.1-A may be set except ACC_ANNOTATION and ACC_MODULE. However, such a class file must not have both its ACC_FINAL and ACC_ABSTRACT flags set (JLS 8.1.1.2).
   - The ACC_SUPER flag indicates which of two alternative semantics is to be expressed by the invokespecial instruction (invokespecial) if it appears in this class or interface. Compilers to the instruction set of the Java Virtual Machine should set the ACC_SUPER flag. In Java SE 8 and above, the Java Virtual Machine considers the ACC_SUPER flag to be set in every class file, regardless of the actual value of the flag in the class file and the version of the class file.
   - The ACC_SUPER flag exists for backward compatibility with code compiled by older compilers for the Java programming language. In JDK releases prior to 1.0.2, the compiler generated access_flags in which the flag now representing ACC_SUPER had no assigned meaning, and Oracle's Java Virtual Machine implementation ignored the flag if it was set.
   - The ACC_SYNTHETIC flag indicates that this class or interface was generated by a compiler and does not appear in source code.
   - An annotation type (JLS 9.6) must have its ACC_ANNOTATION flag set. If the ACC_ANNOTATION flag is set, the ACC_INTERFACE flag must also be set.
   - The ACC_ENUM flag indicates that this class or its superclass is declared as an enumerated type (JLS 8.9).
   - All bits of the access_flags item not assigned in Table 4.1-A are reserved for future use. They should be set to zero in generated class files and should be ignored by Java Virtual Machine implementations.

   Note that the sentence "An annotation type (JLS 9.6) must have its ACC_ANNOTATION flag set. If the ACC_ANNOTATION flag is set, the ACC_INTERFACE flag must also be set." does not require a test because:
   - In Module mode ACC_ANNOTATION is not allowed
   - In Interface mode ACC_ANNOTATION MAY be set
   - In Class mode ACC_ANNOTATION is not allowed
   so the case ACC_ANNOTATION can happen only in the interface mode, so ACC_INTERFACE is set by definition.
     */

/* =================================================================== */
/* magic validation                                                    */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".magic", "start with magic = 0x%08lx", (unsigned long) p->magic); \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".magic", ".......... magic == 0x%08lx ?", (unsigned long) 0xCAFEBABE); \
    if (p->magic != 0xCAFEBABE) {                                       \
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_MAGIC;		\
      return 0;                                                         \
    }                                                                   \
  } while (0)

/* =================================================================== */
/* version validation                                                  */
/* =================================================================== */

/* Version check is done only if this software is compiled with min and max version providers:
   - JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN (inclusive)
   - JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX (inclusive)
   unless in case of a module, where minimum major_version is known in advance: 53.

   For example: -DJAVA_CLASSFILE_PARSER_JNI_VERSION_MIN=xxxmin -DJAVA_CLASSFILE_PARSER_JNI_VERSION_MAX=xxxmax
*/

#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validate_module_modeb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".version", "..... Module mode"); \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".version", ".......... major_version < 53 ?"); \
    if (p->major_version < 53) {                                        \
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_VERSION;   \
      return 0;                                                         \
    }									\
  } while (0)

#if defined(JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN) && defined(JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX)
/* We make a float out of major_version and minor_version and compares */
#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validate_non_module_modeb(scope, contexts, superclassfilep, p) do { \
    float _##scope##minf = (float) JAVA_CLASSFILE_PARSER_JNI_VERSION_MIN; \
    float _##scope##maxf = (float) JAVA_CLASSFILE_PARSER_JNI_VERSION_MAX; \
    float _##scope##f = (p->major_version * 1.0) + (p->minor_version / 10.); \
                                                                        \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".version", "..... Non-Module mode"); \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".version", ".......... %.1f <= %.1f <= %.1f ?", _##scope##minf, _##scope##f, _##scope##maxf); \
    if ((_##scope##f < _##scope##minf) || (_##scope##f > _##scope##maxf)) { \
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_UNSUPPORTED;          \
      return 0;                                                         \
    }                                                                   \
  } while (0)
#else
#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validate_non_module_modeb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".version", "..... Non-Module mode skipped"); \
  } while (0)
#endif

#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".version", "start with major_version = %u, minor_version = %u", (unsigned int) p->major_version, (unsigned int) p->minor_version); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      _JAVA_CLASSFILE_PARSER_ClassFile_version_validate_module_modeb(scope, contexts, superclassfilep, p); \
    } else {                                                            \
      _JAVA_CLASSFILE_PARSER_ClassFile_version_validate_non_module_modeb(scope, contexts, superclassfilep, p); \
    }                                                                   \
  } while (0)

/* =================================================================== */
/* access_flags validation                                             */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_access_flags_validate_module_modeb(scope, contexts, superclassfilep, p) do { \
    static const char *_##scope##utf8kos[] = {                          \
      UTF8_BYTES_ConstantValue,                                         \
      UTF8_BYTES_Code,                                                  \
      UTF8_BYTES_StackMapTable,                                         \
      UTF8_BYTES_Exceptions,						\
      UTF8_BYTES_InnerClasses,                                          \
      UTF8_BYTES_EnclosingMethod,					\
      UTF8_BYTES_Synthetic,						\
      UTF8_BYTES_Signature,						\
      UTF8_BYTES_SourceFile,						\
      UTF8_BYTES_SourceDebugExtension,                                  \
      UTF8_BYTES_LineNumberTable,					\
      UTF8_BYTES_LocalVariableTable,					\
      UTF8_BYTES_LocalVariableTypeTable,				\
      UTF8_BYTES_Deprecated,						\
      UTF8_BYTES_RuntimeVisibleAnnotations,				\
      UTF8_BYTES_RuntimeInvisibleAnnotations,				\
      UTF8_BYTES_RuntimeVisibleParameterAnnotations,			\
      UTF8_BYTES_RuntimeInvisibleParameterAnnotations,                  \
      UTF8_BYTES_RuntimeVisibleTypeAnnotations,                         \
      UTF8_BYTES_RuntimeInvisibleTypeAnnotations,			\
      UTF8_BYTES_AnnotationDefault,					\
      UTF8_BYTES_BootstrapMethods,					\
      UTF8_BYTES_MethodParameters,					\
      UTF8_BYTES_Module,						\
      UTF8_BYTES_ModulePackages,					\
      UTF8_BYTES_ModuleMainClass					\
    };                                                                  \
    static const java_classfile_parser_u2_t _##scope##utf8kolength[] = { \
      UTF8_LENGTH_ConstantValue,					\
      UTF8_LENGTH_Code,                                                 \
      UTF8_LENGTH_StackMapTable,					\
      UTF8_LENGTH_Exceptions,						\
      UTF8_LENGTH_InnerClasses,                                         \
      UTF8_LENGTH_EnclosingMethod,					\
      UTF8_LENGTH_Synthetic,						\
      UTF8_LENGTH_Signature,						\
      UTF8_LENGTH_SourceFile,						\
      UTF8_LENGTH_SourceDebugExtension,                                 \
      UTF8_LENGTH_LineNumberTable,					\
      UTF8_LENGTH_LocalVariableTable,					\
      UTF8_LENGTH_LocalVariableTypeTable,				\
      UTF8_LENGTH_Deprecated,						\
      UTF8_LENGTH_RuntimeVisibleAnnotations,				\
      UTF8_LENGTH_RuntimeInvisibleAnnotations,                          \
      UTF8_LENGTH_RuntimeVisibleParameterAnnotations,			\
      UTF8_LENGTH_RuntimeInvisibleParameterAnnotations,                 \
      UTF8_LENGTH_RuntimeVisibleTypeAnnotations,			\
      UTF8_LENGTH_RuntimeInvisibleTypeAnnotations,			\
      UTF8_LENGTH_AnnotationDefault,					\
      UTF8_LENGTH_BootstrapMethods,					\
      UTF8_LENGTH_MethodParameters,					\
      UTF8_LENGTH_Module,						\
      UTF8_LENGTH_ModulePackages,					\
      UTF8_LENGTH_ModuleMainClass					\
    };                                                                  \
    int _##scope##i;							\
    java_classfile_parser_CONSTANT_Utf8_info_t *_##scope##utf8_infop = NULL; \
    java_classfile_parser_u2_t _##scope##utf8_length;			\
    java_classfile_parser_u1_t *_##scope##utf8_bytesp;                  \
									\
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", "..... Module mode"); \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... access_flags == 0x%8lx ?", (unsigned long) JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE); \
    if (p->access_flags != JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FLAG;	\
      return 0;                                                         \
    }									\
      									\
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(                           \
	_##scope,							\
	contexts ".access_flags",					\
	p,                                                              \
	p->attributespp[0]->attribute_name_index,			\
	JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8,			\
	JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX, \
	{								\
	_##scope##utf8_infop = __##scope##cp_infop->u.utf8Infop;	\
	_##scope##utf8_length = _##scope##utf8_infop->length;		\
	_##scope##utf8_bytesp = _##scope##utf8_infop->bytesp;		\
	}								\
	);								\
      __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".access_flags", "Current JavaUtf8 bytes at constant poolpp[attributespp[0]->attribute_name_index]", _##scope##utf8_bytesp, _##scope##utf8_length); \
      if (_##scope##utf8_length > 0) {                                  \
	for (_##scope##i = 0; _##scope##i < sizeof(_##scope##utf8kos) / sizeof(_##scope##utf8kos[0]); _##scope##i++) { \
  	  if (_##scope##utf8_length == _##scope##utf8kolength[_##scope##i]) { \
	    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... Attribute's CONSTANT_Utf8 is %s ?", _##scope##utf8kos[_##scope##i]); \
            if (memcmp(_##scope##utf8_bytesp, _##scope##utf8kos[_##scope##i], _##scope##utf8_length) == 0) { \
	      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME; \
	      return 0;							\
            }								\
	  }                                          			\
	}								\
      }									\
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_access_flags_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", "start with access_flags = 0x%08lx", (unsigned long) p->access_flags); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      static const char *_##scope##utf8kos[] = {			\
        UTF8_BYTES_ConstantValue,                                       \
        UTF8_BYTES_Code,                                                \
        UTF8_BYTES_StackMapTable,                                       \
        UTF8_BYTES_Exceptions,						\
        UTF8_BYTES_InnerClasses,                                        \
        UTF8_BYTES_EnclosingMethod,					\
        UTF8_BYTES_Synthetic,						\
        UTF8_BYTES_Signature,						\
        UTF8_BYTES_SourceFile,						\
        UTF8_BYTES_SourceDebugExtension,                                \
        UTF8_BYTES_LineNumberTable,					\
        UTF8_BYTES_LocalVariableTable,					\
        UTF8_BYTES_LocalVariableTypeTable,				\
        UTF8_BYTES_Deprecated,						\
        UTF8_BYTES_RuntimeVisibleAnnotations,				\
        UTF8_BYTES_RuntimeInvisibleAnnotations,				\
        UTF8_BYTES_RuntimeVisibleParameterAnnotations,			\
        UTF8_BYTES_RuntimeInvisibleParameterAnnotations,                \
        UTF8_BYTES_RuntimeVisibleTypeAnnotations,                       \
        UTF8_BYTES_RuntimeInvisibleTypeAnnotations,			\
        UTF8_BYTES_AnnotationDefault,					\
        UTF8_BYTES_BootstrapMethods,					\
        UTF8_BYTES_MethodParameters,					\
        UTF8_BYTES_Module,						\
        UTF8_BYTES_ModulePackages,					\
        UTF8_BYTES_ModuleMainClass					\
      };                                                                \
      static const java_classfile_parser_u2_t _##scope##utf8kolength[] = { \
        UTF8_LENGTH_ConstantValue,					\
        UTF8_LENGTH_Code,                                               \
        UTF8_LENGTH_StackMapTable,					\
        UTF8_LENGTH_Exceptions,						\
        UTF8_LENGTH_InnerClasses,                                       \
        UTF8_LENGTH_EnclosingMethod,					\
        UTF8_LENGTH_Synthetic,						\
        UTF8_LENGTH_Signature,						\
        UTF8_LENGTH_SourceFile,						\
        UTF8_LENGTH_SourceDebugExtension,                               \
        UTF8_LENGTH_LineNumberTable,					\
        UTF8_LENGTH_LocalVariableTable,					\
        UTF8_LENGTH_LocalVariableTypeTable,				\
        UTF8_LENGTH_Deprecated,						\
        UTF8_LENGTH_RuntimeVisibleAnnotations,				\
        UTF8_LENGTH_RuntimeInvisibleAnnotations,                        \
        UTF8_LENGTH_RuntimeVisibleParameterAnnotations,			\
        UTF8_LENGTH_RuntimeInvisibleParameterAnnotations,               \
        UTF8_LENGTH_RuntimeVisibleTypeAnnotations,			\
        UTF8_LENGTH_RuntimeInvisibleTypeAnnotations,			\
        UTF8_LENGTH_AnnotationDefault,					\
        UTF8_LENGTH_BootstrapMethods,					\
        UTF8_LENGTH_MethodParameters,					\
        UTF8_LENGTH_Module,						\
        UTF8_LENGTH_ModulePackages,					\
        UTF8_LENGTH_ModuleMainClass					\
      };                                                                \
      int _##scope##i;							\
      java_classfile_parser_CONSTANT_Utf8_info_t *_##scope##utf8_infop = NULL; \
      java_classfile_parser_u2_t _##scope##utf8_length;			\
      java_classfile_parser_u1_t *_##scope##utf8_bytesp;		\
									\
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... access_flags == 0x%8lx ?", (unsigned long) JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE); \
      if (p->access_flags != JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) {				\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FLAG;	\
	return 0;							\
      }									\
      									\
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(                           \
	_##scope,							\
	contexts ".access_flags",					\
	p,                                                              \
	p->attributespp[0]->attribute_name_index,			\
	JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8,			\
	JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX, \
	{								\
	_##scope##utf8_infop = __##scope##cp_infop->u.utf8Infop;	\
	_##scope##utf8_length = _##scope##utf8_infop->length;		\
	_##scope##utf8_bytesp = _##scope##utf8_infop->bytesp;		\
	}								\
	);								\
      __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".access_flags", "Current JavaUtf8 bytes at constant poolpp[attributespp[0]->attribute_name_index]", _##scope##utf8_bytesp, _##scope##utf8_length); \
      if (_##scope##utf8_length > 0) {                                  \
	for (_##scope##i = 0; _##scope##i < sizeof(_##scope##utf8kos) / sizeof(_##scope##utf8kos[0]); _##scope##i++) { \
  	  if (_##scope##utf8_length == _##scope##utf8kolength[_##scope##i]) { \
	    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".access_flags", ".......... Attribute's CONSTANT_Utf8 is %s ?", _##scope##utf8kos[_##scope##i]); \
            if (memcmp(_##scope##utf8_bytesp, _##scope##utf8kos[_##scope##i], _##scope##utf8_length) == 0) { \
	      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME; \
	      return 0;							\
            }								\
	  }                                          			\
	}								\
      }									\
    } else {                                                            \
      if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE) { \
	__JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", "..... Interface mode"); \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT) != JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_ABSTRACT; \
          return 0;                                                     \
        }                                                               \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_FINAL; \
          return 0;                                                     \
        }                                                               \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SUPER) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_SUPER) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_SUPER; \
          return 0;                                                     \
        }                                                               \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ENUM) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ENUM) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_ENUM; \
          return 0;                                                     \
        }                                                               \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_MODULE; \
          return 0;                                                     \
        }                                                               \
      } else {                                                          \
	__JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", "..... Class mode"); \
	__JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", ".......... access_flags & ACC_ANNOTATION == ACC_ANNOTATION ?"); \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ANNOTATION) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ANNOTATION) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_ANNOTATION; \
          return 0;                                                     \
        }                                                               \
	__JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", ".......... access_flags & ACC_MODULE == ACC_MODULE ?"); \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_MODULE; \
          return 0;                                                     \
        }                                                               \
	__JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", ".......... access_flags & ACC_FINAL == ACC_FINAL ?"); \
        if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_FINAL) { \
	  __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".access_flags", ".......... access_flags & ACC_ABSTRACT == ACC_ABSTRACT ?"); \
	  if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_ABSTRACT) { \
	    errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_FINAL_ABSTRACT; \
	    return 0;							\
	  }								\
        }                                                               \
      }                                                                 \
    }									\
  } while (0)

/* =================================================================== */
/* this_class validation                                               */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_this_class_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".this_class", "start with this_class = %u", (unsigned int) p->this_class); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... this_class is a CONSTANT_Module_info ?"); \
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(                           \
	_##scope,							\
	contexts ".this_class",                                         \
	p,                                                              \
	p->this_class,							\
	JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module,			\
	JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_THIS_CLASS,	\
	_JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK				\
	);								\
    } else {                                                            \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Non-module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... this_class is a CONSTANT_Class_info ?"); \
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(_##scope,			\
					     contexts ".this_class",	\
					     p,                         \
					     p->this_class,		\
					     JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class, \
					     JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_THIS_CLASS, \
					     _JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK \
                                             );                         \
    }									\
  } while (0)

/* In case of a the Class mode, searching if the direct superclass nor any of its superclasses may have the ACC_FINAL flag */
/* is NOT done because this module is intended for transpiling to any language: Java for instance will not allow recursive */
/* classes. But perl will not allow that. Just an example. */

/* =================================================================== */
/* super_class validation                                              */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validate_interface_modeb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".super_class", "..... Interface mode"); \
    _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(_##scope,                    \
                                           contexts ".super_class",     \
                                           p,                           \
                                           p->super_class,              \
                                           JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class, \
                                           JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_SUPER_CLASS, \
                                           {                            \
                                             __JAVA_CLASSFILE_PARSER_TRACEF(__##scope, contexts ".super_class", "points to a Class_info that have name_index = %u", __##scope##cp_infop->u.classInfop->name_index); \
                                             _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(__##scope, \
                                                                                    contexts ".super_class", \
                                                                                    p, \
                                                                                    __##scope##cp_infop->u.classInfop->name_index, \
                                                                                    JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8, \
                                                                                    JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_SUPER_CLASS, \
                                                                                    { \
                                                                                      java_classfile_parser_CONSTANT_Utf8_info_t *___##scope##utf8Infop = ___##scope##cp_infop->u.utf8Infop; \
                                                                                       \
                                                                                      __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".super_class", "Current JavaUtf8 bytes at constant poolpp[super_class's name_index]", ___##scope##utf8Infop->bytesp, ___##scope##utf8Infop->length); \
                                                                                      __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".super_class", "Wanted JavaUtf8 bytes", UTF8_BYTES_java_lang_Object, UTF8_LENGTH_java_lang_Object); \
                                                                                      if ((___##scope##utf8Infop->length != UTF8_LENGTH_java_lang_Object) || (memcmp(___##scope##utf8Infop->bytesp, UTF8_BYTES_java_lang_Object, UTF8_LENGTH_java_lang_Object) != 0)) { \
                                                                                        errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_SUPER_CLASS; \
                                                                                        return 0; \
                                                                                      } \
                                                                                    } \
                                                                                    ); \
                                           }                            \
                                           );                           \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validate_class_modeb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".super_class", "..... Class mode"); \
    if (p->super_class != 0) {                                          \
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(_##scope,                  \
                                             contexts ".super_class",   \
                                             p,                         \
                                             p->super_class,            \
                                             JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class, \
                                             JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_SUPER_CLASS, \
                                             _JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK \
                                             );                         \
    } else {                                                            \
      _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(_##scope,                  \
                                             contexts ".super_class",   \
                                             p,                         \
                                             p->this_class,             \
                                             JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class, \
                                             JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_THIS_CLASS, \
                                             {                          \
                                               __JAVA_CLASSFILE_PARSER_TRACEF(__##scope, contexts ".this_class", "points to a CONSTANT_Class_info that have name_index = %u", __##scope##cp_infop->u.classInfop->name_index); \
                                               _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(__##scope, \
                                                                                      contexts ".super_class", \
                                                                                      p, \
                                                                                      __##scope##cp_infop->u.classInfop->name_index, \
                                                                                      JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8, \
                                                                                      JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_THIS_CLASS, \
                                                                                      { \
                                                                                        java_classfile_parser_CONSTANT_Utf8_info_t *___##scope##utf8Infop = ___##scope##cp_infop->u.utf8Infop; \
                                                                                         \
                                                                                        __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".super_class", "Current JavaUtf8 bytes at constant poolpp[this_class's name_index]", ___##scope##utf8Infop->bytesp, ___##scope##utf8Infop->length); \
                                                                                        __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(___##scope, contexts ".super_class", "Wanted JavaUtf8 bytes", UTF8_BYTES_java_lang_Object, UTF8_LENGTH_java_lang_Object); \
                                                                                        if ((___##scope##utf8Infop->length != UTF8_LENGTH_java_lang_Object) || (memcmp(___##scope##utf8Infop->bytesp, UTF8_BYTES_java_lang_Object, UTF8_LENGTH_java_lang_Object) != 0)) { \
                                                                                          errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_THIS_CLASS; \
                                                                                          return 0; \
                                                                                        } \
                                                                                      } \
                                                                                      ); \
                                             }                          \
                                             );                         \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".super_class", "start with super_class = %u", (unsigned int) p->super_class); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".super_class", ".......... super_class is 0 ?"); \
      if (p->super_class != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_SUPER_CLASS; \
	return 0;							\
      }									\
    } else {                                                            \
      if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_INTERFACE) { \
        _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validate_interface_modeb(scope, contexts, superclassfilep, p); \
      } else                                                            \
        _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validate_class_modeb(scope, contexts, superclassfilep, p); \
    }									\
  } while (0)

/* =================================================================== */
/* interfaces validation                                               */
/* =================================================================== */

/* Each value in the interfaces array must be a valid index into the constant_pool table. */
/* The constant_pool entry at each value of interfaces[i], where 0 ≤ i < interfaces_count */
/* must be a CONSTANT_Class_info structure. */
#define _JAVA_CLASSFILE_PARSER_ClassFile_interfaces_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".interfaces", "start with interfaces_count = %u, interfacesp = %p", (unsigned int) p->interfaces_count, p->interfacesp); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".interfaces", ".......... interfaces_count is 0 ?"); \
      if (p->interfaces_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_INTERFACES_COUNT; \
	return 0;							\
      }									\
    } else {                                                            \
      java_classfile_parser_u2_t _##scope##i;                           \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Non-module mode"); \
      for (_##scope##i = 0; _##scope##i < p->interfaces_count; _##scope##i++) { \
        _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(                         \
                                               _##scope,                \
                                               contexts ".interfaces",  \
                                               p,                       \
                                               p->interfacesp[_##scope##i], \
                                               JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class, \
                                               JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_INTERFACE, \
                                               _JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK \
                                                                        ); \
      }                                                                 \
    }                                                                   \
  } while (0)

/* =================================================================== */
/* fields validation                                                   */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_fields_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".fields", "start with fields_count = %u, fieldspp = %p", (unsigned int) p->fields_count, p->fieldspp); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".fields", ".......... fields_count is 0 ?"); \
      if (p->fields_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FIELDS_COUNT; \
	return 0;							\
      }									\
    } else {                                                            \
      java_classfile_parser_u2_t _##scope##i;                           \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Non-module mode"); \
      for (_##scope##i = 0; _##scope##i < p->fields_count; _##scope##i++) { \
        if (! java_classfile_parser_field_info_validateb(p, p->fieldspp[_##scope##i])) { \
          return 0;                                                     \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

/* =================================================================== */
/* methods validation                                                   */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_methods_validateb(scope, contexts, superclassfilep, p) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".methods", "start with methods_count = %u, methodspp = %p", (unsigned int) p->methods_count, p->methodspp); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".methods", ".......... methods_count is 0 ?"); \
      if (p->methods_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_METHODS_COUNT; \
	return 0;							\
      }									\
    } else {                                                            \
      java_classfile_parser_u2_t _##scope##i;                           \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Non-module mode"); \
      for (_##scope##i = 0; _##scope##i < p->methods_count; _##scope##i++) { \
        if (! java_classfile_parser_method_info_validateb(p, p->methodspp[_##scope##i])) { \
          return 0;                                                     \
        }                                                               \
      }                                                                 \
    }                                                                   \
  } while (0)

/* =================================================================== */
/* attributes validation                                                   */
/* =================================================================== */

#define _JAVA_CLASSFILE_PARSER_ClassFile_attributes_validateb(scope, contexts, superclassfilep, p) do { \
      java_classfile_parser_u2_t _##scope##i;                           \
                                                                        \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, contexts ".attributes", "start with attributes_count = %u, attributespp = %p", (unsigned int) p->attributes_count, p->attributespp); \
    if ((p->access_flags & JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) == JAVA_CLASSFILE_PARSER_CLASSFILE_ACC_MODULE) { \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".this_class", "..... Module mode"); \
      __JAVA_CLASSFILE_PARSER_TRACE(_##scope, contexts ".attributes", ".......... attributes_count is 1 ?"); \
      if (p->attributes_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTES_COUNT; \
	return 0;							\
      }									\
    }                                                                   \
    for (_##scope##i = 0; _##scope##i < p->attributes_count; _##scope##i++) { \
      if (! java_classfile_parser_attribute_info_validateb(p, p->attributespp[_##scope##i])) { \
        return 0;                                                       \
      }                                                                 \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_validateb(scope, superclassfilep, p) do {  \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, "ClassFile", "start with , superclassfilep = %p, p = %p", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_access_flags_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_this_class_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_super_class_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_interfaces_validateb(_##scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_fields_validateb(scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_methods_validateb(scope, "ClassFile", superclassfilep, p); \
    _JAVA_CLASSFILE_PARSER_ClassFile_attributes_validateb(scope, "ClassFile", superclassfilep, p); \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H */
