#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H

#define _JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK

#define _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(classfilep, index, type, errno_invalid_index, block_with_cp_infop) do { \
    java_classfile_parser_cp_info_t *cp_infop;				\
                                                                        \
    if ((index < 1) || (index > classfilep->constant_pool_count)) {     \
      errno = errno_invalid_index;                                      \
      return 0;                                                         \
    }									\
    cp_infop = classfilep->constant_poolpp[index];                      \
    if (cp_infop == NULL) {						\
      errno = errno_invalid_index;                                      \
      return 0;                                                         \
    }									\
    if (cp_infop->tag != type) {                                        \
      errno = errno_invalid_index;                                      \
      return 0;                                                         \
    }									\
    block_with_cp_infop                                                 \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H */
