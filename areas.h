/* Used for binary search and ordered according to strcmp()

   Any changes break binary compatibility so in the unlikely
   event further postcode areas are allocated it will be necessary
   to dump and restore any tables with columns of this type

   Client applications receiving results in binary format should
   check the extension version matches return of postcode_version()

   Binary compatibility is guaranteed between major version numbers
*/

static const char * const areas[] = {
   "AB", // Aberdeen
   "AL", // St Albans
   "B",  // Birmingham
   "BA", // Bath
   "BB", // Blackburn
   "BD", // Bradford
   "BF", // BFPO
   "BH", // Bournemouth
   "BL", // Bolton
   "BN", // Brighton
   "BR", // Bromley
   "BS", // Bristol
   "BT", // Northern Ireland
   "BX", // Non-geographic
   "CA", // Carlisle
   "CB", // Cambridge
   "CF", // Cardiff
   "CH", // Chester
   "CM", // Chelmsford
   "CO", // Colchester
   "CR", // Croydon
   "CT", // Canterbury
   "CV", // Coventry
   "CW", // Crewe
   "DA", // Dartford
   "DD", // Dundee
   "DE", // Derby
   "DG", // Dumfries
   "DH", // Durham
   "DL", // Darlington
   "DN", // Doncaster
   "DT", // Dorchester
   "DY", // Dudley
   "E",  // London (East)
   "EC", // London (East Central)
   "EH", // Edinburgh
   "EN", // Enfield
   "EX", // Exeter
   "FK", // Falkirk
   "FY", // Blackpool
   "G",  // Glasgow
   "GL", // Gloucester
   "GU", // Guildford
   "GY", // Guernsey
   "HA", // Harrow
   "HD", // Huddersfield
   "HG", // Harrogate
   "HP", // Hemel Hempstead
   "HR", // Hereford
   "HS", // Outer Hebrides
   "HU", // Hull
   "HX", // Halifax
   "IG", // Ilford
   "IM", // Isle of Man
   "IP", // Ipswich
   "IV", // Inverness
   "JE", // Jersey
   "KA", // Kilmarnock
   "KT", // Kingston upon Thames
   "KW", // Kirkwall
   "KY", // Kirkcaldy
   "L",  // Liverpool
   "LA", // Lancaster
   "LD", // Llanrindod Wells
   "LE", // Leicester
   "LL", // Llandudno
   "LN", // Lincoln
   "LS", // Leeds
   "LU", // Luton
   "M",  // Manchester
   "ME", // Rochester
   "MK", // Milton Keynes
   "ML", // Motherwell
   "N",  // London (North)
   "NE", // Newcastle upon Tyne
   "NG", // Nottingham
   "NN", // Northampton
   "NP", // Newport
   "NR", // Norwich
   "NW", // London (North West)
   "OL", // Oldham
   "OX", // Oxford
   "PA", // Paisley
   "PE", // Peterborough
   "PH", // Perth
   "PL", // Plymouth
   "PO", // Portsmouth
   "PR", // Preston
   "RG", // Reading
   "RH", // Redhill
   "RM", // Romford
   "S",  // Sheffield
   "SA", // Swansea
   "SE", // London (South East)
   "SG", // Stevenage
   "SK", // Stockport
   "SL", // Slough
   "SM", // Sutton
   "SN", // Swindon
   "SO", // Southampton
   "SP", // Salisbury
   "SR", // Sunderland
   "SS", // Southend-on-Sea
   "ST", // Stoke-on-Trent
   "SW", // London (South West)
   "SY", // Shrewsbury
   "TA", // Taunton
   "TD", // Galashiels
   "TF", // Telford
   "TN", // Tonbridge
   "TQ", // Torquay
   "TR", // Truro
   "TS", // Cleveland
   "TW", // Twickenham
   "UB", // Southall
   "W",  // London (West)
   "WA", // Warrington
   "WC", // London (West Central)
   "WD", // Watford
   "WF", // Wakefield
   "WN", // Wigan
   "WR", // Worcester
   "WS", // Walsall
   "WV", // Wolverhampton
   "YO", // York
   "ZE"  // Lerwick
};
