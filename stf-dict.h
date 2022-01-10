////////////////////////////////////////////////////////////////////////////////
//
// STF_Dict - simple library to create and manipulate dictionaries
// Copyright (C) 2021 Saadi Toumi Fouad (saaditoumifouad@gmail.com)
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
  #error "This library is for c, not meant to be used with c++!";
#else
  #ifndef STF_DICT_H
  #define STF_DICT_H

////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

// STF_PRINTC_H
#if defined _WIN32 || defined _WIN64
  #include <windows.h>
  #define GREY FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN
  #define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
  #define RED FOREGROUND_RED| FOREGROUND_INTENSITY
  #define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
  #define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
  #define WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#else
  #define GREY 0
  #define YELLOW 1
  #define RED 2
  #define GREEN 3
  #define BLUE 4
  #define WHITE 5
#endif

void printc(int color, char *output, ...);
// end of STF_PRINTC_H

////////////////////////////////////////////////////////////////////////////////
/// \brief enum type: the type of dict item
///
////////////////////////////////////////////////////////////////////////////////
typedef enum {
  STF_TYPE_BOOL,
  STF_TYPE_UNSIGNED_CHAR,
  STF_TYPE_SIGNED_CHAR,
  STF_TYPE_UNSIGNED_SHORT_INT,
  STF_TYPE_UNSIGNED_INT,
  STF_TYPE_UNSIGNED_LONG_INT,
  STF_TYPE_UNSIGNED_LONG_LONG_INT,
  STF_TYPE_SIGNED_SHORT_INT,
  STF_TYPE_SIGNED_INT,
  STF_TYPE_SIGNED_LONG_INT,
  STF_TYPE_SIGNED_LONG_LONG_INT,
  STF_TYPE_FLOAT,
  STF_TYPE_DOUBLE,
  STF_TYPE_LONG_DOUBLE,
  STF_TYPE_STRING,
  STF_TYPE_DICT
} STF_TYPE;

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

////////////////////////////////////////////////////////////////////////////////
/// \brief Delete a dict
///
/// \param dict The dict to delete
///
////////////////////////////////////////////////////////////////////////////////
#define STF_DELETE_DICT(dict) \
  STF_DICT_CLEAR(dict); \
  free(dict); \
  dict = NULL;

////////////////////////////////////////////////////////////////////////////////
/// \brief Add an item to a dict, in case of key exists then update the value
///
/// \param dict The dict to add to
/// \param k    The key/property of the kv object to add
/// \param v    The value of the kv object to add
///
////////////////////////////////////////////////////////////////////////////////
#define STF_DICT_ADD(dict, k, v) STF_DICT_UPDATE(dict, k, v) || _Generic((v), \
  bool: _STF_DICT_ADD_BOOL, \
  unsigned char: _STF_DICT_ADD_UNSIGNED_CHAR, \
  signed char: _STF_DICT_ADD_SIGNED_CHAR, \
  unsigned short int: _STF_DICT_ADD_UNSIGNED_SHORT_INT, \
  unsigned int: _STF_DICT_ADD_UNSIGNED_INT, \
  unsigned long int: _STF_DICT_ADD_UNSIGNED_LONG_INT, \
  unsigned long long int: _STF_DICT_ADD_UNSIGNED_LONG_LONG_INT, \
  signed short int: _STF_DICT_ADD_SIGNED_SHORT_INT, \
  signed int: _STF_DICT_ADD_SIGNED_INT, \
  signed long int: _STF_DICT_ADD_SIGNED_LONG_INT, \
  signed long long int: _STF_DICT_ADD_SIGNED_LONG_LONG_INT, \
  float: _STF_DICT_ADD_FLOAT, \
  double: _STF_DICT_ADD_DOUBLE, \
  long double: _STF_DICT_ADD_LONG_DOUBLE, \
  char *: _STF_DICT_ADD_STRING, \
  STF_DICT *: _STF_DICT_ADD_DICT, \
  default: _STF_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

