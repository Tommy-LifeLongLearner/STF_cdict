# C Dictionaries

## Introduction

This is a single linked list of structs library for creating and manipulating dictionaries in **c**

## Usage

Include the `c_dict.h` header file
```c
#include "c_dict.h"
```
Create for example a file `test.c`, then create some dicts and add some data

**test.c**
```c
#include "c_dict.h"

int main() {
  DICT *person = DICT_CREATE(); // create a new empty dict
  DICT *pl = DICT_CREATE();
  DICT_ADD(person, "name", "Saadi Toumi Fouad"); // add a key, value pair
  DICT_ADD(person, "year of birth", 1993); 
  DICT_ADD(person, "country", "Algeria");
  DICT_ADD(person, "programming languages", pl);
  DICT_ADD(person, "is married", true);
  DICT_ADD(person, "kids", NULL);
  DICT_ADD(person, "lucky character", 'T');
  DICT_ADD(pl, "C", 65.9);
  DICT_ADD(pl, "C++", 45.3f);
  DICT_ADD(pl, "C#", 34.7l);
  DICT_ADD(pl, "Java", 27.3f);
  DICT_ADD(pl, "JavaScript", 73.8);
  DICT_ADD(pl, "Python", 34.2f);
  DICT_ADD(pl, "PHP", 17l);
  DICT_PRINT(person); // print the content of the dict
  DICT_PRINTD(person); // print the content of the dict plus each value type
  DICT_DELETE(person); // clear the items and free the dict memory
  return 0;
}
```

Compile and link for example using **gcc**:
```
gcc -c c_dict.c -o c_dict.o
gcc test.c -o test c_dict.o 
```

Run the executable so you get the output
**Ordinary print (DICT_PRINT)**
![](C:\Users\STF\Desktop\c_dict\img\img1.png)
**Type print (DICT_PRINTD)**
![](C:\Users\STF\Desktop\c_dict\img\img2.png)

## Supported types as values:
```c
NULL
bool
unsigned char
signed char
unsigned short int
unsigned int
unsigned long int
unsigned long long int
signed short int
signed int
signed long int
signed long long int
float 
double
long double
char *
DICT
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
  DICT_ITEM *start;
  DICT_ITEM *end;
  int size;
} DICT;
```
* **Dict Item**(key value pairs)
```c
////////////////////////////////////////////////////////////////////////////////
/// \brief item class holds the `type` of the item, the `value`, the property
/// name as `key` and the address of the next pair as (KV)
///
////////////////////////////////////////////////////////////////////////////////
typedef struct DICT_ITEM {
  VALUE_TYPE type;
  char *key;
  void *value;
  struct DICT_ITEM *next;
} DICT_ITEM;
```

## Documentation

For more infos checkout the **[Docs](https://github.com/Tommy-LifeLongLearner/c_dict/wiki/Documentation)** 