#include <stdlib.h>
#include <string.h>

#include "binfmt.h"
#include "postcode.h"
#include "dps.h"

// maximum number of characters to attempt to parse
#define POSTCODE_PARSE_LIMIT 32

#define IS_AZ(c) (c >= 'A' && c <= 'Z')
#define IS_09(c) (c >= '0' && c <= '9')

static inline int bcmp_ptr (const void *k, const void *v) {
   return strcmp(k, *((char **) v));
}


const char * postcode_version() { return STR(EXTVERSION); }


postcode postcode_parse (const char *str, bool partial) {
   postcode res = 0;
   if (! str) return 0;

   char buf[POSTCODE_PARSE_LIMIT+1];
   int i = 0;
   for (const char *s = str; *s; s++) {
      if (i == POSTCODE_PARSE_LIMIT) return 0; // maximum length to parse
      if (*s >= 'a' && *s <= 'z') buf[i++] = *s - 32; // tr/[a-z]/[A-Z/
      else buf[i++] = *s;
   }
   buf[i] = '\0';

   // match area
   char key[3] = { 0 };
   size_t n = strspn(buf, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   if (! (n == 1 || n == 2)) return 0;

   memcpy(key, buf, n);
   char *a = bsearch(key, areas, N_ELEMS(areas), sizeof(char *), bcmp_ptr);

   if (!a) return 0;
   SET_AREA(res, ((char **) a) - ((char **) areas) + 1);

   if (buf[n] == '\0') return partial ? res : 0;

   // match first digit of the district
   if (! IS_09(buf[n])) return 0;
   SET_DISTRICT1(res, buf[n++] - 47);

   if (buf[n] == '\0') return partial ? res : 0;

   // second character of district [0-9A-Z], or the sector [0-9]
   uint8_t tmp = 0;
   if      (IS_AZ(buf[n])) SET_DISTRICT2(res, buf[n++] - 47);
   else if (IS_09(buf[n])) tmp = buf[n++];

   while (buf[n] == ' ') n++; // skip any number of spaces

   if (buf[n] == '\0') {
      // prefer district LS48 over district LS4, sector 8
      if (tmp) SET_DISTRICT2(res, tmp - 47);
      return partial ? res : 0;
   }

   // sector or walk
   if (IS_09(buf[n])) {
      SET_SECTOR(res, buf[n++] - 47); // current char is sector
      if (tmp) {
         // permit district 0 but disallow as leading zero (eg. 0[0-9])
         if (GET_DISTRICT1(res) == 1 && IS_09(tmp)) return 0;
         SET_DISTRICT2(res, tmp - 47); // previous char was district
      }
      if (buf[n] =='\0') return partial ? res : 0;
   } else {
      if (! tmp) return 0;
      SET_SECTOR(res, tmp - 47); // previous char was sector
   }

   // walk
   if (strspn(&buf[n], "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 2) return 0;
   SET_WALK1(res, buf[n++] - 64);
   SET_WALK2(res, buf[n++] - 64);

   if (buf[n] != '\0') return 0;

   return res;
}


int postcode_render (postcode p, char buf[8]) {
   if (! postcode_binchk(p)) return 0;

   char *b = buf;

   WRITE_AREA(b,p);
   WRITE_DISTRICT(b,p);
   *(b++) = ' ';
   WRITE_SECTOR(b,p);
   WRITE_WALK(b,p);

   *b = '\0';
   return b - buf; // number of chars written
}


bool postcode_binchk (postcode p) {
   // require a valid area code as defined in areas.h
   if (GET_AREA(p) < 1 || GET_AREA(p) > N_ELEMS(areas)) return false;

   // [0-9]
   if (GET_DISTRICT1(p) < 1 || GET_DISTRICT1(p) > 11) return false;

   // empty (== 0) or [A-Z0-9] excluding intervening codes [:;<=>?@]
   if (GET_DISTRICT2(p) > 43) return false;
   if (GET_DISTRICT2(p) > 11 && GET_DISTRICT2(p) < 18) return false;

   // Do not allow district 00
   if (GET_DISTRICT1(p) == 1 && GET_DISTRICT2(p) == 1) return false;

   // [0-9]
   if (GET_SECTOR(p) < 1 || GET_SECTOR(p) > 11) return false;

   // [A-Z]
   if (GET_WALK1(p) < 1 || GET_WALK1(p) > 27) return false;
   if (GET_WALK2(p) < 1 || GET_WALK2(p) > 27) return false;

   return true;
}


dps postcode_dps_parse (const char *str) {
   if (! (str && strnlen(str, 3) == 2)) return 0;
   char key[3] = { 0 };
   memcpy(key, str, 2);
   if (key[1] >= 'a' && key[1] <= 'z') key[1] -= 32; // tr/[a-z]/[A-Z/
   char *d = bsearch(key, dpsuffix, N_ELEMS(dpsuffix), sizeof(char *), bcmp_ptr);
   if (!d) return 0;
   return ((char **) d) - ((char **) dpsuffix) + 1;
}


int postcode_dps_render (dps d, char buf[3]) {
   if (! postcode_dps_binchk(d)) return 0;
   memcpy(buf, dpsuffix[d-1], 2);
   buf[2] = '\0';
   return 2;
}


bool postcode_dps_binchk (dps d) {
   return d <= N_ELEMS(dpsuffix);
}
