#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H

#define _JAVA_CLASSFILE_PARSER_UTIL_EMPTY_BLOCK
#define _JAVA_CLASSFILE_PARSER_UTIL_ANY_TYPE -1

#define _JAVA_CLASSFILE_PARSER_UTIL_IS_CP_INFO(scope, context, classfilep, index, type, errno_invalid_index, block_with_cp_infop) do { \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, context, "constant_pool lookup with index = %d, type = %d", (int) index, (int) type); \
    __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, context, "..... 1 <= %d <= %u ?", (int) index, (unsigned int) classfilep->constant_pool_count); \
    if ((index < 1) || (index > classfilep->constant_pool_count)) {     \
      errno = errno_invalid_index;                                      \
      return 0;                                                         \
    } else {								\
      java_classfile_parser_cp_info_t *_##scope##cp_infop = classfilep->constant_poolpp[index];	\
      __JAVA_CLASSFILE_PARSER_TRACEF(_##scope, context, "..... constant_poolpp[%u] != NULL ?", (int) index); \
      if (_##scope##cp_infop == NULL) {					\
	errno = errno_invalid_index;					\
	return 0;							\
      }									\
      if (type >= 0) {							\
	__JAVA_CLASSFILE_PARSER_TRACEF(_##scope, context, "..... constant_poolpp[%u]->tag == %d ?", (int) index, (int) type); \
	if (_##scope##cp_infop->tag != type) {				\
	  errno = errno_invalid_index;					\
	  return 0;							\
	}								\
      }									\
      block_with_cp_infop						\
    }								        \
  } while (0)

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_UTIL_H */
