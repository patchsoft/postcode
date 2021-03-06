SELECT
   code,
   postcode_validate(code) AS valid,
   postcode_validate(code) = expect AS pass
FROM (
   VALUES
   -- allow
   ('L1 1AA', true),
   ('L0 0AA', true),
   ('L1 0AA', true),
   ('L0 1AA', true),

   -- forbid
   ('L00 0AA', false),
   ('L00 1AA', false),
   ('L01 0AA', false),
   ('L01 1AA', false),

   -- unsupported
   ('GIR 0AA', false)

) AS sample (code, expect);
