#ifndef JAVA_CLASSFILE_PARSER_H
#define JAVA_CLASSFILE_PARSER_H

#include <stddef.h> /* For size_t */

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

typedef enum _java_classfile_parser_attribute_info_e {
  JAVA_CLASSFILE_PARSER_ATTRIBUTE_INFO_Unknown              =  0,
  JAVA_CLASSFILE_PARSER_ATTRIBUTE_INFO_ConstantValue        =  1
} java_classfile_parser_attribute_info_e;

typedef enum _java_classfile_parser_err_e {
  JAVA_CLASSFILE_PARSER_ERR_EFAULT                                        = - 1,
  JAVA_CLASSFILE_PARSER_ERR_CP_INFO_TAG                                   = - 2,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_MAGIC                               = - 3,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_UNSUPPORTED                         = - 4,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FLAG                     = - 5,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_VERSION                  = - 6,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_THIS_CLASS               = - 7,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_SUPER_CLASS              = - 8,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_INTERFACES_COUNT         = - 9,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_FIELDS_COUNT             = -10,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_METHODS_COUNT            = -11,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTES_COUNT         = -12,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME_INDEX     = -13,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_MODULE_ATTRIBUTE_NAME           = -14,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_ABSTRACT         = -15,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_FINAL            = -16,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_SUPER            = -17,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_ENUM             = -18,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_INTERFACE_FLAG_MODULE           = -19,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_ANNOTATION           = -20,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_MODULE               = -21,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_FINAL_ABSTRACT       = -22,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_ACC_CLASS_FLAG_ANNOTATION_INTERFACE = -23,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_THIS_CLASS                          = -24,
  JAVA_CLASSFILE_PARSER_ERR_CLASSFILE_SUPER_CLASS                         = -25
} java_classfile_parser_err_e;

static const char *java_classfile_parser_err[] = {
  "Not enough data",
  "Invalid constant pool tag",
  "Invalid ClassFile magic number",
  "Unsupported ClassFile version",
  "ACC_MODULE flag is not alone in ClassFile's access_flags",
  "ACC_MODULE flag is set but ClassFile's major version is < 53",
  "ACC_MODULE flag is set but ClassFile's this_class is invalid",
  "ACC_MODULE flag is set but ClassFile's super_class is invalid",
  "ACC_MODULE flag is set but ClassFile's interfaces_count is invalid",
  "ACC_MODULE flag is set but ClassFile's fields_count is invalid",
  "ACC_MODULE flag is set but ClassFile's methods_count is invalid",
  "ACC_MODULE flag is set but ClassFile's attributes_count is invalid",
  "ACC_MODULE flag is set but ClassFile's attribute's name_index is invalid",
  "ACC_MODULE flag is set but ClassFile's attribute's name is invalid",
  "ACC_INTERFACE flag is set but the ACC_ABSTRACT flag is not set",
  "ACC_INTERFACE flag is set but the ACC_FINAL flag is set",
  "ACC_INTERFACE flag is set but the ACC_SUPER flag is set",
  "ACC_INTERFACE flag is set but the ACC_ENUM flag is set",
  "ACC_INTERFACE flag is set but the ACC_MODULE flag is set",
  "ACC_INTERFACE flag is not set but the ACC_ANNOTATION flag is set",
  "ACC_INTERFACE flag is not set but the ACC_MODULE flag is set",
  "ACC_INTERFACE flag is not set but the ACC_FINAL and ACC_ABSTRACT flags are set",
  "ACC_ANNOTATION flag is set but the ACC_INTERFACE flag is not set",
  "ClassFile's this_class is invalid",
  "ClassFile's super_class is invalid"
};

#include <java_classfile_parser/export.h>
#include <java_classfile_parser/structures.h>

#ifdef __cplusplus
extern "C" {
#endif
  /* All functions have the same template */
#define JAVA_CLASSFILE_PARSER_DECL(type)                                \
  java_classfile_parser_EXPORT java_classfile_parser_##type##_t *java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp); \
  java_classfile_parser_EXPORT short                             java_classfile_parser_##type##_validateb(java_classfile_parser_ClassFile_t *classfilep, java_classfile_parser_##type##_t *p); \
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
  JAVA_CLASSFILE_PARSER_DECL(ConstantValue_attribute);

#ifdef __cplusplus
}
#endif

#endif /* JAVA_CLASSFILE_PARSER_H */
