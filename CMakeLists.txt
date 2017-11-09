CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0 FATAL_ERROR)
IF (NOT MYPACKAGEBOOTSTRAP_DONE)
  INCLUDE ("3rdparty/github/cmake-utils/cmake/MyPackageBootstrap.cmake")
ENDIF ()

MYPACKAGESTART (java_classfile_parser 1 0 0)

MYPACKAGELIBRARY(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/java_classfile_parser/internal/config.h.in
  ${INCLUDE_OUTPUT_PATH}/java_classfile_parser/internal/config.h
  src/java_classfile_parser.c)

################
# For CHAR_BIT #
################
CHECK_INCLUDE_FILE ("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILE ("arpa/inet.h" HAVE_ARPA_INET_H)
CHECK_INCLUDE_FILE ("netinet/in.h" HAVE_NETINET_IN_H)
CHECK_INCLUDE_FILE ("machine/endian.h" HAVE_MACHINE_ENDIAN_H)
CHECK_INCLUDE_FILE ("sys/endian.h" HAVE_SYS_ENDIAN_H)

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
