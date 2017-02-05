#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ascii.h"

char *ascii2hex(char *ascii)
{
   size_t i;
   size_t len = strlen(ascii);

   char *hex = calloc(2*len + 1, 1);
   if (hex == NULL)
   {
      return NULL;
   }

   for (i = 0; i < len; i++)
   {
      snprintf(hex + i*2, 3, "%.2X", (uint8_t)ascii[i]);
   }
   return hex;
}

char *hex2ascii(char *hex)
{
   size_t i;
   size_t len = strlen(hex);
   char *str = calloc((len / 2) + 1, 1);

   if (str == NULL || len % 2 != 0)
   {
      return NULL;
   }

   for (i = 0; i < len >> 1; i++)
   {
      uint8_t byte = 0;   

      if (hex[2*i] >= 'A' && hex[2*i] <= 'F')
      {
         byte = (hex[2*i] - 'A' + 0xA) << 4;
      }
      else if (hex[2*i] >= '0' && hex[2*i] <= '9')
      {
         byte = (hex[2*i] - '0') << 4;
      }

      if (hex[2*i + 1] >= 'A' && hex[2*i + 1] <= 'F')
      {
         byte += hex[2*i + 1] - 'A' + 0xA;
      }
      else if (hex[2*i + 1] >= '0' && hex[2*i + 1] <= '9')
      {
         byte += hex[2*i + 1] - '0';
      }

      str[i] = byte;
   }
   return str;
}
