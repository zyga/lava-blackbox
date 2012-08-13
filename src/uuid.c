#include "uuid.h"

#include <errno.h>
#include <stdio.h>

int
uuid_gen(char *buf) {
   FILE *stream = NULL;
   int retval;
   size_t num_read;

   stream = fopen(UUID_PATHNAME, "rt");
   if (!stream) {
       retval = errno;
       goto out;
   }
   num_read = fread(buf, 1, UUID_ASCII_LEN, stream);
   if (num_read != UUID_ASCII_LEN) {
       retval = errno ? errno : EIO;
       goto out;
   } else {
       buf[UUID_ASCII_LEN] = 0;
       retval = 0;
   }
out:
   if (stream != NULL)
       fclose(stream);
   return retval;
}
