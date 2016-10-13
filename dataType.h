#pragma once

#include <stdint.h>


typedef struct FILEHEADER
{
  uint32_t size;
  char *data;
  uint32_t offset;
} fileHeader;


typedef char RGB8;


/* End of dataType.hpp */