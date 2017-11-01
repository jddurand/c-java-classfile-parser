CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0 FATAL_ERROR)
IF (NOT MYPACKAGEBOOTSTRAP_DONE)
  INCLUDE ("3rdparty/github/cmake-utils/cmake/MyPackageBootstrap.cmake")
ENDIF ()

MYPACKAGESTART (java_classfile_parser 1 0 0)

MYPACKAGELIBRARY(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
  ${INCLUDE_OUTPUT_PATH}/java_classfile_parser/internal/config.h
  src/java_classfile_parser.c)

################
# Executables  #
################
MYPACKAGEEXECUTABLE(javaClassFileParserExe bin/java_classfile_parser.c)
FOREACH (_target javaClassFileParserExe javaClassFileParserExe_static)
  IF (${_target} STREQUAL "javaClassFileParserExe")
    SET_TARGET_PROPERTIES(${_target} PROPERTIES OUTPUT_NAME javap_classfile_parser)
  ELSE ()
    SET_TARGET_PROPERTIES(${_target} PROPERTIES OUTPUT_NAME javap_classfile_parser_static)
  ENDIF ()
ENDFOREACH ()
