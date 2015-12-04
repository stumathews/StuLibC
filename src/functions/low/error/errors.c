#include <string.h>
#include <errno.h>
#include <stulibc.h>



void ERR_Print(const char* error, int should_log)
{
  CHECK_STRING( error, IS_NOT_EMPTY );
  PRINT("Error: %s", error);
  
  if(should_log)
  {
    LOG_Log((char*)error);
  }
}

char* ERR_GetLastError()
{
  return (char*) strerror(errno);
}
