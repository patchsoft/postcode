SELECT
   code,
   qry,
   code % qry AS match,
   code % qry = expect AS pass
FROM (
   VALUES
   ('EC4Y 0HQ'::postcode, '',           false),

   ('EC4Y 0HQ'::postcode, 'EC4Y 0HQ',   true),
   ('EC4Y 0HQ'::postcode, 'EC4Y 0',     true),
   ('EC4Y 0HQ'::postcode, 'EC4Y ',      true),
   ('EC4Y 0HQ'::postcode, 'EC4Y',       true),
   ('EC4Y 0HQ'::postcode, 'EC',         true),

   ('EC4Y 0HQ'::postcode, ' EC4Y 0HQ ', false),
   ('EC4Y 0HQ'::postcode, 'EC4Y 0HQ ',  false),
   ('EC4Y 0HQ'::postcode, 'EC4Y 0H ',   false),
   ('EC4Y 0HQ'::postcode, 'EC4 ',       false),
   ('EC4Y 0HQ'::postcode, 'EC4',        false),
   ('EC4Y 0HQ'::postcode, 'EC4 0',      false),
   ('EC4Y 0HQ'::postcode, 'EC4 0HQ',    false),
   ('EC4Y 0HQ'::postcode, 'E4 0HQ',     false),
   ('EC4Y 0HQ'::postcode, 'E',          false),
   ('EC4Y 0HQ'::postcode, 'E ',         false),

   ('EC40 1AB'::postcode, 'EC40 1AB',   true),
   ('EC40 1AB'::postcode, 'EC40 1',     true),
   ('EC40 1AB'::postcode, 'EC40 ',      true),
   ('EC40 1AB'::postcode, 'EC40',       true),
   ('EC40 1AB'::postcode, 'EC',         true),

   ('EC40 1AB'::postcode, 'EC4',        false),
   ('EC40 1AB'::postcode, 'EC4 ',       false),
   ('EC40 1AB'::postcode, 'EC41',       false),
   ('EC40 1AB'::postcode, 'EC4 1',      false),
   ('EC40 1AB'::postcode, 'EH',         false),
   ('EC40 1AB'::postcode, 'EH4',        false),
   ('EC40 1AB'::postcode, 'EH40',       false)

) AS sample (code, qry, expect)
ORDER BY code % qry = expect ASC
