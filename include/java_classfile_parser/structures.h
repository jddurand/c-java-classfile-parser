#ifndef JAVA_CLASSFILE_PARSER_STRUCTURES_H
#define JAVA_CLASSFILE_PARSER_STRUCTURES_H

#include <java_classfile_parser/ux.h>

typedef struct java_classfile_parser_ClassFile                                 java_classfile_parser_ClassFile_t;
typedef struct java_classfile_parser_cp_info                                   java_classfile_parser_cp_info_t;
typedef struct java_classfile_parser_field_info                                java_classfile_parser_field_info_t;
typedef struct java_classfile_parser_method_info                               java_classfile_parser_method_info_t;
typedef struct java_classfile_parser_attribute_info                            java_classfile_parser_attribute_info_t;
typedef struct java_classfile_parser_CONSTANT_Class_info                       java_classfile_parser_CONSTANT_Class_info_t;
typedef struct java_classfile_parser_CONSTANT_Fieldref_info                    java_classfile_parser_CONSTANT_Fieldref_info_t;
typedef struct java_classfile_parser_CONSTANT_Methodref_info                   java_classfile_parser_CONSTANT_Methodref_info_t;
typedef struct java_classfile_parser_CONSTANT_InterfaceMethodref_info          java_classfile_parser_CONSTANT_InterfaceMethodref_info_t;
typedef struct java_classfile_parser_CONSTANT_String_info                      java_classfile_parser_CONSTANT_String_info_t;
typedef struct java_classfile_parser_CONSTANT_Integer_info                     java_classfile_parser_CONSTANT_Integer_info_t;
typedef struct java_classfile_parser_CONSTANT_Float_info                       java_classfile_parser_CONSTANT_Float_info_t;
typedef struct java_classfile_parser_CONSTANT_Long_info                        java_classfile_parser_CONSTANT_Long_info_t;
typedef struct java_classfile_parser_CONSTANT_Double_info                      java_classfile_parser_CONSTANT_Double_info_t;
typedef struct java_classfile_parser_CONSTANT_NameAndType_info                 java_classfile_parser_CONSTANT_NameAndType_info_t;
typedef struct java_classfile_parser_CONSTANT_Utf8_info                        java_classfile_parser_CONSTANT_Utf8_info_t;
typedef struct java_classfile_parser_CONSTANT_MethodHandle_info                java_classfile_parser_CONSTANT_MethodHandle_info_t;
typedef struct java_classfile_parser_CONSTANT_MethodType_info                  java_classfile_parser_CONSTANT_MethodType_info_t;
typedef struct java_classfile_parser_CONSTANT_InvokeDynamic_info               java_classfile_parser_CONSTANT_InvokeDynamic_info_t;
typedef struct java_classfile_parser_CONSTANT_Module_info                      java_classfile_parser_CONSTANT_Module_info_t;
typedef struct java_classfile_parser_CONSTANT_Package_info                     java_classfile_parser_CONSTANT_Package_info_t;
typedef struct java_classfile_parser_Unknown_attribute                         java_classfile_parser_Unknown_attribute_t;
typedef struct java_classfile_parser_ConstantValue_attribute                   java_classfile_parser_ConstantValue_attribute_t;
typedef struct java_classfile_parser_Code_attribute                            java_classfile_parser_Code_attribute_t;
typedef struct java_classfile_parser_Exception                                 java_classfile_parser_Exception_t;
typedef struct java_classfile_parser_Top_variable_info                         java_classfile_parser_Top_variable_info_t;
typedef struct java_classfile_parser_Integer_variable_info                     java_classfile_parser_Integer_variable_info_t;
typedef struct java_classfile_parser_Float_variable_info                       java_classfile_parser_Float_variable_info_t;
typedef struct java_classfile_parser_Null_variable_info                        java_classfile_parser_Null_variable_info_t;
typedef struct java_classfile_parser_UninitializedThis_variable_info           java_classfile_parser_UninitializedThis_variable_info_t;
typedef struct java_classfile_parser_Object_variable_info                      java_classfile_parser_Object_variable_info_t;
typedef struct java_classfile_parser_Uninitialized_variable_info               java_classfile_parser_Uninitialized_variable_info_t;
typedef struct java_classfile_parser_Long_variable_info                        java_classfile_parser_Long_variable_info_t;
typedef struct java_classfile_parser_Double_variable_info                      java_classfile_parser_Double_variable_info_t;
typedef struct java_classfile_parser_verification_type_info                    java_classfile_parser_verification_type_info_t;
typedef struct java_classfile_parser_same_frame                                java_classfile_parser_same_frame_t;
typedef struct java_classfile_parser_same_locals_1_stack_item_frame            java_classfile_parser_same_locals_1_stack_item_frame_t;
typedef struct java_classfile_parser_same_locals_1_stack_item_frame_extended   java_classfile_parser_same_locals_1_stack_item_frame_extended_t;
typedef struct java_classfile_parser_chop_frame                                java_classfile_parser_chop_frame_t;
typedef struct java_classfile_parser_same_frame_extended                       java_classfile_parser_same_frame_extended_t;
typedef struct java_classfile_parser_append_frame                              java_classfile_parser_append_frame_t;
typedef struct java_classfile_parser_full_frame                                java_classfile_parser_full_frame_t;
typedef struct java_classfile_parser_stack_map_frame                           java_classfile_parser_stack_map_frame_t;
typedef struct java_classfile_parser_StackMapTable_attribute                   java_classfile_parser_StackMapTable_attribute_t;

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
  java_classfile_parser_ClassFile_t       *classfilep; /* Pointer to main classfile */
};

