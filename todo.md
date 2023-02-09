## Notes from schombert

- Reading files line-by-line with getline() is inefficient, its faster to just jump(move?) their contents all at once into a character array and operate on that
- `Global_Market` is ill defined, as it manages both market and readining defs from the file, in this case the def reading should be moved out of the class

## finished
- the `type` member of the token struct should probably be a enum Class
- avoid putting `using namespace std;` in headers (this forces others into using it, so needed evil ig)
- `#pragma once` instead of header guards, while not standard it apparently works nearly everywhere (odd)
- Dont initalise strings to "NULL" as by default they have a length of 0 which better represents their lack of value
- `float fMilitancy = 0` is valid and better than putting/creating a new constructor (there are some cases where i would need a new constructor, but this is true nonetheless)
- No need to use typedef, this is a legacy feature of C and in any case where a *type alias* is needed the `using` keyword is better

## Note
- use `constexpr inline float fOilOutputAmount = 1.0f` instead of `#define fOilOutputAmount 1.0` which will work the same way but with better type safety
- if a member function of a class or struct doesnt modify its contents, its a good idea to mark that function `const`

## Design
- `string szCulture` isnt best, since theres a limited number of cultures in the game itd be better to just read all the cultures and store a index to the culture in a vector rather than the whole string 
- `bool isNumber(string szLine)` is bad as it creates a copy of szLine for the function, it would be better to use `bool isNumber(std::string_view szLine)` as this wouldnt create a copy
- though in the case a string view wouldnt work `bool isNumber(string const& szLine)` as this passes szLine as a reference (again not creating a copy)
