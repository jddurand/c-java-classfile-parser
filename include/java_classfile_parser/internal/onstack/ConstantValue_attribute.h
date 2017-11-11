#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANTVALUE_ATTRIBUTE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANTVALUE_ATTRIBUTE_H

#define _JAVA_CLASSFILE_PARSER_ConstantValue_attribute(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U2(_##scope, ConstantValue_attribute, onstack, endianness, constantvalue_index, bufferp, lengthl); \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_ConstantValue_attribute_freev(scope, p) do { \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ConstantValue_attribute_freev(scope, p) do { \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_ConstantValue_attribute_freev(_##scope, p);   \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_ConstantValue_attribute_validateb(scope, p) do { \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CONSTANTVALUE_ATTRIBUTE_H */
