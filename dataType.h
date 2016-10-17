#pragma once

#include <stdint.h>

#define FILEOUT 2
#define FILEIN 1
#define FUNCSUCCEED 0

typedef struct FILEHEADER
{
  uint32_t size;
  char *data;
  uint32_t offset;
} fileHeader;


typedef char RGB8;


/* End of dataType.hpp */