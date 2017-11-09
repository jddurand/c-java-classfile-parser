#ifndef JAVA_CLASSFILE_PARSER_INTERNAL_DEPENDENCIES_H
#define JAVA_CLASSFILE_PARSER_INTERNAL_DEPENDENCIES_H

/* All dependencies are loaded here */

#include <java_classfile_parser.h>
#include "java_classfile_parser/internal/constants.h"
#include "java_classfile_parser/internal/config.h"
#include "java_classfile_parser/internal/endian.h"
#include "java_classfile_parser/internal/trace.h"
#include "java_classfile_parser/internal/ntohx.h"
#include "java_classfile_parser/internal/onstack/free.h"
#include "java_classfile_parser/internal/onstack/u1.h"
#include "java_classfile_parser/internal/onstack/u1/array.h"
#include "java_classfile_parser/internal/onstack/u2.h"
#include "java_classfile_parser/internal/onstack/u2.h"
#include "java_classfile_parser/internal/onstack/u2/array.h"
#include "java_classfile_parser/internal/onstack/u4.h"
#include "java_classfile_parser/internal/onstack/free.h"

/* From there ALL needed include files are already included: no need for any include anymore */
#include "java_classfile_parser/internal/onstack/ClassFile.h"

#endif /* JAVA_CLASSFILE_PARSER_INTERNAL_DEPENDENCIES_H */
