#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_NTOHX_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_NTOHX_H

/* These macros are executed only when current binary is low endian */
/* We do NOT use ntohs and al. because there is no guarantee that our sizeof(u2) is 2*sizeof(u1) etc. */
/* Nevertheless we have macros thanks for cmake to know in advance the result. */
/* System's ntohs is very likely to be more performant, using bswap etc. */
/* In optimized mode, ntohs is usually a macro. In debug mode, it may be a function -; */
#if defined(ntohs) && defined(CHAR_BIT) && (CHAR_BIT == 8) && defined(SIZEOF_UNSIGNED_SHORT) && (SIZEOF_UNSIGNED_SHORT == 2)
#define __JAVA_CLASSFILE_PARSER_NTOHS_LE(scope, n) ntohs(n)
#else
#define __JAVA_CLASSFILE_PARSER_NTOHS_LE(scope, n) (((((java_classfile_parser_u2_t)(n) & 0x00FF)) << 8) | \
                                                    ((((java_classfile_parser_u2_t)(n) & 0xFF00)) >> 8))
#endif

#if defined(ntohl) && defined(CHAR_BIT) && (CHAR_BIT == 8) && defined(SIZEOF_UNSIGNED_LONG) && (SIZEOF_UNSIGNED_LONG == 4)
#define __JAVA_CLASSFILE_PARSER_NTOHL_LE(scope, n) ntohl(n)
#else
#define __JAVA_CLASSFILE_PARSER_NTOHL_LE(scope, n) (((((java_classfile_parser_u4_t)(n) & 0x000000FF)) << 24) | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0x0000FF00)) << 8)  | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0x00FF0000)) >> 8)  | \
                                                    ((((java_classfile_parser_u4_t)(n) & 0xFF000000)) >> 24))
#endif

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_NTOHX_H */
