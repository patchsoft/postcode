#ifndef POSTCODE_H__
#define POSTCODE_H__

#include "areas.h"

#define STR(macro) QUOTE(macro)
#define QUOTE(name) #name

#ifndef EXTVERSION
#error  EXTVERSION is not defined
#endif

#define N_ELEMS(arr) (sizeof(arr) / sizeof(arr[0]))

#define GET_BITS(var,pos,len)     ((var) >> (pos) & ((1<<(len))-1))
#define CLR_BITS(var,pos,len)     ((var) &= ~(((1<<(len))-1)<<pos))
#define SET_BITS(var,pos,len,set) ((var) = ((var) &~ (((1<<(len))-1)<<pos)) | ((set)<<(pos)))

#define GET_WALK2(p)       GET_BITS(p,  0, 5)
#define GET_WALK1(p)       GET_BITS(p,  5, 5)
#define GET_SECTOR(p)      GET_BITS(p, 10, 4)
#define GET_DISTRICT2(p)   GET_BITS(p, 14, 6)
#define GET_DISTRICT1(p)   GET_BITS(p, 20, 4)
#define GET_AREA(p)        GET_BITS(p, 24, 8)

#define SET_WALK2(p,v)     SET_BITS(p,  0, 5, v)
#define SET_WALK1(p,v)     SET_BITS(p,  5, 5, v)
#define SET_SECTOR(p,v)    SET_BITS(p, 10, 4, v)
#define SET_DISTRICT2(p,v) SET_BITS(p, 14, 6, v)
#define SET_DISTRICT1(p,v) SET_BITS(p, 20, 4, v)
#define SET_AREA(p,v)      SET_BITS(p, 24, 8, v)

// each subsequent mask includes the preceeding range
#define MASK_WALK(p)       CLR_BITS(p, 0, 10)
#define MASK_SECTOR(p)	   CLR_BITS(p, 0, 14)
#define MASK_DISTRICT(p)   CLR_BITS(p, 0, 24)

// write 1 or 2 chars to buffer and advance pointer
// WRITE_AREA() may need prior call to postcode_binchk() to ensure index validity
#define WRITE_AREA(b,p) do { b = stpncpy(b, areas[GET_AREA(p)-1], 2); } while(0)

#define WRITE_DISTRICT(b,p) do { *(b++) = GET_DISTRICT1(p) + 47; \
           if (GET_DISTRICT2(p)) *(b++) = GET_DISTRICT2(p) + 47; } while(0)

#define WRITE_SECTOR(b,p) do { *(b++) = GET_SECTOR(p) + 47; } while(0)

#define WRITE_WALK(b,p) do { *(b++) = GET_WALK1(p) + 64; \
                             *(b++) = GET_WALK2(p) + 64; } while(0)

#endif
