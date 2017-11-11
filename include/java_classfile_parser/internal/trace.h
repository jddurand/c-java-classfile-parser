#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H

#include <genericLogger.h>

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
#   define __JAVA_CLASSFILE_PARSER_TRACE(scope, contexts, msgs) fprintf(stderr, "%*s%s: %s\n", (int) strlen(#scope), " ", (contexts != NULL) ? contexts : "", msgs);
#   define __JAVA_CLASSFILE_PARSER_TRACEF(scope, contexts, fmts, ...) fprintf(stderr, "%*s%s%s " fmts "\n", (int) strlen(#scope), " ", (contexts != NULL) ? contexts : "", (contexts != NULL) ? ":" : " ", __VA_ARGS__);
#  endif

typedef struct java_classfile_parser_stringGenerator {
  char         *s;      /* Pointer */
  size_t        l;      /* Used size */
  short         okb;    /* Status */
  size_t        allocl; /* Allocated size */
} java_classfile_parser_stringGenerator_t;

#define __JAVA_CLASSFILE_PARSER_CHUNKED_SIZE_UPPER(size, chunk) ((size) < (chunk)) ? (chunk) : ((1 + ((size) / (chunk))) * (chunk))

/*****************************************************************************/
static short _java_classfile_parser_appendOpaqueDataToStringGenerator(java_classfile_parser_stringGenerator_t *stringGeneratorp, char *p, size_t sizel)
/*****************************************************************************/
{
  char              *tmpp;
  short              rcb;
  size_t             allocl;
  size_t             wantedl;

  if (stringGeneratorp->s == NULL) {
    /* Get an allocl that is a multiple of 1024 */
    /* 1023 -> 1024 */
    /* 1024 -> 2048 */
    /* 2047 -> 2048 */
    /* 2048 -> 3072 */
    /* ... */
    /* i.e. this is the upper multiple of 1024 and have space for the NUL byte */
    allocl = __JAVA_CLASSFILE_PARSER_CHUNKED_SIZE_UPPER(sizel, 1024);
    /* Check for turn-around, should never happen */
    if (allocl < sizel) {
      goto err;
    }
    stringGeneratorp->s  = malloc(allocl);
    if (stringGeneratorp->s == NULL) {
      goto err;
    }
    memcpy(stringGeneratorp->s, p, sizel);
    stringGeneratorp->allocl = allocl;
    stringGeneratorp->l      = sizel + 1;  /* NUL byte is set at exit of the routine */
    stringGeneratorp->okb    = 1;
  } else if (stringGeneratorp->okb) {
    wantedl = stringGeneratorp->l + sizel; /* +1 for the NUL is already accounted in stringGeneratorp->l */
    allocl = __JAVA_CLASSFILE_PARSER_CHUNKED_SIZE_UPPER(wantedl, 1024);
    /* Check for turn-around, should never happen */
    if (allocl < wantedl) {
      goto err;
    }
    if (allocl > stringGeneratorp->allocl) {
      tmpp = realloc(stringGeneratorp->s, allocl); /* The +1 for the NULL byte is already in */
      if (tmpp == NULL) {
        goto err;
      }
      stringGeneratorp->s      = tmpp;
      stringGeneratorp->allocl = allocl;
    }
    memcpy(stringGeneratorp->s + stringGeneratorp->l - 1, p, sizel);
    stringGeneratorp->l = wantedl; /* Already contains the +1 fir the NUL byte */
  } else {
    goto err;
  }

  stringGeneratorp->s[stringGeneratorp->l - 1] = '\0';
  rcb = 1;
  goto done;

 err:
  if (stringGeneratorp->s != NULL) {
    free(stringGeneratorp->s);
    stringGeneratorp->s = NULL;
  }
  stringGeneratorp->okb    = 0;
  stringGeneratorp->l      = 0;
  stringGeneratorp->allocl = 0;
  rcb = 0;

 done:
  return rcb;
}

/*****************************************************************************/
static void _java_classfile_parser_generateStringWithLoggerCallback(void *userDatavp, genericLoggerLevel_t logLeveli, const char *msgs)
/*****************************************************************************/
{
  _java_classfile_parser_appendOpaqueDataToStringGenerator((java_classfile_parser_stringGenerator_t *) userDatavp, (char *) msgs, strlen(msgs));
}

