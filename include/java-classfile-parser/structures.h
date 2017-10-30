#ifndef JAVA_CLASSFILE_PARSER_STRUCTURES_H
#define JAVA_CLASSFILE_PARSER_STRUCTURES_H

#include <java-classfile-parser/ux.h>

typedef struct java_classfile_parser_ClassFile                        java_classfile_parser_ClassFile_t;
typedef struct java_classfile_parser_cp_info                          java_classfile_parser_cp_info_t;
typedef struct java_classfile_parser_field_info                       java_classfile_parser_field_info_t;
typedef struct java_classfile_parser_method_info                      java_classfile_parser_method_info_t;
typedef struct java_classfile_parser_attribute_info                   java_classfile_parser_attribute_info_t;
typedef struct java_classfile_parser_CONSTANT_Class_info              java_classfile_parser_CONSTANT_Class_info_t;
typedef struct java_classfile_parser_CONSTANT_Fieldref_info           java_classfile_parser_CONSTANT_Fieldref_info_t;
typedef struct java_classfile_parser_CONSTANT_Methodref_info          java_classfile_parser_CONSTANT_Methodref_info_t;
typedef struct java_classfile_parser_CONSTANT_InterfaceMethodref_info java_classfile_parser_CONSTANT_InterfaceMethodref_info_t;
typedef struct java_classfile_parser_CONSTANT_String_info             java_classfile_parser_CONSTANT_String_info_t;
typedef struct java_classfile_parser_CONSTANT_Integer_info            java_classfile_parser_CONSTANT_Integer_info_t;
typedef struct java_classfile_parser_CONSTANT_Float_info              java_classfile_parser_CONSTANT_Float_info_t;
typedef struct java_classfile_parser_CONSTANT_Long_info               java_classfile_parser_CONSTANT_Long_info_t;
typedef struct java_classfile_parser_CONSTANT_Double_info             java_classfile_parser_CONSTANT_Double_info_t;
typedef struct java_classfile_parser_CONSTANT_NameAndType_info        java_classfile_parser_CONSTANT_NameAndType_info_t;
typedef struct java_classfile_parser_CONSTANT_Utf8_info               java_classfile_parser_CONSTANT_Utf8_info_t;
typedef struct java_classfile_parser_CONSTANT_MethodHandle_info       java_classfile_parser_CONSTANT_MethodHandle_info_t;
typedef struct java_classfile_parser_CONSTANT_MethodType_info         java_classfile_parser_CONSTANT_MethodType_info_t;
typedef struct java_classfile_parser_CONSTANT_InvokeDynamic_info      java_classfile_parser_CONSTANT_InvokeDynamic_info_t;
typedef struct java_classfile_parser_CONSTANT_Module_info             java_classfile_parser_CONSTANT_Module_info_t;
typedef struct java_classfile_parser_CONSTANT_Package_info            java_classfile_parser_CONSTANT_Package_info_t;

struct java_classfile_parser_ClassFile {
  java_classfile_parser_u4_t               magic;
  java_classfile_parser_u2_t               minor_version;
  java_classfile_parser_u2_t               major_version;
  java_classfile_parser_u2_t               constant_pool_count;
  java_classfile_parser_cp_info_t        **constant_poolpp;
  java_classfile_parser_u2_t               access_flags;
  java_classfile_parser_u2_t               this_class;
  java_classfile_parser_u2_t               super_class;
  java_classfile_parser_u2_t               interfaces_count;
  java_classfile_parser_u2_t              *interfacesp;
  java_classfile_parser_u2_t               fields_count;
  java_classfile_parser_field_info_t     **fieldspp;
  java_classfile_parser_u2_t               methods_count;
  java_classfile_parser_method_info_t    **methodspp;
  java_classfile_parser_u2_t               attributes_count;
  java_classfile_parser_attribute_info_t **attributespp;
};

