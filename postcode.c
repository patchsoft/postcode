#include <postgres.h>
#include <utils/builtins.h>
#include <libpq/pqformat.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

#include "postcode.h"
#include "binfmt.h"

#define PG_RETURN_POSTCODE(p) return Int32GetDatum(p)
#define PG_GETARG_POSTCODE(n) DatumGetInt32(PG_GETARG_DATUM(n))

Datum postcode_in             (PG_FUNCTION_ARGS);
Datum postcode_out            (PG_FUNCTION_ARGS);
Datum postcode_recv           (PG_FUNCTION_ARGS);
Datum postcode_send           (PG_FUNCTION_ARGS);
Datum postcode_validate       (PG_FUNCTION_ARGS);
Datum postcode_cmp            (PG_FUNCTION_ARGS);
Datum postcode_eq             (PG_FUNCTION_ARGS);
Datum postcode_ne             (PG_FUNCTION_ARGS);
Datum postcode_lt             (PG_FUNCTION_ARGS);
Datum postcode_gt             (PG_FUNCTION_ARGS);
Datum postcode_lte            (PG_FUNCTION_ARGS);
Datum postcode_gte            (PG_FUNCTION_ARGS);
Datum postcode_cmp_partial    (PG_FUNCTION_ARGS);
Datum postcode_eq_partial     (PG_FUNCTION_ARGS);
Datum postcode_ne_partial     (PG_FUNCTION_ARGS);

__attribute__((warn_unused_result))
static inline postcode postcode_mask (postcode a, postcode b) {
   if (! GET_AREA(b))      return 0;
   if (! GET_DISTRICT1(b)) return MASK_DISTRICT(a);
   if (! GET_SECTOR(b))    return MASK_SECTOR(a);
   if (! GET_WALK1(b))     return MASK_WALK(a);
   return a;
}


PG_FUNCTION_INFO_V1(postcode_in);

Datum postcode_in (PG_FUNCTION_ARGS) {
   postcode p = postcode_parse(PG_GETARG_CSTRING(0), false);

   if (p == 0)
      ereport(ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                      errmsg (_("cannot parse input for type postcode"))));

   PG_RETURN_POSTCODE(p);
}


PG_FUNCTION_INFO_V1(postcode_out);

Datum postcode_out (PG_FUNCTION_ARGS) {
   char *str = palloc(8);
   postcode_render(PG_GETARG_POSTCODE(0), str);
   PG_RETURN_CSTRING(str);
}


PG_FUNCTION_INFO_V1(postcode_recv);

Datum postcode_recv (PG_FUNCTION_ARGS) {
   postcode p = pq_getmsgint((StringInfo) PG_GETARG_POINTER(0), sizeof(int32));

   if (! postcode_binchk(p))
      ereport(ERROR, (errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
                      errmsg (_("received binary data is invalid for type postcode")),
                      errhint(_("server binary format version is %s"), STR(EXTVERSION))));

   PG_RETURN_POSTCODE(p);
}


PG_FUNCTION_INFO_V1(postcode_send);

Datum postcode_send (PG_FUNCTION_ARGS) {
   StringInfoData b;
   pq_begintypsend(&b);
   pq_sendint(&b, PG_GETARG_POSTCODE(0), sizeof(int32));
   PG_RETURN_BYTEA_P(pq_endtypsend(&b));
}


PG_FUNCTION_INFO_V1(postcode_validate);

Datum postcode_validate (PG_FUNCTION_ARGS) {
   postcode p = postcode_parse(text_to_cstring(PG_GETARG_TEXT_P(0)), false);
   PG_RETURN_BOOL(p ? TRUE : FALSE);
}


PG_FUNCTION_INFO_V1(postcode_cmp);

Datum postcode_cmp (PG_FUNCTION_ARGS) {
   postcode a = PG_GETARG_POSTCODE(0),
            b = PG_GETARG_POSTCODE(1);

   if (a == b) PG_RETURN_INT32( 0);
   if (a >  b) PG_RETURN_INT32( 1);
   else        PG_RETURN_INT32(-1);
}


PG_FUNCTION_INFO_V1(postcode_eq);

Datum postcode_eq (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) == PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_ne);

Datum postcode_ne (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) != PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_lt);

Datum postcode_lt (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) < PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_gt);

Datum postcode_gt (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) > PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_lte);

Datum postcode_lte (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) <= PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_gte);

Datum postcode_gte (PG_FUNCTION_ARGS) {
   PG_RETURN_BOOL(PG_GETARG_POSTCODE(0) >= PG_GETARG_POSTCODE(1));
}


PG_FUNCTION_INFO_V1(postcode_cmp_partial);

Datum postcode_cmp_partial (PG_FUNCTION_ARGS) {
   postcode b = postcode_parse(text_to_cstring(PG_GETARG_TEXT_P(1)), true);
   postcode a = postcode_mask(PG_GETARG_POSTCODE(0), b);

   if (a == b) PG_RETURN_INT32( 0);
   if (a >  b) PG_RETURN_INT32( 1);
   else        PG_RETURN_INT32(-1);
}


PG_FUNCTION_INFO_V1(postcode_eq_partial);

Datum postcode_eq_partial (PG_FUNCTION_ARGS) {
   postcode b = postcode_parse(text_to_cstring(PG_GETARG_TEXT_P(1)), true);
   postcode a = postcode_mask(PG_GETARG_POSTCODE(0), b);

   if (b == 0) PG_RETURN_BOOL(false); // invalid postcode fragment
   PG_RETURN_BOOL(a == b);
}


PG_FUNCTION_INFO_V1(postcode_ne_partial);

Datum postcode_ne_partial (PG_FUNCTION_ARGS) {
   postcode b = postcode_parse(text_to_cstring(PG_GETARG_TEXT_P(1)), true);
   postcode a = postcode_mask(PG_GETARG_POSTCODE(0), b);

   if (b == 0) PG_RETURN_BOOL(true); // invalid postcode fragment
   PG_RETURN_BOOL(a != b);
}


PG_FUNCTION_INFO_V1(postcode_to_char);

Datum postcode_to_char (PG_FUNCTION_ARGS) {
   postcode p = PG_GETARG_POSTCODE(0);
   text  *txt = PG_GETARG_TEXT_P(1);
   char  *str = VARDATA(txt);
   size_t len = VARSIZE(txt) - VARHDRSZ;

   // each template pattern expands to a maximum of two characters
   if (len >= SIZE_MAX/2)
      ereport(ERROR, (errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
                      errmsg (_("template argument too long"))));

   char *buf = palloc(len*2 + 1);
   char *b = buf;

   for (size_t i = 0; i != len; i++) {
      switch (str[i]) {
         case 'A': WRITE_AREA(b, p);     break;
         case 'D': WRITE_DISTRICT(b, p); break;
         case 'S': WRITE_SECTOR(b, p);   break;
         case 'W': WRITE_WALK(b, p);     break;

        default: *(b++) = str[i];
      }
   }
   *b = '\0';

   PG_RETURN_TEXT_P(cstring_to_text(buf));
}
