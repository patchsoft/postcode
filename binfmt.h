#ifndef POSTCODE_BINFMT_H__
#define POSTCODE_BINFMT_H__

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t postcode;
typedef uint8_t  dps;

const char * postcode_version (void);

__attribute__((nonnull (1)))
__attribute__((warn_unused_result))
postcode postcode_parse (const char *str, bool partial);

__attribute__((nonnull (2)))
int postcode_render (postcode p, char buf[8]);

__attribute__((warn_unused_result))
bool postcode_binchk (postcode p);

__attribute__((nonnull (1)))
__attribute__((warn_unused_result))
dps postcode_dps_parse (const char *str);

__attribute__((nonnull (2)))
int postcode_dps_render (dps d, char buf[3]);

__attribute__((warn_unused_result))
bool postcode_dps_binchk (dps d);

#endif
