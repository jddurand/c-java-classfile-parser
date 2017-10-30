#include "java-classfile-parser/internal/config.h"
#include <java-classfile-parser.h>

int main(int argc, char **argv) {
  int         fd = -1;
  char       *bytep = NULL;
  size_t      bytel;
  char       *remainsp = NULL;
  size_t      remainsl;
  int         rc;
  java_classfile_parser_ClassFile_t *classFilep;
  struct stat buf;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s file.class\n", argv[0]);
    goto err;
  }

  fd = open(argv[1], O_RDONLY);
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
    fprintf(stderr, "malloc(%ud) failure, %s\n", (unsigned long) bytel, strerror(errno));
    goto err;
  }

  if (read(fd, bytep, bytel) != bytel) {
    fprintf(stderr, "read of %ud bytes failure, %s\n", (unsigned long) bytel, strerror(errno));
    goto err;
  }

  classFilep = java_classfile_parser_ClassFile_newp(bytep, bytel, &remainsp, &remainsl);
  if (classFilep == NULL) {
    fprintf(stderr, "%s parsing failure\n", argv[1]);
    goto err;
  } else {
    fprintf(stderr, "%s parsing success, remains %lu bytes\n", argv[1], (unsigned long) remainsl);
    java_classfile_parser_ClassFile_freev(classFilep);
  }

  rc = 0;
  goto done;

 err:
  rc = 1;

 done:
  if (fd >= 0) {
    if (close(fd) != 0) {
      fprintf(stderr, "%s close failure, %s\n", argv[1], strerror(errno));
    }
  }
  if (bytep != NULL) {
    free(bytep);
  }
  
  return rc;
}
