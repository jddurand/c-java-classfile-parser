#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ENDIAN_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ENDIAN_H

/* Systems may have predefined macros */
#if defined(__BYTE_ORDER) && defined(__BIG_ENDIAN)
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() (__BYTE_ORDER == __BIG_ENDIAN)
#elif defined(__BIG_ENDIAN__) || defined(_ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__)
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() 1
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#elif defined(__FLOAT_WORD_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() (__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__)
#else
/* C.f. https://www.ibm.com/developerworks/aix/library/au-endianc/ */
static const int _java_classfile_parse_bigendian = 1;
#define _JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN() ( (*(char*)&_java_classfile_parse_bigendian) == 0 )
#endif

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ENDIAN_H */
