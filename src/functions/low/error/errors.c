#include <errors.h>
#include <logging.h>
#include <string.h>
#include <errno.h>
#include <debugging.h>
#include <safetychecking.h>

void ERR_Print(const char* error, int should_log)
{
  CHECK_STRING( error, IS_NOT_EMPTY );
  DBG("Printing error:%s\n", error);
  perror(error);
  
  if( should_log )
    LOG_Log((char*)error);
}

char* ERR_GetLastError()
{
  return (char*) strerror(errno);
}
