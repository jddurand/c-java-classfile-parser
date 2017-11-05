#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_GENERATOR_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_GENERATOR_H

/* ======================================================================== */
/* EXPORTED FUNCTIONS                                                       */
/* ======================================================================== */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION_EXPORTED(type)                \
  java_classfile_parser_##type##_t *java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    char *dummyp;                                                       \
    size_t dummyl;                                                      \
    return _java_classfile_parser_##type##_newp(bufferp, lengthl, bufferpp != NULL ? bufferpp : &dummyp, lengthlp != NULL ? lengthlp : &dummyl); \
  }                                                                     \
                                                                        \
  void java_classfile_parser_##type##_freev(java_classfile_parser_##type##_t *p) \
  {                                                                     \
    _java_classfile_parser_##type##_freev(p);                           \
  }

/* ======================================================================== */
/* EXPORTED FUNCTIONS PROXIES                                               */
/* ======================================================================== */
/* - "newp" functions that are endianness aware, and their non-endianness aware version */
/* - "freev" function */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION_PROXY(type)                   \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_BE_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    _JAVA_CLASSFILE_PARSER_##type(, BE, type, bufferp, lengthl);        \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_LE_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    _JAVA_CLASSFILE_PARSER_##type(, LE, type, bufferp, lengthl);        \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static java_classfile_parser_##type##_t *_java_classfile_parser_##type##_newp(char *bufferp, size_t lengthl, char **bufferpp, size_t *lengthlp) \
  {                                                                     \
    java_classfile_parser_##type##_t  type;                             \
    java_classfile_parser_##type##_t *p;                                \
                                                                        \
    if (_JAVA_CLASSFILE_PARSER_SYSTEM_IS_BIGENDIAN()) {                 \
      _JAVA_CLASSFILE_PARSER_##type(, BE, type, bufferp, lengthl);      \
    } else {                                                            \
      _JAVA_CLASSFILE_PARSER_##type(, LE, type, bufferp, lengthl);      \
    }                                                                   \
                                                                        \
    p = (java_classfile_parser_##type##_t *) malloc(sizeof(java_classfile_parser_##type##_t)); \
    if (p == NULL) {                                                    \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    memcpy(p, &type, sizeof(java_classfile_parser_##type##_t));         \
    *bufferpp = bufferp;                                                \
    *lengthlp = lengthl;                                                \
    return p;                                                           \
  }                                                                     \
                                                                        \
  static void _java_classfile_parser_##type##_freev(java_classfile_parser_##type##_t *p) \
  {                                                                     \
    _JAVA_CLASSFILE_PARSER_##type##_freev(, p);                         \
  }

/* ======================================================================== */
/* FUNCTIONS GENERATOR                                                      */
/* ======================================================================== */
#define _JAVA_CLASSFILE_GENERATE_FUNCTION(type)                 \
  _JAVA_CLASSFILE_GENERATE_FUNCTION_PROXY(type)                 \
  _JAVA_CLASSFILE_GENERATE_FUNCTION_EXPORTED(type)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_GENERATOR_H */
