#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_METHODHANDLE_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_METHODHANDLE_INFO_H

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(_##scope, CONSTANT_MethodHandle_info, onstack, endianness, reference_kind, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_MethodHandle_info, onstack, endianness, reference_index, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(scope, p) do { \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(_##scope, p); \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_validateb(scope, loaderp, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_METHODHANDLE_INFO_H */
