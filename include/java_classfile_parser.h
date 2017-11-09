#ifndef JAVA_CLASSFILE_PARSER_H
#define JAVA_CLASSFILE_PARSER_H

#include <stddef.h> /* For size_t */
#include <java_classfile_parser/export.h>
#include <java_classfile_parser/structures.h>

typedef enum _java_classfile_parser_cp_info_e {
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class              =  7,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref           =  9,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref          = 10,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref = 11,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String             =  8,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer            =  3,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float              =  4,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long               =  5,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double             =  6,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType        = 12,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8               =  1,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle       = 15,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType         = 16,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic      = 18,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module             = 19,
  JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package            = 20
} java_classfile_parser_cp_info_e;

typedef enum _java_classfile_parser_err_e {
  JAVA_CLASSFILE_PARSER_ERR_EFAULT = -1,
  JAVA_CLASSFILE_PARSER_ERR_INVALID_CP_INFO_TAG = -2
} java_classfile_parser_err_e;

static const char *java_classfile_parser_err[] = {
  "Not enough data",
  "Invalid constant pool tag"
};

#ifdef __cplusplus
extern "C" {
#endif
  /* All functions have the same template */
#define JAVA_CLASSFILE_PARSER_DECL(type)                                \
  java_classfile_parser_EXPORT java_classfile_parser_##type##_t *java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp); \
  java_classfile_parser_EXPORT void                              java_classfile_parser_##type##_freev(java_classfile_parser_##type##_t *p)

  JAVA_CLASSFILE_PARSER_DECL(ClassFile);
  JAVA_CLASSFILE_PARSER_DECL(cp_info);
  JAVA_CLASSFILE_PARSER_DECL(field_info);
  JAVA_CLASSFILE_PARSER_DECL(method_info);
  JAVA_CLASSFILE_PARSER_DECL(attribute_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Class_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Fieldref_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Methodref_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_InterfaceMethodref_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_String_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Integer_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Float_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Long_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Double_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_NameAndType_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Utf8_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_MethodHandle_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_MethodType_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_InvokeDynamic_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Module_info);
  JAVA_CLASSFILE_PARSER_DECL(CONSTANT_Package_info);

#ifdef __cplusplus
}
#endif

#endif /* JAVA_CLASSFILE_PARSER_H */