struct java_classfile_parser_method_info {
  java_classfile_parser_u2_t               access_flags;
  java_classfile_parser_u2_t               name_index;
  java_classfile_parser_u2_t               descriptor_index;
  java_classfile_parser_u2_t               attributes_count;
  java_classfile_parser_attribute_info_t **attributespp;
  java_classfile_parser_ClassFile_t       *classfilep; /* Pointer to main classfile */
};

/* Attributes sub-structures must be defined before attribute_info */
/* It is only at validation phase that an attribute may move to a known type */

struct java_classfile_parser_Unknown_attribute {
  java_classfile_parser_u1_t *infop;
};

struct java_classfile_parser_ConstantValue_attribute {
  java_classfile_parser_u2_t constantvalue_index;
};

struct java_classfile_parser_Exception {
  java_classfile_parser_u2_t start_pc;
  java_classfile_parser_u2_t end_pc;
  java_classfile_parser_u2_t handler_pc;
  java_classfile_parser_u2_t catch_type;
};

struct java_classfile_parser_Code_attribute {
  java_classfile_parser_u2_t              attribute_name_index;
  java_classfile_parser_u4_t              attribute_length;
  java_classfile_parser_u2_t              max_stack;
  java_classfile_parser_u2_t              max_locals;
  java_classfile_parser_u4_t              code_length;
  java_classfile_parser_u1_t             *codep;
  java_classfile_parser_u2_t              exception_table_length;
  java_classfile_parser_Exception_t      *exception_tablep;
  java_classfile_parser_u2_t              attributes_count;
  java_classfile_parser_attribute_info_t *attributesp;
};

struct java_classfile_parser_Top_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Top = 0 */
};

struct java_classfile_parser_Integer_variable_info {
  java_classfile_parser_u1_t tag; /*ITEM_Integer = 1 */
};

struct java_classfile_parser_Float_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Float = 2 */
};

struct java_classfile_parser_Null_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Null = 5 */
};

struct java_classfile_parser_UninitializedThis_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_UninitializedThis = 6 */
};

struct java_classfile_parser_Object_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Object = 7 */
  java_classfile_parser_u2_t cpool_index;
};

struct java_classfile_parser_Uninitialized_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Uninitialized = 8 */
  java_classfile_parser_u2_t offset;
};

struct java_classfile_parser_Long_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Long = 4 */
};

struct java_classfile_parser_Double_variable_info {
  java_classfile_parser_u1_t tag; /* ITEM_Double = 3 */
};

