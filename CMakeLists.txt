CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0 FATAL_ERROR)
IF (NOT MYPACKAGEBOOTSTRAP_DONE)
  INCLUDE ("3rdparty/github/cmake-utils/cmake/MyPackageBootstrap.cmake")
ENDIF ()

MYPACKAGESTART (java-classfile-parser 1 0 0)

MYPACKAGELIBRARY(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
  ${INCLUDE_OUTPUT_PATH}/javap/internal/config.h
  src/java-classfile-parser.c)

################
# Dependencies #
################
MYPACKAGEDEPENDENCY (genericLogger "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/github/genericLogger" LIBS)

################
# Executables  #
################
MYPACKAGEEXECUTABLE(javaClassFileParserExe bin/java-classfile-parser.c)
FOREACH (_target javaClassFileParserExe javaClassFileParserExe_static)
  IF (${_target} STREQUAL "javaClassFileParserExe")
    SET_TARGET_PROPERTIES(${_target} PROPERTIES OUTPUT_NAME javap-classfile-parser)
  ELSE ()
    SET_TARGET_PROPERTIES(${_target} PROPERTIES OUTPUT_NAME javap-classfile-parser_static)
  ENDIF ()
ENDFOREACH ()
