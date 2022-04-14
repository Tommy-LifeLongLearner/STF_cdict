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
  #define __USE_MINGW_ANSI_STDIO 1

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
  VALUE_TYPE_DICT,
  VALUE_TYPE_LIST
} VALUE_TYPE;

////////////////////////////////////////////////////////////////////////////////
/// \brief item class holds the `type` of the item, the `value`, the property
/// name as `key` and the address of the next pair as (DICT_ITEM)
///
////////////////////////////////////////////////////////////////////////////////
typedef struct DICT_ITEM {
  VALUE_TYPE type;
  char *key;
  void *value;
  struct DICT_ITEM *next;
} DICT_ITEM;

////////////////////////////////////////////////////////////////////////////////
/// \brief item class holds the `type` of the item, the `value` and the address 
/// of the next pair as (LIST_ITEM)
///
////////////////////////////////////////////////////////////////////////////////
typedef struct LIST_ITEM {
  VALUE_TYPE type;
  void *value;
  struct LIST_ITEM *next;
} LIST_ITEM;

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
/// \brief list class(linked list of items) with the first and
/// last item as `start`, `end` and the number of items as `size`
///
////////////////////////////////////////////////////////////////////////////////
typedef struct {
  LIST_ITEM *start;
  LIST_ITEM *end;
  int size;
} LIST;

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
/// \brief Delete a list
///
/// \param list The list to delete
///
////////////////////////////////////////////////////////////////////////////////
#define LIST_DELETE(list) \
  LIST_CLEAR(list); \
  free(list); \
  list = NULL;

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
  LIST *: _DICT_ADD_LIST, \
  default: _DICT_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

