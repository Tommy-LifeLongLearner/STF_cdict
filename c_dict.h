////////////////////////////////////////////////////////////////////////////////
//
// C_Dict - simple library to create and manipulate dictionaries
// Copyright (C) 2022 Saadi Toumi Fouad (saaditoumifouad@gmail.com)
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
  #error "This library is for c, not meant to be used with c++!";
#else
  #ifndef DICT_H
  #define DICT_H

////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

// PRINTC
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
// end of PRINTC

////////////////////////////////////////////////////////////////////////////////
/// \brief enum type: the type of dict item
///
////////////////////////////////////////////////////////////////////////////////
typedef enum {
  VALUE_TYPE_NULL,
  VALUE_TYPE_BOOL,
  VALUE_TYPE_UNSIGNED_CHAR,
  VALUE_TYPE_SIGNED_CHAR,
  VALUE_TYPE_UNSIGNED_SHORT_INT,
  VALUE_TYPE_UNSIGNED_INT,
  VALUE_TYPE_UNSIGNED_LONG_INT,
  VALUE_TYPE_UNSIGNED_LONG_LONG_INT,
  VALUE_TYPE_SIGNED_SHORT_INT,
  VALUE_TYPE_SIGNED_INT,
  VALUE_TYPE_SIGNED_LONG_INT,
  VALUE_TYPE_SIGNED_LONG_LONG_INT,
  VALUE_TYPE_FLOAT,
  VALUE_TYPE_DOUBLE,
  VALUE_TYPE_LONG_DOUBLE,
  VALUE_TYPE_STRING,
  VALUE_TYPE_DICT
} VALUE_TYPE;

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

////////////////////////////////////////////////////////////////////////////////
/// \brief Delete a dict
///
/// \param dict The dict to delete
///
////////////////////////////////////////////////////////////////////////////////
#define DICT_DELETE(dict) \
  DICT_CLEAR(dict); \
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
#define DICT_ADD(dict, k, v) DICT_UPDATE(dict, k, v) || _Generic((v), \
  bool: _DICT_ADD_BOOL, \
  unsigned char: _DICT_ADD_UNSIGNED_CHAR, \
  signed char: _DICT_ADD_SIGNED_CHAR, \
  unsigned short int: _DICT_ADD_UNSIGNED_SHORT_INT, \
  unsigned int: _DICT_ADD_UNSIGNED_INT, \
  unsigned long int: _DICT_ADD_UNSIGNED_LONG_INT, \
  unsigned long long int: _DICT_ADD_UNSIGNED_LONG_LONG_INT, \
  signed short int: _DICT_ADD_SIGNED_SHORT_INT, \
  signed int: _DICT_ADD_SIGNED_INT, \
  signed long int: _DICT_ADD_SIGNED_LONG_INT, \
  signed long long int: _DICT_ADD_SIGNED_LONG_LONG_INT, \
  float: _DICT_ADD_FLOAT, \
  double: _DICT_ADD_DOUBLE, \
  long double: _DICT_ADD_LONG_DOUBLE, \
  char *: _DICT_ADD_STRING, \
  DICT *: _DICT_ADD_DICT, \
  default: _DICT_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

////////////////////////////////////////////////////////////////////////////////
/// \brief Update an item in a dict
///
/// \param dict The dict to update in
/// \param k    The key/property of the item to update
/// \param v    The value of the item to set to
///
////////////////////////////////////////////////////////////////////////////////
#define DICT_UPDATE(dict, k, v) _Generic((v), \
  bool: _DICT_UPDATE_BOOL, \
  unsigned char: _DICT_UPDATE_UNSIGNED_CHAR, \
  signed char: _DICT_UPDATE_SIGNED_CHAR, \
  unsigned short int: _DICT_UPDATE_UNSIGNED_SHORT_INT, \
  unsigned int: _DICT_UPDATE_UNSIGNED_INT, \
  unsigned long int: _DICT_UPDATE_UNSIGNED_LONG_INT, \
  unsigned long long int: _DICT_UPDATE_UNSIGNED_LONG_LONG_INT, \
  signed short int: _DICT_UPDATE_SIGNED_SHORT_INT, \
  signed int: _DICT_UPDATE_SIGNED_INT, \
  signed long int: _DICT_UPDATE_SIGNED_LONG_INT, \
  signed long long int: _DICT_UPDATE_SIGNED_LONG_LONG_INT, \
  float: _DICT_UPDATE_FLOAT, \
  double: _DICT_UPDATE_DOUBLE, \
  long double: _DICT_UPDATE_LONG_DOUBLE, \
  char *: _DICT_UPDATE_STRING, \
  DICT *: _DICT_UPDATE_DICT, \
  default: _DICT_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