////////////////////////////////////////////////////////////////////////////////
/// \brief Update an item in a dict
///
/// \param dict The dict to update in
/// \param k    The key/property of the item to update
/// \param v    The value of the item to set to
///
////////////////////////////////////////////////////////////////////////////////
#define STF_DICT_UPDATE(dict, k, v) _Generic((v), \
  bool: _STF_DICT_UPDATE_BOOL, \
  unsigned char: _STF_DICT_UPDATE_UNSIGNED_CHAR, \
  signed char: _STF_DICT_UPDATE_SIGNED_CHAR, \
  unsigned short int: _STF_DICT_UPDATE_UNSIGNED_SHORT_INT, \
  unsigned int: _STF_DICT_UPDATE_UNSIGNED_INT, \
  unsigned long int: _STF_DICT_UPDATE_UNSIGNED_LONG_INT, \
  unsigned long long int: _STF_DICT_UPDATE_UNSIGNED_LONG_LONG_INT, \
  signed short int: _STF_DICT_UPDATE_SIGNED_SHORT_INT, \
  signed int: _STF_DICT_UPDATE_SIGNED_INT, \
  signed long int: _STF_DICT_UPDATE_SIGNED_LONG_INT, \
  signed long long int: _STF_DICT_UPDATE_SIGNED_LONG_LONG_INT, \
  float: _STF_DICT_UPDATE_FLOAT, \
  double: _STF_DICT_UPDATE_DOUBLE, \
  long double: _STF_DICT_UPDATE_LONG_DOUBLE, \
  char *: _STF_DICT_UPDATE_STRING, \
  STF_DICT *: _STF_DICT_UPDATE_DICT, \
  default: _STF_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_PRIMITIVE(char *k, void *nvp, STF_TYPE t);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_BOOL(char *k, bool v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_CHAR(char *k, unsigned char v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_CHAR(char *k, signed char v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(char *k, unsigned short int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_INT(char *k, unsigned int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_INT(char *k, unsigned long int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(char *k, unsigned long long int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_SHORT_INT(char *k, signed short int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_INT(char *k, signed int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_LONG_INT(char *k, signed long int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(char *k, signed long long int v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_FLOAT(char *k, float v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_DOUBLE(char *k, double v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_LONG_DOUBLE(char *k, long double v);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_STRING(char *k, char *s);
bool _STF_ERROR_UNSUPPORTED_TYPE(STF_DICT *dict, char *k, void *v, char *src);
static void _STF_DICT_ITEM_PRINT(STF_DICT_ITEM *kv, int level, bool printType);
static void _STF_DELETE_KV(STF_DICT_ITEM *kv);
STF_DICT * STF_DICT_CREATE();
bool STF_DICT_ADD_KV(STF_DICT *dict, STF_DICT_ITEM *kv);
bool _STF_DICT_ADD_BOOL(STF_DICT *dict, char *k, bool v, char *src);
bool _STF_DICT_ADD_UNSIGNED_CHAR(STF_DICT *dict, char *k, unsigned char v, char *src);
bool _STF_DICT_ADD_SIGNED_CHAR(STF_DICT *dict, char *k, signed char v, char *src);
bool _STF_DICT_ADD_UNSIGNED_SHORT_INT(STF_DICT *dict, char *k, unsigned short int v, char *src);
bool _STF_DICT_ADD_UNSIGNED_INT(STF_DICT *dict, char *k, unsigned int v, char *src);
bool _STF_DICT_ADD_UNSIGNED_LONG_INT(STF_DICT *dict, char *k, unsigned long int v, char *src);
bool _STF_DICT_ADD_UNSIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, unsigned long long int v, char *src);
bool _STF_DICT_ADD_SIGNED_SHORT_INT(STF_DICT *dict, char *k, signed short int v, char *src);
bool _STF_DICT_ADD_SIGNED_INT(STF_DICT *dict, char *k, signed int v, char *src);
bool _STF_DICT_ADD_SIGNED_LONG_INT(STF_DICT *dict, char *k, signed long int v, char *src);
bool _STF_DICT_ADD_SIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, signed long long int v, char *src);
bool _STF_DICT_ADD_FLOAT(STF_DICT *dict, char *k, float v, char *src);
bool _STF_DICT_ADD_DOUBLE(STF_DICT *dict, char *k, double v, char *src);
bool _STF_DICT_ADD_LONG_DOUBLE(STF_DICT *dict, char *k, long double v, char *src);
bool _STF_DICT_ADD_STRING(STF_DICT *dict, char *k, char* v, char *src);
static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_DICT(char *k, STF_DICT *newDict);
bool _STF_DICT_ADD_DICT(STF_DICT *dict, char *k, STF_DICT *newDict, char *src);
static STF_DICT_ITEM * _STF_DICT_ITEM_COPY(STF_DICT_ITEM *kv);
static void _STF_DICT_SHIFT(STF_DICT *dict);
void STF_DICT_CLEAR(STF_DICT *dict);
static void STF_PRINT_REPEAT(char * str, int times);
void STF_DICT_PRINTL(STF_DICT *dict, int level, bool printType);
void STF_DICT_PRINT(STF_DICT *dict);
void STF_DICT_PRINTD(STF_DICT *dict);
void * STF_DICT_GET(STF_DICT *dict, char *k);
bool STF_DICT_INCLUDES(STF_DICT *dict, char *k);
STF_DICT * STF_DICT_COPY(STF_DICT *dict);
void * STF_DICT_FOREACH(STF_DICT *dict, void* (*cb)(STF_DICT_ITEM *, int));
static bool _STF_DICT_UPDATE_PRIMITIVE(STF_DICT *dict, char *k, void *nvp, STF_TYPE t);
bool _STF_DICT_UPDATE_BOOL(STF_DICT *dict, char *k, bool v, char *src);
bool _STF_DICT_UPDATE_UNSIGNED_CHAR(STF_DICT *dict, char *k, unsigned char v, char *src);
bool _STF_DICT_UPDATE_SIGNED_CHAR(STF_DICT *dict, char *k, signed char v, char *src);
bool _STF_DICT_UPDATE_UNSIGNED_SHORT_INT(STF_DICT *dict, char *k, unsigned short int v, char *src);
bool _STF_DICT_UPDATE_UNSIGNED_INT(STF_DICT *dict, char *k, unsigned int v, char *src);
bool _STF_DICT_UPDATE_UNSIGNED_LONG_INT(STF_DICT *dict, char *k, unsigned long int v, char *src);
bool _STF_DICT_UPDATE_UNSIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, unsigned long long int v, char *src);
bool _STF_DICT_UPDATE_SIGNED_SHORT_INT(STF_DICT *dict, char *k, signed short int v, char *src);
bool _STF_DICT_UPDATE_SIGNED_INT(STF_DICT *dict, char *k, signed int v, char *src);
bool _STF_DICT_UPDATE_SIGNED_LONG_INT(STF_DICT *dict, char *k, signed long int v, char *src);
bool _STF_DICT_UPDATE_SIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, signed long long int v, char *src);
bool _STF_DICT_UPDATE_FLOAT(STF_DICT *dict, char *k, float v, char *src);
bool _STF_DICT_UPDATE_DOUBLE(STF_DICT *dict, char *k, double v, char *src);
bool _STF_DICT_UPDATE_LONG_DOUBLE(STF_DICT *dict, char *k, long double v, char *src);
bool _STF_DICT_UPDATE_STRING(STF_DICT *dict, char *k, char* v, char *src);
bool _STF_DICT_UPDATE_DICT(STF_DICT *dict, char *k, STF_DICT *newDict, char *src);
bool STF_DICT_REMOVE(STF_DICT *dict, char *k);

  #endif //STF_DICT_H
#endif