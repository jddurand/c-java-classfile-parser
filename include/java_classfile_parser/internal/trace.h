#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H

#ifndef JAVA_CLASSFILE_PARSER_NTRACE
# ifdef JAVA_CLASSFILE_PARSER_LOGGER
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(scope, u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %*s%s=%u '%c', remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), " ", #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %s=%u (not printable), remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U1]        0x%02x ->       0x%02x %*s%s=%u, remains %lu", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), " ", #u1, (unsigned int) u1, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U1*]            ->            %*s%s=0%lx, remains %lu", bufferp - u1l, (int) strlen(#scope), " ", #u1p, (unsigned long) u1p, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U2]      0x%04x ->     0x%04x %*s%s=%u, remains %lu", bufferp - 2, (unsigned int) be2, (unsigned int) u22, (int) strlen(#scope), " ", #u2, (unsigned int) u2, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U2*]            ->            %*s%s=0%lx, remains %lu", bufferp - (u2l * 2), (int) strlen(#scope), " ", #u2p, (unsigned long) u2p, (unsigned long) lengthl);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl) JAVA_CLASSFILE_PARSER_LOGGER("%p[U4]  0x%08lx -> 0x%08lx %*s%s=%lu, remains %lu", bufferp - 4, (unsigned long) be4, (unsigned long) u4, (int) strlen(#scope), " ", #u4, (unsigned long) u4, (unsigned long) lengthl);
#  else
#   define __JAVA_CLASSFILE_PARSER_TRACE_CHAR(scope, u1, be1, bufferp, lengthl) ((u1 >= 0x20) && (u1 <= 0x7E)) ? fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %*s%s=%u '%c', remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), " ", #u1, (unsigned int) u1, (unsigned char) u1, (unsigned long) lengthl) : fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %s=%u (not printable), remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl) fprintf(stderr, "%p[U1]        0x%02x ->       0x%02x %*s%s=%u, remains %lu\n", bufferp - 1, (unsigned int) be1, (unsigned int) u1, (int) strlen(#scope), " ", #u1, (unsigned int) u1, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl) fprintf(stderr, "%p[U1*]            ->            %*s%s=0x%lx, remains %lu\n", bufferp - u1l, (int) strlen(#scope), " ", #u1p, (unsigned long) u1p, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl) fprintf(stderr, "%p[U2]      0x%04x ->     0x%04x %*s%s=%u, remains %lu\n", bufferp - 2, (unsigned int) be2, (unsigned int) u2, (int) strlen(#scope), " ", #u2, (unsigned int) u2, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl) fprintf(stderr, "%p[U2*]            ->            %*s%s=0%lx, remains %lu\n", bufferp - (u2l * 2), (int) strlen(#scope), " ", #u2p, (unsigned long) u2p, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl) fprintf(stderr, "%p[U4]  0x%08lx -> 0x%08lx %*s%s=%lu, remains %lu\n", bufferp - 4, (unsigned long) be4, (unsigned long) u4, (int) strlen(#scope), " ", #u4, (unsigned long) u4, (unsigned long) lengthl); fflush(stderr);
#   define __JAVA_CLASSFILE_PARSER_TRACE(scope, msgs) fprintf(stderr, msgs "\n");
#   define __JAVA_CLASSFILE_PARSER_TRACEF(scope, fmts, ...) fprintf(stderr, fmts "\n", __VA_ARGS__);
#  endif
#else
# define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE(scope, msgs)
# define __JAVA_CLASSFILE_PARSER_TRACEF(scope, fmts, ...)
#endif

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H */