/* C.f. http://grapsus.net/blog/post/Hexadecimal-dump-in-C */
#ifndef __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS
#define __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS 16
#endif
#define __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(scope, contexts, arg_headers, arg_p, arg_lengthl) do { \
    java_classfile_parser_stringGenerator_t  _##scope##stringGenerator; \
    char                                    *_##scope##headers = (char *) (arg_headers); \
    char                                    *_##scope##p = (char *) (arg_p);                   \
    size_t                                   _##scope##lengthl = (size_t) (arg_lengthl); \
    genericLogger_t                         *_##scope##genericLoggerp;  \
    size_t                                   _##scope##i;               \
    size_t                                   _##scope##j;               \
                                                                        \
    _##scope##stringGenerator.s           = NULL;                       \
    _##scope##stringGenerator.l           = 0;                          \
    _##scope##stringGenerator.okb         = 0;                          \
                                                                        \
    _##scope##genericLoggerp = GENERICLOGGER_CUSTOM(_java_classfile_parser_generateStringWithLoggerCallback, (void *) &_##scope##stringGenerator, GENERICLOGGER_LOGLEVEL_TRACE); \
    if (_##scope##genericLoggerp != NULL) {                             \
      __JAVA_CLASSFILE_PARSER_TRACE(scope, contexts, "--------------------------------------------"); \
      __JAVA_CLASSFILE_PARSER_TRACEF(scope, contexts, "%s (%ld bytes)", _##scope##headers, (unsigned long) _##scope##lengthl); \
      for (_##scope##i = 0; _##scope##i < _##scope##lengthl + ((_##scope##lengthl % __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS) ? (__JAVA_CLASSFILE_PARSER_HEXDUMP_COLS - _##scope##lengthl % __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS) : 0); _##scope##i++) { \
        /* print offset */                                              \
        if (_##scope##i % __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS == 0) {  \
          GENERICLOGGER_TRACEF(_##scope##genericLoggerp, "0x%06x: ", _##scope##i); \
        }                                                               \
        /* print hex data */                                            \
        if (_##scope##i < _##scope##lengthl) {                          \
          GENERICLOGGER_TRACEF(_##scope##genericLoggerp, "%02x ", 0xFF & _##scope##p[_##scope##i]); \
        } else { /* end of block, just aligning for ASCII dump */       \
          GENERICLOGGER_TRACE(_##scope##genericLoggerp, "   ");         \
        }                                                               \
        /* print ASCII dump */                                          \
        if (_##scope##i % __JAVA_CLASSFILE_PARSER_HEXDUMP_COLS == (__JAVA_CLASSFILE_PARSER_HEXDUMP_COLS - 1)) { \
          for (_##scope##j = _##scope##i - (__JAVA_CLASSFILE_PARSER_HEXDUMP_COLS - 1); _##scope##j <= _##scope##i; _##scope##j++) { \
            if (_##scope##j >= _##scope##lengthl) { /* end of block, not really printing */ \
              GENERICLOGGER_TRACE(_##scope##genericLoggerp, " ");       \
            }                                                           \
            else if (isprint(0xFF & _##scope##p[_##scope##j])) { /* printable char */ \
              GENERICLOGGER_TRACEF(_##scope##genericLoggerp, "%c", 0xFF & _##scope##p[_##scope##j]); \
            }                                                           \
            else { /* other char */                                     \
              GENERICLOGGER_TRACE(_##scope##genericLoggerp, ".");       \
            }                                                           \
          }                                                             \
          if (_##scope##stringGenerator.okb) {                          \
            __JAVA_CLASSFILE_PARSER_TRACE(scope, contexts, _##scope##stringGenerator.s); \
            free(_##scope##stringGenerator.s);                          \
            _##scope##stringGenerator.s = NULL;                         \
            _##scope##stringGenerator.okb = 0;                          \
          }                                                             \
        }                                                               \
      }                                                                 \
      __JAVA_CLASSFILE_PARSER_TRACE(scope, contexts, "--------------------------------------------"); \
      GENERICLOGGER_FREE(_##scope##genericLoggerp);                     \
    }                                                                   \
  } while (0)

#else /* JAVA_CLASSFILE_PARSER_NTRACE */
# define __JAVA_CLASSFILE_PARSER_TRACE_U1(scope, u1, be1, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U1_ARRAY(scope, u1p, u1l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2(scope, u2, be2, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U2_ARRAY(scope, u2p, u2l, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE_U4(scope, u4, be4, bufferp, lengthl)
# define __JAVA_CLASSFILE_PARSER_TRACE(scope, contexts, msgs)
# define __JAVA_CLASSFILE_PARSER_TRACEF(scope, contexts, fmts, ...)
# define __JAVA_CLASSFILE_PARSER_TRACE_HEXDUMP(scope, contexts, headers, p, lengthl)
#endif

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_TRACE_H */
