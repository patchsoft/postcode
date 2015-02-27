Postcode 1.3
============
UK postcode encoded in 32 bits and optimised for indexing and partial matches


Coverage
--------
Supports all 126 postcode areas. The crown dependencies GY, JE and IM are
included plus two non-geographic areas BX and BF.

The type should support all current and future codes with the sole exception
of the atypical code GIR 0AA, which Royal Mail nolonger includes within the
postcode address file. In the unlikely event further postcode areas are added
the type is extensible to a maximum of 255 areas (see areas.h)


Parsing
-------
Text input must match one of the above areas followed by a correctly specified
district, sector and walk. Although the type enforces entry of a code with the
correct components, confirming a code is allocated for use requires an external
data source such as [Code-Point Open](http://www.ordnancesurvey.co.uk)

The text parser is relatively tolerant of varied formatting and will correct
for capitalisation and a variable number (or lack of) spaces between the
outward and inward codes.


Rendering
---------
When rendering postcodes to text the output buy by default will be in upper
case with a single space between the outcode and incode. If an alternative
format is required a to_char() function. The default output is equivalent to
calling to_char(postcode, 'AD SW');


Partial matching
----------------
For partial match queries using the % operator any potential ambiguity is
resolved by allocating the maximum number of digits to the district unless an
explicit space is placed between the district and sector.

For example % 'LS24' returns all postcodes in district LS24. To return all
codes in sector 4 of LS2 use % 'LS2 4'.

Neither or both characters of the walk must be entered. A partial search
including them is functionally equivalent to the equality = operator.


Indexing
--------
Standard B-tree operators are supported. The sort order is consistent with
that of the type rendered to text format using the C locale. Indexes can
also be used to accelerate partial matches performed via the % operator.

A B-tree index for the encoded type will be approximately 25% smaller than
an equivalent index on a column of type text. This may give a performance
advantage where the index can therefore be held entirely within memory.


Delivery point suffixes
-----------------------
For any postcode there is a maximum of 175 delivery points, each of which
is allocated a suffix of the form [1-9][A-Z] with the characters CIKMOV not
used. Suffixes follow the sequence 1A, 1B, 1C through to 9T. Codes 9U-9Z
are for use by applications as defaults where the correct suffix is unknown.

A suitable type (dps) is provided which encodes into one byte all possible
values, including codes 9U-9Z. Parsing is case insensitive but output is
always in upper case.

The type aims to provide strict validation rather than space efficiency,
although some small storage savings can be made compared to char(2) if
careful ordering of columns is made with respect to alignment.


Binary format
-------------
For client applications exchanging results in binary format the functions
declared in binfmt.h can be used for parsing from or rendering to text format


Bugs
----
Regression tests are provided using pg_regress via the installcheck target.
Reports of errors or omissions are welcomed by the author via email to
dgreen at patchsoft .co.uk (remove all spaces).
