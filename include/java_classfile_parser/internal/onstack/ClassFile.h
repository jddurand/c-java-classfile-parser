#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H

#include "java_classfile_parser/internal/onstack/cp_info.h"
#include "java_classfile_parser/internal/onstack/field_info.h"
#include "java_classfile_parser/internal/onstack/method_info.h"
#include "java_classfile_parser/internal/onstack/attribute_info.h"

#undef ACC_PUBLIC
#undef ACC_FINAL
#undef ACC_SUPER
#undef ACC_INTERFACE
#undef ACC_ABSTRACT
#undef ACC_SYNTHETIC
#undef ACC_ANNOTATION
#undef ACC_ENUM
#undef ACC_MODULE

#define ACC_PUBLIC      0x0001 /* Declared public; may be accessed from outside its package. */
#define ACC_FINAL       0x0010 /* Declared final; no subclasses allowed. */
#define ACC_SUPER       0x0020 /* Treat superclass methods specially when invoked by the invokespecial instruction. */
#define ACC_INTERFACE   0x0200 /* Is an interface, not a class. */
#define ACC_ABSTRACT    0x0400 /* Declared abstract; must not be instantiated. */
#define ACC_SYNTHETIC   0x1000 /* Declared synthetic; not present in the source code. */
#define ACC_ANNOTATION  0x2000 /* Declared as an annotation type. */
#define ACC_ENUM        0x4000 /* Declared as an enum type. */
#define ACC_MODULE      0x8000 /* Is a module, not a class or interface. */

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

#define _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(classfilep, p) do { \
    if (p->magic != 0xCAFEBABE) {                                       \
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_MAGIC;		\
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
      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_UNSUPPORTED;		\
      return 0;                                                         \
    }                                                                   \
  } while (0)
#else
#define _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(classfilep, p) do { \
  } while (0)
#endif

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
     */