struct java_classfile_parser_cp_info {
  java_classfile_parser_u1_t  tag;
  union {
    java_classfile_parser_CONSTANT_Class_info_t              *classInfop;
    java_classfile_parser_CONSTANT_Fieldref_info_t           *fieldrefInfop;
    java_classfile_parser_CONSTANT_Methodref_info_t          *methodrefInfop;
    java_classfile_parser_CONSTANT_InterfaceMethodref_info_t *interfaceMethodrefInfop;
    java_classfile_parser_CONSTANT_String_info_t             *stringInfop;
    java_classfile_parser_CONSTANT_Integer_info_t            *integerInfop;
    java_classfile_parser_CONSTANT_Float_info_t              *floatInfop;
    java_classfile_parser_CONSTANT_Long_info_t               *longInfop;
    java_classfile_parser_CONSTANT_Double_info_t             *doubleInfop;
    java_classfile_parser_CONSTANT_NameAndType_info_t        *nameAndTypeInfop;
    java_classfile_parser_CONSTANT_Utf8_info_t               *utf8Infop;
    java_classfile_parser_CONSTANT_MethodHandle_info_t       *methodHandleInfop;
    java_classfile_parser_CONSTANT_MethodType_info_t         *methodTypeInfop;
    java_classfile_parser_CONSTANT_InvokeDynamic_info_t      *invokeDynamicInfop;
    java_classfile_parser_CONSTANT_Module_info_t             *moduleInfop;
    java_classfile_parser_CONSTANT_Package_info_t            *packageInfop;
  } u;
};

struct java_classfile_parser_field_info {
  java_classfile_parser_u2_t               access_flags;
  java_classfile_parser_u2_t               name_index;
  java_classfile_parser_u2_t               descriptor_index;
  java_classfile_parser_u2_t               attributes_count;
  java_classfile_parser_attribute_info_t **attributespp;
};

struct java_classfile_parser_method_info {
  java_classfile_parser_u2_t               access_flags;
  java_classfile_parser_u2_t               name_index;
  java_classfile_parser_u2_t               descriptor_index;
  java_classfile_parser_u2_t               attributes_count;
  java_classfile_parser_attribute_info_t **attributespp;
};

struct java_classfile_parser_attribute_info {
  java_classfile_parser_u2_t  attribute_name_index;
  java_classfile_parser_u4_t  attribute_length;
  java_classfile_parser_u1_t *infop;
};

struct java_classfile_parser_CONSTANT_Class_info {
  java_classfile_parser_u2_t name_index;
};

struct java_classfile_parser_CONSTANT_Fieldref_info {
  java_classfile_parser_u2_t class_index;
  java_classfile_parser_u2_t name_and_type_index;
};

struct java_classfile_parser_CONSTANT_Methodref_info {
  java_classfile_parser_u2_t class_index;
  java_classfile_parser_u2_t name_and_type_index;
};

struct java_classfile_parser_CONSTANT_InterfaceMethodref_info {
  java_classfile_parser_u2_t class_index;
  java_classfile_parser_u2_t name_and_type_index;
};

struct java_classfile_parser_CONSTANT_String_info {
  java_classfile_parser_u2_t string_index;
};

struct java_classfile_parser_CONSTANT_Integer_info {
  java_classfile_parser_u4_t bytes;
};

struct java_classfile_parser_CONSTANT_Float_info {
  java_classfile_parser_u4_t bytes;
};

struct java_classfile_parser_CONSTANT_Long_info {
  java_classfile_parser_u4_t high_bytes;
  java_classfile_parser_u4_t low_bytes;
};

struct java_classfile_parser_CONSTANT_Double_info {
  java_classfile_parser_u4_t high_bytes;
  java_classfile_parser_u4_t low_bytes;
};

struct java_classfile_parser_CONSTANT_NameAndType_info {
  java_classfile_parser_u2_t name_index;
  java_classfile_parser_u2_t descriptor_index;
};

struct java_classfile_parser_CONSTANT_Utf8_info {
  java_classfile_parser_u2_t  length;
  java_classfile_parser_u1_t *bytesp;
};

struct java_classfile_parser_CONSTANT_MethodHandle_info {
  java_classfile_parser_u1_t reference_kind;
  java_classfile_parser_u2_t reference_index;
};

struct java_classfile_parser_CONSTANT_MethodType_info {
  java_classfile_parser_u2_t descriptor_index;
};

struct java_classfile_parser_CONSTANT_InvokeDynamic_info {
  java_classfile_parser_u2_t bootstrap_method_attr_index;
  java_classfile_parser_u2_t name_and_type_index;
};

struct java_classfile_parser_CONSTANT_Module_info {
  java_classfile_parser_u2_t name_index;
};

struct java_classfile_parser_CONSTANT_Package_info {
  java_classfile_parser_u2_t name_index;
};

#endif /* JAVA_CLASSFILE_PARSER_STRUCTURES_H */
