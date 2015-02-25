SELECT
   code,
   format,
   to_char(code, format) AS out,
   to_char(code, format) = expect AS pass
FROM (
   VALUES
   ('EC4Y 0HQ'::postcode, 'AD SW', 'EC4Y 0HQ'),
   ('EC4Y 0HQ'::postcode, 'ADSW', 'EC4Y0HQ'),
   ('EC4Y 0HQ'::postcode, 'ADSW', 'EC4Y0HQ'),
   ('EC4Y 0HQ'::postcode, 'AD', 'EC4Y'),
   ('EC4Y 0HQ'::postcode, 'SW', '0HQ'),
   ('EC4Y 0HQ'::postcode, 'A', 'EC'),
   ('EC4Y 0HQ'::postcode, 'D', '4Y'),
   ('EC4Y 0HQ'::postcode, 'S', '0'),
   ('EC4Y 0HQ'::postcode, 'W', 'HQ'),
   ('EC4Y 0HQ'::postcode, ' AD SW ', ' EC4Y 0HQ '),
   ('EC4Y 0HQ'::postcode, '-AD SW-', '-EC4Y 0HQ-'),
   ('EC4Y 0HQ'::postcode, '', ''),
   ('EC4Y 0HQ'::postcode, 'test', 'test'),
   ('EC4Y 0HQ'::postcode, E'A\nD\nS\nW', E'EC\n4Y\n0\nHQ'),
   ('EC4Y 0HQ'::postcode, 'ADAD', 'EC4YEC4Y'),
   ('EC4Y 0HQ'::postcode, 'AA', 'ECEC'),
   ('EC4Y 0HQ'::postcode, 'A A', 'EC EC'),
   ('EC4Y 0HQ'::postcode, ' D D ', ' 4Y 4Y '),
   ('EC4Y 0HQ'::postcode, 'WW', 'HQHQ'),
   ('EC4Y 0HQ'::postcode, 'WSW', 'HQ0HQ'),
   ('SW1A 1AA'::postcode, 'W', 'AA'),
   ('BX5 5AT'::postcode, 'DD', '55'),
   ('BX5 5AT'::postcode, 'AD SW', 'BX5 5AT'),
   ('BX5 5AT'::postcode, 'ADSW', 'BX55AT'),
   ('BX5 5AT'::postcode, '.ADSW.ADSW.', '.BX55AT.BX55AT.'),
   ('G58 1SB'::postcode, 'ADSW', 'G581SB'),
   ('G58 1SB'::postcode, 'AD SW', 'G58 1SB'),
   ('G58 1SB'::postcode, 'AA', 'GG'),
   ('G58 1SB'::postcode, 'SWAAD', '1SBGG58'),
   ('G58 1SB'::postcode, '.SWAAD-', '.1SBGG58-')
) AS sample (code, format, expect)
ORDER BY to_char(code, format) = expect ASC
