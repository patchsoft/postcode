/* Used for binary search and ordered according to strcmp()

   first character is numerical [0-9]
   second character is alphabetical [A-Z] excluding CIKMOV

   maximum code found in PAF is 9T with 9U-9Z used as defaults
   where DPS for an address is unknown
*/

static const char * const dpsuffix[] = {
	"1A",
	"1B",
	"1D",
	"1E",
	"1F",
	"1G",
	"1H",
	"1J",
	"1L",
	"1N",
	"1P",
	"1Q",
	"1R",
	"1S",
	"1T",
	"1U",
	"1W",
	"1X",
	"1Y",
	"1Z",
	"2A",
	"2B",
	"2D",
	"2E",
	"2F",
	"2G",
	"2H",
	"2J",
	"2L",
	"2N",
	"2P",
	"2Q",
	"2R",
	"2S",
	"2T",
	"2U",
	"2W",
	"2X",
	"2Y",
	"2Z",
	"3A",
	"3B",
	"3D",
	"3E",
	"3F",
	"3G",
	"3H",
	"3J",
	"3L",
	"3N",
	"3P",
	"3Q",
	"3R",
	"3S",
	"3T",
	"3U",
	"3W",
	"3X",
	"3Y",
	"3Z",
	"4A",
	"4B",
	"4D",
	"4E",
	"4F",
	"4G",
	"4H",
	"4J",
	"4L",
	"4N",
	"4P",
	"4Q",
	"4R",
	"4S",
	"4T",
	"4U",
	"4W",
	"4X",
	"4Y",
	"4Z",
	"5A",
	"5B",
	"5D",
	"5E",
	"5F",
	"5G",
	"5H",
	"5J",
	"5L",
	"5N",
	"5P",
	"5Q",
	"5R",
	"5S",
	"5T",
	"5U",
	"5W",
	"5X",
	"5Y",
	"5Z",
	"6A",
	"6B",
	"6D",
	"6E",
	"6F",
	"6G",
	"6H",
	"6J",
	"6L",
	"6N",
	"6P",
	"6Q",
	"6R",
	"6S",
	"6T",
	"6U",
	"6W",
	"6X",
	"6Y",
	"6Z",
	"7A",
	"7B",
	"7D",
	"7E",
	"7F",
	"7G",
	"7H",
	"7J",
	"7L",
	"7N",
	"7P",
	"7Q",
	"7R",
	"7S",
	"7T",
	"7U",
	"7W",
	"7X",
	"7Y",
	"7Z",
	"8A",
	"8B",
	"8D",
	"8E",
	"8F",
	"8G",
	"8H",
	"8J",
	"8L",
	"8N",
	"8P",
	"8Q",
	"8R",
	"8S",
	"8T",
	"8U",
	"8W",
	"8X",
	"8Y",
	"8Z",
	"9A",
	"9B",
	"9D",
	"9E",
	"9F",
	"9G",
	"9H",
	"9J",
	"9L",
	"9N",
	"9P",
	"9Q",
	"9R",
	"9S",
	"9T",
	"9U",
	"9W",
	"9X",
	"9Y",
	"9Z"
};