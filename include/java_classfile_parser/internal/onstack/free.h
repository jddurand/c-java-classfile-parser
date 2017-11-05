#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FREE_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FREE_H

#define __JAVA_CLASSFILE_PARSER_ONSTACK_FREEV(scope, type, onstack) do { \
    java_classfile_parser_##type##_t *_##scope##tofreep = &(onstack);   \
    __JAVA_CLASSFILE_PARSER_##type##_freev(_##scope, _##scope##tofreep); \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_ONSTACK_FREE_H */
