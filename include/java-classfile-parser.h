#ifndef JAVA_CLASSFILE_PARSER_H
#define JAVA_CLASSFILE_PARSER_H

#include <stddef.h> /* For size_t */
#include <java-classfile-parser/export.h>
#include <java-classfile-parser/structures.h>

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
  JAVA_CLASSFILE_PARSER_ERR_EFAULT = -1
} java_classfile_parser_err_e;

#ifdef __cplusplus
extern "C" {
#endif
  java_classfile_parser_EXPORT java_classfile_parser_ClassFile_t                        *java_classfile_parser_ClassFile_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_ClassFile_freev(java_classfile_parser_ClassFile_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_cp_info_t                          *java_classfile_parser_cp_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_cp_info_freev(java_classfile_parser_cp_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Class_info_t              *java_classfile_parser_CONSTANT_Class_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Class_info_freev(java_classfile_parser_CONSTANT_Class_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Fieldref_info_t           *java_classfile_parser_CONSTANT_Fieldref_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Fieldref_info_freev(java_classfile_parser_CONSTANT_Fieldref_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Methodref_info_t          *java_classfile_parser_CONSTANT_Methodref_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Methodref_info_freev(java_classfile_parser_CONSTANT_Methodref_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_InterfaceMethodref_info_t *java_classfile_parser_CONSTANT_InterfaceMethodref_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_InterfaceMethodref_info_freev(java_classfile_parser_CONSTANT_InterfaceMethodref_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_String_info_t             *java_classfile_parser_CONSTANT_String_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_String_info_freev(java_classfile_parser_CONSTANT_String_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Integer_info_t            *java_classfile_parser_CONSTANT_Integer_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Integer_info_freev(java_classfile_parser_CONSTANT_Integer_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Float_info_t              *java_classfile_parser_CONSTANT_Float_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Float_info_freev(java_classfile_parser_CONSTANT_Float_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Long_info_t               *java_classfile_parser_CONSTANT_Long_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Long_info_freev(java_classfile_parser_CONSTANT_Long_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Double_info_t             *java_classfile_parser_CONSTANT_Double_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Double_info_freev(java_classfile_parser_CONSTANT_Double_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_NameAndType_info_t        *java_classfile_parser_CONSTANT_NameAndType_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_NameAndType_info_freev(java_classfile_parser_CONSTANT_NameAndType_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Utf8_info_t               *java_classfile_parser_CONSTANT_Utf8_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Utf8_info_freev(java_classfile_parser_CONSTANT_Utf8_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_MethodHandle_info_t       *java_classfile_parser_CONSTANT_MethodHandle_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_MethodHandle_info_freev(java_classfile_parser_CONSTANT_MethodHandle_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_MethodType_info_t         *java_classfile_parser_CONSTANT_MethodType_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_MethodType_info_freev(java_classfile_parser_CONSTANT_MethodType_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_InvokeDynamic_info_t      *java_classfile_parser_CONSTANT_InvokeDynamic_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_InvokeDynamic_info_freev(java_classfile_parser_CONSTANT_InvokeDynamic_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Module_info_t             *java_classfile_parser_CONSTANT_Module_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Module_info_freev(java_classfile_parser_CONSTANT_Module_info_t *p);
  java_classfile_parser_EXPORT java_classfile_parser_CONSTANT_Package_info_t            *java_classfile_parser_CONSTANT_Package_info_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp);
  java_classfile_parser_EXPORT void                                                      java_classfile_parser_CONSTANT_Package_info_freev(java_classfile_parser_CONSTANT_Package_info_t *p);

#ifdef __cplusplus
}
#endif

#endif /* JAVA_CLASSFILE_PARSER_H */