struct java_classfile_parser_verification_type_info {
  java_classfile_parser_u1_t                                tag;
  union {
    java_classfile_parser_Top_variable_info_t               top_variable;
    java_classfile_parser_Integer_variable_info_t           integer_variable;
    java_classfile_parser_Float_variable_info_t             float_variable;
    java_classfile_parser_Long_variable_info_t              long_variable;
    java_classfile_parser_Double_variable_info_t            double_variable;
    java_classfile_parser_Null_variable_info_t              null_variable;
    java_classfile_parser_UninitializedThis_variable_info_t this_variable;
    java_classfile_parser_Object_variable_info_t            object_variable;
    java_classfile_parser_Uninitialized_variable_info_t     uninitialized_variable;
  } u;
};

struct java_classfile_parser_same_frame {
  java_classfile_parser_u1_t frame_type; /* SAME = [0-63] */
};

struct java_classfile_parser_same_locals_1_stack_item_frame {
  java_classfile_parser_u1_t                     frame_type; /* SAME_LOCALS_1_STACK_ITEM = [64-127] */
  java_classfile_parser_verification_type_info_t stack[1];
};

struct java_classfile_parser_same_locals_1_stack_item_frame_extended {
  java_classfile_parser_u1_t                     frame_type; /* SAME_LOCALS_1_STACK_ITEM_EXTENDED = 247 */
  java_classfile_parser_u2_t                     offset_delta;
  java_classfile_parser_verification_type_info_t stack[1];
};

struct java_classfile_parser_chop_frame {
  java_classfile_parser_u1_t frame_type; /* CHOP = [248-250] */
  java_classfile_parser_u2_t offset_delta;
};

struct java_classfile_parser_same_frame_extended {
  java_classfile_parser_u1_t frame_type; /* SAME_FRAME_EXTENDED = 251 */
  java_classfile_parser_u2_t offset_delta;
};

struct java_classfile_parser_append_frame {
  java_classfile_parser_u1_t                      frame_type; /* APPEND = [252-254] */
  java_classfile_parser_u2_t                      offset_delta;
  java_classfile_parser_verification_type_info_t *localsp; /* frame_type - 251 elements */
};

struct java_classfile_parser_full_frame {
  java_classfile_parser_u1_t                      frame_type; /* FULL_FRAME = 255 */
  java_classfile_parser_u2_t                      offset_delta;
  java_classfile_parser_u2_t                      number_of_locals;
  java_classfile_parser_verification_type_info_t *localsp; /* number_of_locals elements */
  java_classfile_parser_u2_t                      number_of_stack_items;
  java_classfile_parser_verification_type_info_t *stackp; /* number_of_stack_items elements */
};

struct java_classfile_parser_stack_map_frame {
  java_classfile_parser_u1_t                                        frame_type;
  union {
    java_classfile_parser_same_frame_t                              same_frame;
    java_classfile_parser_same_locals_1_stack_item_frame_t          same_locals_1_stack_item_frame;
    java_classfile_parser_same_locals_1_stack_item_frame_extended_t same_locals_1_stack_item_frame_extended;
    java_classfile_parser_chop_frame_t                              chop_frame;
    java_classfile_parser_same_frame_extended_t                     same_frame_extended;
    java_classfile_parser_append_frame_t                            append_frame;
    java_classfile_parser_full_frame_t                              full_frame;
  } u;
};

struct java_classfile_parser_StackMapTable_attribute {
  java_classfile_parser_u2_t               attribute_name_index;
  java_classfile_parser_u4_t               attribute_length;
  java_classfile_parser_u2_t               number_of_entries;
  java_classfile_parser_stack_map_frame_t *entriesp;
};

struct java_classfile_parser_attribute_info {
  java_classfile_parser_u2_t                         attribute_name_index;
  java_classfile_parser_u4_t                         attribute_length;
  java_classfile_parser_u1_t                        *infop;
  java_classfile_parser_attribute_info_e             type;
  union {
    java_classfile_parser_Unknown_attribute_t        unknown;
    java_classfile_parser_ConstantValue_attribute_t  constantValue;
    java_classfile_parser_Code_attribute_t           code;
  } u;
  java_classfile_parser_ClassFile_t                 *classfilep; /* Pointer to main classfile */
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
