#include <java_classfile_parser.h>
#include "java_classfile_parser/internal/config.h"

#if _WIN32
#define JAVA_CLASSFILE_PARSER_OPEN _open
#define JAVA_CLASSFILE_PARSER_READ _read
#define JAVA_CLASSFILE_PARSER_CLOSE _close
#else
#define JAVA_CLASSFILE_PARSER_OPEN open
#define JAVA_CLASSFILE_PARSER_READ read
#define JAVA_CLASSFILE_PARSER_CLOSE close
#endif

static java_classfile_parser_ClassFile_t *java_classfile_parser_loader(java_classfile_parser_CONSTANT_Utf8_info_t *utf8Infop);

/****************************************************************************/
int main(int argc, char **argv)
/****************************************************************************/
{
  int                                fd = -1;
  char                              *bytep = NULL;
  size_t                             bytel;
  char                              *remainsp = NULL;
  java_classfile_parser_ClassFile_t *classFilep = NULL;
  size_t                             remainsl;
  int                                rc;
  struct stat                        buf;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s file.class\n", argv[0]);
    goto err;
  }

  fd = JAVA_CLASSFILE_PARSER_OPEN(argv[1], O_RDONLY
#ifdef O_BINARY
				  |O_BINARY
#endif
				  );
  if (fd < 0) {
    fprintf(stderr, "%s open failure, %s\n", argv[1], strerror(errno));
    goto err;
  }

  if (fstat(fd, &buf) != 0) {
    fprintf(stderr, "%s stat failure, %s\n", argv[1], strerror(errno));
    goto err;
  }

  bytel = (size_t) buf.st_size;
  if (bytel == 0) {
    fprintf(stderr, "%s is zero size\n", argv[1]);
    goto err;
  }

  bytep = (char *) malloc(bytel);
  if (bytep == NULL) {
    fprintf(stderr, "malloc(%lu) failure, %s\n", (unsigned long) bytel, strerror(errno));
    goto err;
  }

  if (JAVA_CLASSFILE_PARSER_READ(fd, bytep, bytel) != bytel)
    {
    fprintf(stderr, "read of %lu bytes failure, %s\n", (unsigned long) bytel, strerror(errno));
    goto err;
  }

  classFilep = java_classfile_parser_ClassFile_newp(bytep, bytel, &remainsp, &remainsl);
  if (classFilep == NULL) {
    fprintf(stderr, "%s parsing failure, errno=%d\n", argv[1], errno);
    goto err;
  }
  fprintf(stderr, "%s parsing success, remains %lu bytes\n", argv[1], (unsigned long) remainsl);

  if (! java_classfile_parser_ClassFile_validateb(NULL /* java_classfile_parser_loader */, classFilep)) {
    fprintf(stderr, "%s validation failure, errno=%d\n", argv[1], errno);
    goto err;
  }
  fprintf(stderr, "%s validation success\n", argv[1]);

  rc = 0;
  goto done;

 err:
  rc = 1;

 done:
  if (fd >= 0) {
    if (JAVA_CLASSFILE_PARSER_CLOSE(fd) != 0) {
      fprintf(stderr, "%s close failure, %s\n", argv[1], strerror(errno));
    }
  }
  if (bytep != NULL) {
    free(bytep);
  }
  java_classfile_parser_ClassFile_freev(classFilep); /* This is NULL aware */

  return rc;
}

/****************************************************************************/
static java_classfile_parser_ClassFile_t *java_classfile_parser_loader(java_classfile_parser_CONSTANT_Utf8_info_t *utf8Infop)
/****************************************************************************/
{
  return NULL;
}

