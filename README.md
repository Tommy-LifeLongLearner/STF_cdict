# STF C Dictionaries

## Introduction

This is a simple library for creating and manipulating dictionaries in **c** using linked lists of structs

## Usage

Include the `stf-dict.h` header file
```c
#include "stf-dict.h"
```
Then create some dicts and manipulate them
```c
STF_DICT *dict = STF_DICT_CREATE();
STF_DICT_PRINT(dict);
STF_DELETE_DICT(dict);
```
Output (empty dict)
```txt
{
  empty
}
```
Add some key value pairs
```c
  STF_DICT *dict = STF_DICT_CREATE();
  STF_DICT_ADD(dict, "name", "Saadi Toumi Fouad");
  STF_DICT_ADD(dict, "age", 29);
  STF_DICT_ADD(dict, "country", "Algeria");
  STF_DICT_PRINT(dict);
  STF_DELETE_DICT(dict);
```
Output
```txt
{
  "name": "Saadi Toumi Fouad",
  "age": 29,
  "country": "Algeria"
}
```

## Supported types:
```c
bool as STF_TYPE_BOOL
char as STF_TYPE_UNSIGNED_CHAR
signed char as STF_TYPE_SIGNED_CHAR
unsigned short int as STF_TYPE_UNSIGNED_SHORT_INT
unsigned int as STF_TYPE_UNSIGNED_INT
unsigned long int as STF_TYPE_UNSIGNED_LONG_INT
unsigned long long_int as STF_TYPE_UNSIGNED_LONG_LONG_INT
signed short int as STF_TYPE_SIGNED_SHORT_INT
signed int as STF_TYPE_SIGNED_INT
signed long_int as STF_TYPE_SIGNED_LONG_INT
signed long long int as STF_TYPE_SIGNED_LONG_LONG_INT
float as STF_TYPE_FLOAT
double as STF_TYPE_DOUBLE
long double as STF_TYPE_LONG_DOUBLE
string as STF_TYPE_STRING
dict as STF_TYPE_DICT
```

## Implementation:
* **Dict**
```c
////////////////////////////////////////////////////////////////////////////////
/// \brief dict class(linked list of items) with the first and
/// last item as `start`, `end` and the number of items as `size`
///
////////////////////////////////////////////////////////////////////////////////
typedef struct {
  STF_DICT_ITEM *start;
  STF_DICT_ITEM *end;
  int size;
} STF_DICT;
```
* **Dict Item**(key value pairs)
```c
////////////////////////////////////////////////////////////////////////////////
/// \brief item class holds the `type` of the item, the `value`, the property
/// name as `key` and the address of the next pair as (KV)
///
////////////////////////////////////////////////////////////////////////////////
typedef struct STF_DICT_ITEM {
  STF_TYPE type;
  char *key;
  void *value;
  struct STF_DICT_ITEM *next;
} STF_DICT_ITEM;
```

## Documentation

For more infos checkout the [Docs](https://github.com/Tommy-LifeLongLearner/STF_cdict/wiki)