static DICT_ITEM * _DICT_ITEM_CREATE_PRIMITIVE(char *k, void *nvp, VALUE_TYPE t);
static DICT_ITEM * _DICT_ITEM_CREATE_BOOL(char *k, bool v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_CHAR(char *k, unsigned char v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_CHAR(char *k, signed char v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(char *k, unsigned short int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_INT(char *k, unsigned int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_INT(char *k, unsigned long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(char *k, unsigned long long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_SHORT_INT(char *k, signed short int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_INT(char *k, signed int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_INT(char *k, signed long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(char *k, signed long long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_FLOAT(char *k, float v);
static DICT_ITEM * _DICT_ITEM_CREATE_DOUBLE(char *k, double v);
static DICT_ITEM * _DICT_ITEM_CREATE_LONG_DOUBLE(char *k, long double v);
static DICT_ITEM * _DICT_ITEM_CREATE_STRING(char *k, char *s);
bool _DICT_ERROR_UNSUPPORTED_TYPE(DICT *dict, char *k, void *v, char *src);
static void _DICT_ITEM_PRINT(DICT_ITEM *kv, int level, bool printType);
static void _DELETE_KV(DICT_ITEM *kv);
DICT * DICT_CREATE();
bool DICT_ADD_KV(DICT *dict, DICT_ITEM *kv);
bool _DICT_ADD_NULL(DICT *dict, char *k, void* v, char *src);
bool _DICT_ADD_BOOL(DICT *dict, char *k, bool v, char *src);
bool _DICT_ADD_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src);
bool _DICT_ADD_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src);
bool _DICT_ADD_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src);
bool _DICT_ADD_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src);
bool _DICT_ADD_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src);
bool _DICT_ADD_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src);
bool _DICT_ADD_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src);
bool _DICT_ADD_SIGNED_INT(DICT *dict, char *k, signed int v, char *src);
bool _DICT_ADD_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src);
bool _DICT_ADD_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src);
bool _DICT_ADD_FLOAT(DICT *dict, char *k, float v, char *src);
bool _DICT_ADD_DOUBLE(DICT *dict, char *k, double v, char *src);
bool _DICT_ADD_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src);
bool _DICT_ADD_STRING(DICT *dict, char *k, char* v, char *src);
static DICT_ITEM * _DICT_ITEM_CREATE_DICT(char *k, DICT *newDict);
bool _DICT_ADD_DICT(DICT *dict, char *k, DICT *newDict, char *src);
static DICT_ITEM * _DICT_ITEM_COPY(DICT_ITEM *kv);
static void _DICT_SHIFT(DICT *dict);
void DICT_CLEAR(DICT *dict);
static void PRINT_REPEAT(char * str, int times);
void DICT_PRINTL(DICT *dict, int level, bool printType);
void DICT_PRINT(DICT *dict);
void DICT_PRINTD(DICT *dict);
void * DICT_GET(DICT *dict, char *k);
bool DICT_INCLUDES(DICT *dict, char *k);
DICT * DICT_COPY(DICT *dict);
void * DICT_FOREACH(DICT *dict, void* (*cb)(DICT_ITEM *, int));
static bool _DICT_UPDATE_PRIMITIVE(DICT *dict, char *k, void *nvp, VALUE_TYPE t);
bool _DICT_UPDATE_NULL(DICT *dict, char *k, void *v, char *src);
bool _DICT_UPDATE_BOOL(DICT *dict, char *k, bool v, char *src);
bool _DICT_UPDATE_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src);
bool _DICT_UPDATE_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src);
bool _DICT_UPDATE_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src);
bool _DICT_UPDATE_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src);
bool _DICT_UPDATE_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src);
bool _DICT_UPDATE_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src);
bool _DICT_UPDATE_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src);
bool _DICT_UPDATE_SIGNED_INT(DICT *dict, char *k, signed int v, char *src);
bool _DICT_UPDATE_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src);
bool _DICT_UPDATE_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src);
bool _DICT_UPDATE_FLOAT(DICT *dict, char *k, float v, char *src);
bool _DICT_UPDATE_DOUBLE(DICT *dict, char *k, double v, char *src);
bool _DICT_UPDATE_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src);
bool _DICT_UPDATE_STRING(DICT *dict, char *k, char* v, char *src);
bool _DICT_UPDATE_DICT(DICT *dict, char *k, DICT *newDict, char *src);
bool DICT_REMOVE(DICT *dict, char *k);

  #endif //DICT_H
#endif