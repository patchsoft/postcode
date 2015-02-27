CREATE TYPE postcode;

CREATE FUNCTION postcode_in(cstring)
   RETURNS postcode
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_out(postcode)
   RETURNS cstring
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_recv(internal)
   RETURNS postcode
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_send(postcode)
   RETURNS bytea
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE postcode (
   INPUT    = postcode_in,
   OUTPUT   = postcode_out,
   RECEIVE  = postcode_recv,
   SEND     = postcode_send,
   LIKE     = pg_catalog.int4,
   CATEGORY = 'S'
);

CREATE FUNCTION postcode_validate(text)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_cmp(postcode, postcode)
   RETURNS integer
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_eq(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_ne(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_lt(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_gt(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_lte(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_gte(postcode, postcode)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_cmp_partial(postcode, text)
   RETURNS integer
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_eq_partial(postcode, text)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION postcode_ne_partial(postcode, text)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION to_char(postcode, text)
   RETURNS text
   AS 'MODULE_PATHNAME', 'postcode_to_char'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR = (
   PROCEDURE  = postcode_eq,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = =,
   NEGATOR    = <>,
   RESTRICT   = eqsel,
   JOIN       = eqjoinsel);

CREATE OPERATOR <> (
   PROCEDURE  = postcode_ne,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = <>,
   NEGATOR    = =,
   RESTRICT   = neqsel,
   JOIN       = neqjoinsel);

CREATE OPERATOR < (
   PROCEDURE  = postcode_lt,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = >,
   NEGATOR    = >=);

CREATE OPERATOR > (
   PROCEDURE  = postcode_gt,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = <,
   NEGATOR    = <=);

CREATE OPERATOR <= (
   PROCEDURE  = postcode_lte,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = >=,
   NEGATOR    = >);

CREATE OPERATOR >= (
   PROCEDURE  = postcode_gte,
   LEFTARG    = postcode,
   RIGHTARG   = postcode,
   COMMUTATOR = <=,
   NEGATOR    = <);

CREATE OPERATOR % (
   PROCEDURE  = postcode_eq_partial,
   LEFTARG    = postcode,
   RIGHTARG   = text,
   NEGATOR    = !%,
   RESTRICT   = eqsel,
   JOIN       = eqjoinsel
);

CREATE OPERATOR !% (
   PROCEDURE  = postcode_ne_partial,
   LEFTARG    = postcode,
   RIGHTARG   = text,
   NEGATOR    = %,
   RESTRICT   = neqsel,
   JOIN       = neqjoinsel
);

CREATE OPERATOR FAMILY postcode_ops USING btree;

CREATE OPERATOR CLASS postcode_ops DEFAULT
FOR TYPE postcode USING btree FAMILY postcode_ops AS
   OPERATOR 1 <  (postcode, postcode),
   OPERATOR 2 <= (postcode, postcode),
   OPERATOR 3 =  (postcode, postcode),
   OPERATOR 4 >= (postcode, postcode),
   OPERATOR 5 >  (postcode, postcode),
   FUNCTION 1 postcode_cmp(postcode, postcode),

   OPERATOR 3 %  (postcode, text),
   FUNCTION 1 postcode_cmp_partial(postcode, text);


CREATE TYPE dps;

CREATE FUNCTION dps_in(cstring)
   RETURNS dps
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_out(dps)
   RETURNS cstring
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_recv(internal)
   RETURNS dps
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_send(dps)
   RETURNS bytea
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE dps (
   INPUT          = dps_in,
   OUTPUT         = dps_out,
   RECEIVE        = dps_recv,
   SEND           = dps_send,
   CATEGORY       = 'S',
   INTERNALLENGTH = 1,
   ALIGNMENT      = char,
   PASSEDBYVALUE
);

CREATE FUNCTION dps_validate(text)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_cmp(dps, dps)
   RETURNS integer
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_eq(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_ne(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_lt(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_gt(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_lte(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION dps_gte(dps, dps)
   RETURNS boolean
   AS 'MODULE_PATHNAME'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR = (
   PROCEDURE  = dps_eq,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = =,
   NEGATOR    = <>,
   RESTRICT   = eqsel,
   JOIN       = eqjoinsel);

CREATE OPERATOR <> (
   PROCEDURE  = dps_ne,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = <>,
   NEGATOR    = =,
   RESTRICT   = neqsel,
   JOIN       = neqjoinsel);

CREATE OPERATOR < (
   PROCEDURE  = dps_lt,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = >,
   NEGATOR    = >=);

CREATE OPERATOR > (
   PROCEDURE  = dps_gt,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = <,
   NEGATOR    = <=);

CREATE OPERATOR <= (
   PROCEDURE  = dps_lte,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = >=,
   NEGATOR    = >);

CREATE OPERATOR >= (
   PROCEDURE  = dps_gte,
   LEFTARG    = dps,
   RIGHTARG   = dps,
   COMMUTATOR = <=,
   NEGATOR    = <);

CREATE OPERATOR FAMILY dps_ops USING btree;

CREATE OPERATOR CLASS dps_ops
DEFAULT FOR TYPE dps USING btree FAMILY dps_ops AS
   OPERATOR 1 <,
   OPERATOR 2 <=,
   OPERATOR 3 =,
   OPERATOR 4 >=,
   OPERATOR 5 >,
   FUNCTION 1 dps_cmp(dps, dps);