////////////////////////////////////////////////////////////////////////////////
/// \brief Add an item to a list
///
/// \param list The list to add to
/// \param v    The value to add as an item
///
////////////////////////////////////////////////////////////////////////////////
#define LIST_ADD(list, v) _Generic((v), \
  bool: _LIST_ADD_BOOL, \
  unsigned char: _LIST_ADD_UNSIGNED_CHAR, \
  signed char: _LIST_ADD_SIGNED_CHAR, \
  unsigned short int: _LIST_ADD_UNSIGNED_SHORT_INT, \
  unsigned int: _LIST_ADD_UNSIGNED_INT, \
  unsigned long int: _LIST_ADD_UNSIGNED_LONG_INT, \
  unsigned long long int: _LIST_ADD_UNSIGNED_LONG_LONG_INT, \
  signed short int: _LIST_ADD_SIGNED_SHORT_INT, \
  signed int: _LIST_ADD_SIGNED_INT, \
  signed long int: _LIST_ADD_SIGNED_LONG_INT, \
  signed long long int: _LIST_ADD_SIGNED_LONG_LONG_INT, \
  float: _LIST_ADD_FLOAT, \
  double: _LIST_ADD_DOUBLE, \
  long double: _LIST_ADD_LONG_DOUBLE, \
  char *: _LIST_ADD_STRING, \
  LIST *: _LIST_ADD_LIST, \
  DICT *: _LIST_ADD_DICT, \
  default: _LIST_ADD_ERROR_UNSUPPORTED_TYPE)(list, v, #v)

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
  LIST *: _DICT_UPDATE_LIST, \
  default: _DICT_ERROR_UNSUPPORTED_TYPE)(dict, k, v, #v)

////////////////////////////////////////////////////////////////////////////////
/// \brief Update an item in a list
///
/// \param list The list to update in
/// \param v    The index of the item to update
///
////////////////////////////////////////////////////////////////////////////////
#define LIST_UPDATE(list, index, v) _Generic((v), \
  bool: _LIST_UPDATE_BOOL, \
  unsigned char: _LIST_UPDATE_UNSIGNED_CHAR, \
  signed char: _LIST_UPDATE_SIGNED_CHAR, \
  unsigned short int: _LIST_UPDATE_UNSIGNED_SHORT_INT, \
  unsigned int: _LIST_UPDATE_UNSIGNED_INT, \
  unsigned long int: _LIST_UPDATE_UNSIGNED_LONG_INT, \
  unsigned long long int: _LIST_UPDATE_UNSIGNED_LONG_LONG_INT, \
  signed short int: _LIST_UPDATE_SIGNED_SHORT_INT, \
  signed int: _LIST_UPDATE_SIGNED_INT, \
  signed long int: _LIST_UPDATE_SIGNED_LONG_INT, \
  signed long long int: _LIST_UPDATE_SIGNED_LONG_LONG_INT, \
  float: _LIST_UPDATE_FLOAT, \
  double: _LIST_UPDATE_DOUBLE, \
  long double: _LIST_UPDATE_LONG_DOUBLE, \
  char *: _LIST_UPDATE_STRING, \
  LIST *: _LIST_UPDATE_LIST, \
  DICT *: _LIST_UPDATE_DICT, \
  default: _LIST_UPDATE_ERROR_UNSUPPORTED_TYPE)(list, index, v, #v)

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if an item exists in a list
///
/// \param list The list to check in
/// \param v    The value of the item to check
///
////////////////////////////////////////////////////////////////////////////////
#define LIST_INCLUDES(list, v) _Generic((v), \
  bool: _LIST_INCLUDES_BOOL, \
  unsigned char: _LIST_INCLUDES_UNSIGNED_CHAR, \
  signed char: _LIST_INCLUDES_SIGNED_CHAR, \
  unsigned short int: _LIST_INCLUDES_UNSIGNED_SHORT_INT, \
  unsigned int: _LIST_INCLUDES_UNSIGNED_INT, \
  unsigned long int: _LIST_INCLUDES_UNSIGNED_LONG_INT, \
  unsigned long long int: _LIST_INCLUDES_UNSIGNED_LONG_LONG_INT, \
  signed short int: _LIST_INCLUDES_SIGNED_SHORT_INT, \
  signed int: _LIST_INCLUDES_SIGNED_INT, \
  signed long int: _LIST_INCLUDES_SIGNED_LONG_INT, \
  signed long long int: _LIST_INCLUDES_SIGNED_LONG_LONG_INT, \
  float: _LIST_INCLUDES_FLOAT, \
  double: _LIST_INCLUDES_DOUBLE, \
  long double: _LIST_INCLUDES_LONG_DOUBLE, \
  char *: _LIST_INCLUDES_STRING, \
  default: _LIST_INCLUDES_ERROR_UNSUPPORTED_TYPE)(list, v, #v)

static DICT_ITEM * _DICT_ITEM_CREATE_PRIMITIVE(char *k, void *nvp, VALUE_TYPE t);
static LIST_ITEM * _LIST_ITEM_CREATE_PRIMITIVE(void *nvp, VALUE_TYPE t);
static DICT_ITEM * _DICT_ITEM_CREATE_BOOL(char *k, bool v);
static LIST_ITEM * _LIST_ITEM_CREATE_BOOL(bool v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_CHAR(char *k, unsigned char v);
static LIST_ITEM * _LIST_ITEM_CREATE_UNSIGNED_CHAR(unsigned char v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_CHAR(char *k, signed char v);
static LIST_ITEM * _LIST_ITEM_CREATE_SIGNED_CHAR(signed char v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(char *k, unsigned short int v);
static LIST_ITEM * _LIST_ITEM_CREATE_UNSIGNED_SHORT_INT(unsigned short int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_INT(char *k, unsigned int v);
static LIST_ITEM * _LIST_ITEM_CREATE_UNSIGNED_INT(unsigned int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_INT(char *k, unsigned long int v);
static LIST_ITEM * _LIST_ITEM_CREATE_UNSIGNED_LONG_INT(unsigned long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(char *k, unsigned long long int v);
static LIST_ITEM * _LIST_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(unsigned long long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_SHORT_INT(char *k, signed short int v);
static LIST_ITEM * _LIST_ITEM_CREATE_SIGNED_SHORT_INT(signed short int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_INT(char *k, signed int v);
static LIST_ITEM * _LIST_ITEM_CREATE_SIGNED_INT(signed int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_INT(char *k, signed long int v);
static LIST_ITEM * _LIST_ITEM_CREATE_SIGNED_LONG_INT(signed long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(char *k, signed long long int v);
static LIST_ITEM * _LIST_ITEM_CREATE_SIGNED_LONG_LONG_INT(signed long long int v);
static DICT_ITEM * _DICT_ITEM_CREATE_FLOAT(char *k, float v);
static LIST_ITEM * _LIST_ITEM_CREATE_FLOAT(float v);
static DICT_ITEM * _DICT_ITEM_CREATE_DOUBLE(char *k, double v);
static LIST_ITEM * _LIST_ITEM_CREATE_DOUBLE(double v);
static DICT_ITEM * _DICT_ITEM_CREATE_LONG_DOUBLE(char *k, long double v);
static LIST_ITEM * _LIST_ITEM_CREATE_LONG_DOUBLE(long double v);
static DICT_ITEM * _DICT_ITEM_CREATE_STRING(char *k, char *s);
static LIST_ITEM * _LIST_ITEM_CREATE_STRING(char *s);
bool _DICT_ERROR_UNSUPPORTED_TYPE(DICT *dict, char *k, void *v, char *src);
bool _LIST_ADD_ERROR_UNSUPPORTED_TYPE(LIST *list, void *v, char *src);
bool _LIST_UPDATE_ERROR_UNSUPPORTED_TYPE(LIST *list, int index, void *v, char *src);
static void _DICT_ITEM_PRINT(DICT_ITEM *kv, int level, bool printType);
static void _LIST_ITEM_PRINT(LIST_ITEM *item, int level, bool printType);
static void _DELETE_KV(DICT_ITEM *kv);
static void _DELETE_ITEM(LIST_ITEM *item);
DICT * DICT_CREATE();
LIST * LIST_CREATE();
bool DICT_ADD_KV(DICT *dict, DICT_ITEM *kv);
bool LIST_ADD_ITEM(LIST *list, LIST_ITEM *item);
bool _DICT_ADD_NULL(DICT *dict, char *k, void* v, char *src);
bool _LIST_ADD_NULL(LIST *list, void* v, char *src);
bool _DICT_ADD_BOOL(DICT *dict, char *k, bool v, char *src);
bool _LIST_ADD_BOOL(LIST *list, bool v, char *src);
bool _DICT_ADD_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src);
bool _LIST_ADD_UNSIGNED_CHAR(LIST *list, unsigned char v, char *src);
bool _DICT_ADD_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src);
bool _LIST_ADD_SIGNED_CHAR(LIST *list, signed char v, char *src);
bool _DICT_ADD_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src);
bool _LIST_ADD_UNSIGNED_SHORT_INT(LIST *list, unsigned short int v, char *src);
bool _DICT_ADD_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src);
bool _LIST_ADD_UNSIGNED_INT(LIST *list, unsigned int v, char *src);
bool _DICT_ADD_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src);
bool _LIST_ADD_UNSIGNED_LONG_INT(LIST *list, unsigned long int v, char *src);
bool _DICT_ADD_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src);
bool _LIST_ADD_UNSIGNED_LONG_LONG_INT(LIST *list, unsigned long long int v, char *src);
bool _DICT_ADD_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src);
bool _LIST_ADD_SIGNED_SHORT_INT(LIST *list, signed short int v, char *src);
bool _DICT_ADD_SIGNED_INT(DICT *dict, char *k, signed int v, char *src);
bool _LIST_ADD_SIGNED_INT(LIST *list, signed int v, char *src);
bool _DICT_ADD_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src);
bool _LIST_ADD_SIGNED_LONG_INT(LIST *list, signed long int v, char *src);
bool _DICT_ADD_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src);
bool _LIST_ADD_SIGNED_LONG_LONG_INT(LIST *list, signed long long int v, char *src);
bool _DICT_ADD_FLOAT(DICT *dict, char *k, float v, char *src);
bool _LIST_ADD_FLOAT(LIST *list, float v, char *src);
bool _DICT_ADD_DOUBLE(DICT *dict, char *k, double v, char *src);
bool _LIST_ADD_DOUBLE(LIST *list, double v, char *src);
bool _DICT_ADD_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src);
bool _LIST_ADD_LONG_DOUBLE(LIST *list, long double v, char *src);
bool _DICT_ADD_STRING(DICT *dict, char *k, char* v, char *src);
bool _LIST_ADD_STRING(LIST *list, char* v, char *src);
static DICT_ITEM * _DICT_ITEM_CREATE_DICT(char *k, DICT *newDict);
static DICT_ITEM * _DICT_ITEM_CREATE_LIST(char *k, LIST *newList);
static LIST_ITEM * _LIST_ITEM_CREATE_LIST(LIST *newList);
static LIST_ITEM * _LIST_ITEM_CREATE_DICT(DICT *newDict);
bool _DICT_ADD_DICT(DICT *dict, char *k, DICT *newDict, char *src);
bool _DICT_ADD_LIST(DICT *dict, char *k, LIST *newList, char *src);
bool _LIST_ADD_LIST(LIST *list, LIST *newList, char *src);
bool _LIST_ADD_DICT(LIST *list, DICT *dict, char *src);
static DICT_ITEM * _DICT_ITEM_COPY(DICT_ITEM *kv);
static LIST_ITEM * _LIST_ITEM_COPY(LIST_ITEM *item);
static void _DICT_SHIFT(DICT *dict);
static void _LIST_SHIFT(LIST *list);
void DICT_CLEAR(DICT *dict);
void LIST_CLEAR(LIST *list);
static void PRINT_REPEAT(char * str, int times);
void DICT_PRINTL(DICT *dict, int level, bool printType);
void LIST_PRINTL(LIST *list, int level, bool printType);
void DICT_PRINT(DICT *dict);
void LIST_PRINT(LIST *list);
void DICT_PRINTD(DICT *dict);
void LIST_PRINTD(LIST *list);
void * DICT_GET(DICT *dict, char *k);
void * LIST_GET(LIST *list, int index);
bool DICT_INCLUDES(DICT *dict, char *k);
static bool _LIST_INCLUDES_PRIMITIVE(LIST *list, void *nvp, VALUE_TYPE t);
bool _LIST_INCLUDES_BOOL(LIST *list, bool v, char *src);
bool _LIST_INCLUDES_NULL(LIST *list, void *v, char *src);
bool _LIST_INCLUDES_UNSIGNED_CHAR(LIST *list, unsigned char v, char *src);
bool _LIST_INCLUDES_SIGNED_CHAR(LIST *list, signed char v, char *src);
bool _LIST_INCLUDES_UNSIGNED_SHORT_INT(LIST *list, unsigned short int v, char *src);
bool _LIST_INCLUDES_UNSIGNED_INT(LIST *list, unsigned int v, char *src);
bool _LIST_INCLUDES_UNSIGNED_LONG_INT(LIST *list, unsigned long int v, char *src);
bool _LIST_INCLUDES_UNSIGNED_LONG_LONG_INT(LIST *list, unsigned long long int v, char *src);
bool _LIST_INCLUDES_SIGNED_SHORT_INT(LIST *list, signed short int v, char *src);
bool _LIST_INCLUDES_SIGNED_INT(LIST *list, signed int v, char *src);
bool _LIST_INCLUDES_SIGNED_LONG_INT(LIST *list, signed long int v, char *src);
bool _LIST_INCLUDES_SIGNED_LONG_LONG_INT(LIST *list, signed long long int v, char *src);
bool _LIST_INCLUDES_FLOAT(LIST *list, float v, char *src);
bool _LIST_INCLUDES_DOUBLE(LIST *list, double v, char *src);
bool _LIST_INCLUDES_LONG_DOUBLE(LIST *list, long double v, char *src);
bool _LIST_INCLUDES_STRING(LIST *list, char* v, char *src);
bool _LIST_INCLUDES_ERROR_UNSUPPORTED_TYPE(LIST *list, void *v, char *src);
DICT * DICT_COPY(DICT *dict);
LIST * LIST_COPY(LIST *list);
void * DICT_FOREACH(DICT *dict, void* (*cb)(DICT_ITEM *, int));
void * LIST_FOREACH(LIST *list, void* (*cb)(LIST_ITEM *, int));
static bool _DICT_UPDATE_PRIMITIVE(DICT *dict, char *k, void *nvp, VALUE_TYPE t);
static bool _LIST_UPDATE_PRIMITIVE(LIST *list, int index, void *nvp, VALUE_TYPE t);
bool _DICT_UPDATE_NULL(DICT *dict, char *k, void *v, char *src);
bool _LIST_UPDATE_NULL(LIST *list, int index, void *v, char *src);
bool _DICT_UPDATE_BOOL(DICT *dict, char *k, bool v, char *src);
bool _LIST_UPDATE_BOOL(LIST *list, int index, bool v, char *src);
bool _DICT_UPDATE_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src);
bool _LIST_UPDATE_UNSIGNED_CHAR(LIST *list, int index, unsigned char v, char *src);
bool _DICT_UPDATE_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src);
bool _LIST_UPDATE_SIGNED_CHAR(LIST *list, int index, signed char v, char *src);
bool _DICT_UPDATE_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src);
bool _LIST_UPDATE_UNSIGNED_SHORT_INT(LIST *list, int index, unsigned short int v, char *src);
bool _DICT_UPDATE_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src);
bool _LIST_UPDATE_UNSIGNED_INT(LIST *list, int index, unsigned int v, char *src);
bool _DICT_UPDATE_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src);
bool _LIST_UPDATE_UNSIGNED_LONG_INT(LIST *list, int index, unsigned long int v, char *src);
bool _DICT_UPDATE_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src);
bool _LIST_UPDATE_UNSIGNED_LONG_LONG_INT(LIST *list, int index, unsigned long long int v, char *src);
bool _DICT_UPDATE_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src);
bool _LIST_UPDATE_SIGNED_SHORT_INT(LIST *list, int index, signed short int v, char *src);
bool _DICT_UPDATE_SIGNED_INT(DICT *dict, char *k, signed int v, char *src);
bool _LIST_UPDATE_SIGNED_INT(LIST *list, int index, signed int v, char *src);
bool _DICT_UPDATE_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src);
bool _LIST_UPDATE_SIGNED_LONG_INT(LIST *list, int index, signed long int v, char *src);
bool _DICT_UPDATE_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src);
bool _LIST_UPDATE_SIGNED_LONG_LONG_INT(LIST *list, int index, signed long long int v, char *src);
bool _DICT_UPDATE_FLOAT(DICT *dict, char *k, float v, char *src);
bool _LIST_UPDATE_FLOAT(LIST *list, int index, float v, char *src);
bool _DICT_UPDATE_DOUBLE(DICT *dict, char *k, double v, char *src);
bool _LIST_UPDATE_DOUBLE(LIST *list, int index, double v, char *src);
bool _DICT_UPDATE_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src);
bool _LIST_UPDATE_LONG_DOUBLE(LIST *list, int index, long double v, char *src);
bool _DICT_UPDATE_STRING(DICT *dict, char *k, char* v, char *src);
bool _LIST_UPDATE_STRING(LIST *list, int index, char* v, char *src);
bool _DICT_UPDATE_DICT(DICT *dict, char *k, DICT *newDict, char *src);
bool _DICT_UPDATE_LIST(DICT *dict, char *k, LIST *newList, char *src);
bool _LIST_UPDATE_LIST(LIST *list, int index, LIST *newItem, char *src);
bool _LIST_UPDATE_DICT(LIST *list, int index, DICT *newDICT, char *src);
bool DICT_REMOVE(DICT *dict, char *k);
bool LIST_REMOVE(LIST *list, int index);

  #endif //DICT_H
#endif