#define _JAVA_CLASSFILE_PARSER_ClassFile_access_flags_validateb(classfilep, p) do { \
    java_classfile_parser_cp_info_t *cp_infop;				\
    java_classfile_parser_attribute_info_t *attribute_infop;		\
    static const char *utf8kos[] = {                                    \
      UTF8_BYTES_ConstantValue,						\
      UTF8_BYTES_Code,							\
      UTF8_BYTES_StackMapTable,						\
      UTF8_BYTES_Exceptions,						\
      UTF8_BYTES_InnerClasses,						\
      UTF8_BYTES_EnclosingMethod,					\
      UTF8_BYTES_Synthetic,						\
      UTF8_BYTES_Signature,						\
      UTF8_BYTES_SourceFile,						\
      UTF8_BYTES_SourceDebugExtension,					\
      UTF8_BYTES_LineNumberTable,					\
      UTF8_BYTES_LocalVariableTable,					\
      UTF8_BYTES_LocalVariableTypeTable,				\
      UTF8_BYTES_Deprecated,						\
      UTF8_BYTES_RuntimeVisibleAnnotations,				\
      UTF8_BYTES_RuntimeInvisibleAnnotations,				\
      UTF8_BYTES_RuntimeVisibleParameterAnnotations,			\
      UTF8_BYTES_RuntimeInvisibleParameterAnnotations,			\
      UTF8_BYTES_RuntimeVisibleTypeAnnotations,				\
      UTF8_BYTES_RuntimeInvisibleTypeAnnotations,			\
      UTF8_BYTES_AnnotationDefault,					\
      UTF8_BYTES_BootstrapMethods,					\
      UTF8_BYTES_MethodParameters,					\
      UTF8_BYTES_Module,						\
      UTF8_BYTES_ModulePackages,					\
      UTF8_BYTES_ModuleMainClass					\
    };									\
    static const java_classfile_parser_u2_t utf8kolength[] = {	        \
      UTF8_LENGTH_ConstantValue,					\
      UTF8_LENGTH_Code,							\
      UTF8_LENGTH_StackMapTable,					\
      UTF8_LENGTH_Exceptions,						\
      UTF8_LENGTH_InnerClasses,						\
      UTF8_LENGTH_EnclosingMethod,					\
      UTF8_LENGTH_Synthetic,						\
      UTF8_LENGTH_Signature,						\
      UTF8_LENGTH_SourceFile,						\
      UTF8_LENGTH_SourceDebugExtension,					\
      UTF8_LENGTH_LineNumberTable,					\
      UTF8_LENGTH_LocalVariableTable,					\
      UTF8_LENGTH_LocalVariableTypeTable,				\
      UTF8_LENGTH_Deprecated,						\
      UTF8_LENGTH_RuntimeVisibleAnnotations,				\
      UTF8_LENGTH_RuntimeInvisibleAnnotations,				\
      UTF8_LENGTH_RuntimeVisibleParameterAnnotations,			\
      UTF8_LENGTH_RuntimeInvisibleParameterAnnotations,			\
      UTF8_LENGTH_RuntimeVisibleTypeAnnotations,			\
      UTF8_LENGTH_RuntimeInvisibleTypeAnnotations,			\
      UTF8_LENGTH_AnnotationDefault,					\
      UTF8_LENGTH_BootstrapMethods,					\
      UTF8_LENGTH_MethodParameters,					\
      UTF8_LENGTH_Module,						\
      UTF8_LENGTH_ModulePackages,					\
      UTF8_LENGTH_ModuleMainClass					\
    };									\
    int i;								\
    java_classfile_parser_CONSTANT_Utf8_info_t *utf8_infop = NULL;	\
    java_classfile_parser_u2_t utf8_length;				\
    java_classfile_parser_u1_t *utf8_bytesp;				\
									\
    if ((p->access_flags & ACC_MODULE) == ACC_MODULE) {			\
      									\
      if (p->access_flags != ACC_MODULE) {				\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FLAG;	\
	return 0;							\
      }									\
      									\
      if (p->major_version < 53) {                                      \
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_VERSION; \
	return 0;							\
      }									\
      									\
      if ((p->this_class < 1) || (p->this_class > p->constant_pool_count)) { \
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_THIS_CLASS; \
	return 0;							\
      }									\
      cp_infop = p->constant_poolpp[p->this_class];			\
      if (cp_infop == NULL) {						\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_THIS_CLASS; \
	return 0;							\
      }									\
      if (cp_infop->tag != JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class) { \
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_THIS_CLASS; \
	return 0;							\
      }									\
      									\
      if (p->super_class != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_SUPER_CLASS; \
	return 0;							\
      }									\
      									\
      if (p->interfaces_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_INTERFACES_COUNT; \
	return 0;							\
      }									\
      									\
      if (p->fields_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FIELDS_COUNT; \
	return 0;							\
      }									\
      									\
      if (p->methods_count != 0) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_METHODS_COUNT; \
	return 0;							\
      }									\
      									\
      if (p->attributes_count != 1) {					\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTES_COUNT; \
	return 0;							\
      }									\
      attribute_infop = p->attributespp[0];				\
      if ((attribute_infop->attribute_name_index < 1) || (attribute_infop->attribute_name_index > p->constant_pool_count)) { \
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX; \
	return 0;							\
      }									\
      cp_infop = p->constant_poolpp[attribute_infop->attribute_name_index]; \
      if (cp_infop == NULL) {						\
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX; \
	return 0;							\
      }									\
      if (cp_infop->tag != JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8) { \
	errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX; \
	return 0;							\
      }									\
      utf8_infop = cp_infop->u.utf8Infop;				\
      utf8_length = utf8_infop->length;					\
      utf8_bytesp = utf8_infop->bytesp;					\
      if (utf8_length > 0) {						\
	for (i = 0; i < sizeof(utf8kos) / sizeof(utf8kos[0]); i++) {	\
  	  if (utf8_length == utf8kolength[i]) {				\
	    if (memcmp(utf8_bytesp, utf8kos[i], utf8_length)) {         \
	      errno = JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME; \
	      return 0;							\
            }								\
	  }                                          			\
	}								\
      }									\
      									\
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ClassFile_validateb(classfilep, p) do {  \
    _JAVA_CLASSFILE_PARSER_ClassFile_magic_validateb(classfilep, p);    \
    _JAVA_CLASSFILE_PARSER_ClassFile_version_validateb(classfilep, p);  \
    _JAVA_CLASSFILE_PARSER_ClassFile_access_flags_validateb(classfilep, p); \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CLASSFILE_H */
