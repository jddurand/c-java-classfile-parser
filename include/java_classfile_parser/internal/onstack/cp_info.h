#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CP_INFO_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CP_INFO_H

#include "java_classfile_parser/internal/onstack/CONSTANT_Class_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Fieldref_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Methodref_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_InterfaceMethodref_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_String_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Integer_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Float_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Long_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Double_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_NameAndType_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Utf8_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_MethodHandle_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_MethodType_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_InvokeDynamic_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Module_info.h"
#include "java_classfile_parser/internal/onstack/CONSTANT_Package_info.h"

#define _JAVA_CLASSFILE_PARSER_cp_info(scope, endianness, onstack, bufferp, lengthl) do { \
    _JAVA_CLASSFILE_PARSER_U1(_##scope, cp_info, onstack, endianness, tag, bufferp, lengthl); \
    switch (onstack.tag) {                                              \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      onstack.u.classInfop = _java_classfile_parser_CONSTANT_Class_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.classInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      onstack.u.fieldrefInfop = _java_classfile_parser_CONSTANT_Fieldref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.fieldrefInfop == NULL) {                            \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      onstack.u.methodrefInfop = _java_classfile_parser_CONSTANT_Methodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodrefInfop == NULL) {                           \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      onstack.u.interfaceMethodrefInfop = _java_classfile_parser_CONSTANT_InterfaceMethodref_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.interfaceMethodrefInfop == NULL) {                  \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      onstack.u.stringInfop = _java_classfile_parser_CONSTANT_String_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.stringInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      onstack.u.integerInfop = _java_classfile_parser_CONSTANT_Integer_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.integerInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      onstack.u.floatInfop = _java_classfile_parser_CONSTANT_Float_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.floatInfop == NULL) {                               \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      onstack.u.longInfop = _java_classfile_parser_CONSTANT_Long_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.longInfop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      onstack.u.doubleInfop = _java_classfile_parser_CONSTANT_Double_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.doubleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      onstack.u.nameAndTypeInfop = _java_classfile_parser_CONSTANT_NameAndType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.nameAndTypeInfop == NULL) {                         \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      onstack.u.utf8Infop = _java_classfile_parser_CONSTANT_Utf8_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.utf8Infop == NULL) {                                \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      onstack.u.methodHandleInfop = _java_classfile_parser_CONSTANT_MethodHandle_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodHandleInfop == NULL) {                        \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      onstack.u.methodTypeInfop = _java_classfile_parser_CONSTANT_MethodType_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.methodTypeInfop == NULL) {                          \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      onstack.u.invokeDynamicInfop = _java_classfile_parser_CONSTANT_InvokeDynamic_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.invokeDynamicInfop == NULL) {                       \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      onstack.u.moduleInfop = _java_classfile_parser_CONSTANT_Module_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.moduleInfop == NULL) {                              \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      onstack.u.packageInfop = _java_classfile_parser_CONSTANT_Package_info_##endianness##_newp(bufferp, lengthl, &bufferp, &lengthl); \
      if (onstack.u.packageInfop == NULL) {                             \
        __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
        return NULL;                                                    \
      }                                                                 \
      break;                                                            \
    default:                                                            \
      errno = JAVA_CLASSFILE_PARSER_ERR_INVALID_CP_INFO_TAG;            \
      __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(_##scope, cp_info, onstack); \
      return NULL;                                                      \
    }                                                                   \
  } while (0)

#define __JAVA_CLASSFILE_PARSER_cp_info_freev(scope, p) do {            \
    switch (p->tag) {                                                   \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Class:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Class_info_freev(_##scope, p->u.classInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Fieldref:               \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Fieldref_info_freev(_##scope, p->u.fieldrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Methodref:              \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Methodref_info_freev(_##scope, p->u.methodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InterfaceMethodref:     \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InterfaceMethodref_info_freev(_##scope, p->u.interfaceMethodrefInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_String:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_String_info_freev(_##scope, p->u.stringInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Integer:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Integer_info_freev(_##scope, p->u.integerInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Float:                  \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Float_info_freev(_##scope, p->u.floatInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Long:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Long_info_freev(_##scope, p->u.longInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Double:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Double_info_freev(_##scope, p->u.doubleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_NameAndType:            \
      _JAVA_CLASSFILE_PARSER_CONSTANT_NameAndType_info_freev(_##scope, p->u.nameAndTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Utf8:                   \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Utf8_info_freev(_##scope, p->u.utf8Infop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodHandle:           \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodHandle_info_freev(_##scope, p->u.methodHandleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_MethodType:             \
      _JAVA_CLASSFILE_PARSER_CONSTANT_MethodType_info_freev(_##scope, p->u.methodTypeInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_InvokeDynamic:          \
      _JAVA_CLASSFILE_PARSER_CONSTANT_InvokeDynamic_info_freev(_##scope, p->u.invokeDynamicInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Module:                 \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Module_info_freev(_##scope, p->u.moduleInfop); \
      break;                                                            \
    case JAVA_CLASSFILE_PARSER_CP_INFO_CONSTANT_Package:                \
      _JAVA_CLASSFILE_PARSER_CONSTANT_Package_info_freev(_##scope, p->u.packageInfop); \
      break;                                                            \
    default:                                                            \
      break;                                                            \
    }                                                                   \
  } while (0)

#define _JAVA_CLASSFILE_PARSER_cp_info_freev(scope, p) do {             \
    if (p != NULL) {                                                    \
      __JAVA_CLASSFILE_PARSER_cp_info_freev(_##scope, p);               \
      free(p);                                                          \
    }                                                                   \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_CP_INFO_H */
