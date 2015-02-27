EXTENSION    = postcode
EXTVERSION   = 1.3

MODULE_big   = postcode
OBJS	     = postcode.o binfmt.o
DATA         = postcode--$(EXTVERSION).sql
REGRESS	     = parser sort random quirks format match partial dps
REGRESS_OPTS = --load-extension=$(EXTENSION)

PG_CPPFLAGS  = -Wall -Wpedantic -DEXTVERSION=$(EXTVERSION)

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
