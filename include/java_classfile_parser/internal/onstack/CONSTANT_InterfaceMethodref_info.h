#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTERFACEMETHODREF_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTERFACEMETHODREF_INFO_H

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InterfaceMethodref_info, onstack, endianness, class_index, bufferp, lengthl); \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, CONSTANT_InterfaceMethodref_info, onstack, endianness, name_and_type_index, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(scope, p) do { \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(_##scope, p); \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_validateb(scope, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANT_INTERFACEMETHODREF_INFO_H */
