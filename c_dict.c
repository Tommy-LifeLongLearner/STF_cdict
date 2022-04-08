#ifndef __cplusplus /////////////////////////////////////////////////////////////////////
#include "c_dict.h"

const char *C_TYPES[] = {"NULL", "BOOL", "UNSIGNED_CHAR", "SIGNED_CHAR", "UNSIGNED_SHORT_INT", "UNSIGNED_INT", "UNSIGNED_LONG_INT", "UNSIGNED_LONG_LONG_INT", "SIGNED_SHORT_INT", "SIGNED_INT", "SIGNED_LONG_INT", "SIGNED_LONG_LONG_INT", "FLOAT", "DOUBLE", "LONG_DOUBLE", "STRING", "DICT"};

void printc(int color, char *output, ...) {    
  va_list args;
  va_start(args, output);

  #if defined _WIN32 || defined _WIN64
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    // save the config
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
 
    SetConsoleTextAttribute(hConsole, color);
    vprintf(output, args);
    // restore the config
    SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes);
  #else
    switch(color) {
      case 0: printf("\033[30m"); break;
      case 1: printf("\033[1;33m"); break;
      case 2: printf("\033[1;31m"); break; 
      case 3: printf("\033[1;32m"); break; 
      case 4: printf("\033[1;34m"); break; 
      case 5: printf("\033[1;37m"); break;
    }
    vprintf(output, args);
  #endif
  va_end(args);
}

static DICT_ITEM * _DICT_ITEM_CREATE_PRIMITIVE(char *k, void *nvp, VALUE_TYPE t) {
  DICT_ITEM *kvNode = malloc(sizeof(DICT_ITEM));
  if(kvNode != NULL) {
    kvNode->value = nvp;
    kvNode->type = t;
    kvNode->key = k;
    kvNode->next = NULL;
  }
  return kvNode;
}

static DICT_ITEM * _DICT_ITEM_CREATE_BOOL(char *k, bool v) {
  bool *nvp = malloc(sizeof(bool));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_BOOL);
}

static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_CHAR(char *k, unsigned char v) {
  unsigned char *nvp = malloc(sizeof(unsigned char));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_UNSIGNED_CHAR);
}

static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_CHAR(char *k, signed char v) {
  signed char *nvp = malloc(sizeof(signed char));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_SIGNED_CHAR);
}

static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(char *k, unsigned short int v) {
  unsigned short int *nvp = malloc(sizeof(unsigned short int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_UNSIGNED_SHORT_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_INT(char *k, unsigned int v) {
  unsigned int *nvp = malloc(sizeof(unsigned int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_UNSIGNED_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_INT(char *k, unsigned long int v) {
  unsigned long int *nvp = malloc(sizeof(unsigned long int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_UNSIGNED_LONG_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(char *k, unsigned long long int v) {
  unsigned long long int *nvp = malloc(sizeof(unsigned long long int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_UNSIGNED_LONG_LONG_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_SHORT_INT(char *k, signed short int v) {
  signed short int *nvp = malloc(sizeof(signed short int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_SIGNED_SHORT_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_INT(char *k, signed int v) {
  signed int *nvp = malloc(sizeof(signed int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_SIGNED_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_INT(char *k, signed long int v) {
  signed long int *nvp = malloc(sizeof(signed long int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_SIGNED_LONG_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(char *k, signed long long int v) {
  signed long long int *nvp = malloc(sizeof(signed long long int));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_SIGNED_LONG_LONG_INT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_FLOAT(char *k, float v) {
  float *nvp = malloc(sizeof(float));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_FLOAT);
}

static DICT_ITEM * _DICT_ITEM_CREATE_DOUBLE(char *k, double v) {
  double *nvp = malloc(sizeof(double));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_DOUBLE);
}

static DICT_ITEM * _DICT_ITEM_CREATE_LONG_DOUBLE(char *k, long double v) {
  long double *nvp = malloc(sizeof(long double));
  *nvp = v;
  return _DICT_ITEM_CREATE_PRIMITIVE(k, nvp, VALUE_TYPE_LONG_DOUBLE);
}

static DICT_ITEM * _DICT_ITEM_CREATE_STRING(char *k, char *s) {
  DICT_ITEM *p = malloc(sizeof(DICT_ITEM));
  if(p != NULL) {
    char *sc;
    if(s != NULL) {
      sc = malloc(strlen(s) + 1);
      if(sc != NULL) {
        strcpy(sc, s);
        sc[strlen(s)] = '\0';
      }
    }
    p->value = (void *)sc;
    p->type = VALUE_TYPE_STRING;
    p->key = k;
    p->next = NULL;
  }
  return p;
}

static void _DICT_ITEM_PRINT(DICT_ITEM *kv, int level, bool printType) {
  PRINT_REPEAT("  ", level + 1);
  if(kv != NULL) {
    if(kv->value == NULL && kv->type != VALUE_TYPE_NULL) {
      printc(GREEN, "\"%s\": ", kv->key);
      printc(RED, "NULL");
    }else {
      if(printType) {
        printc(YELLOW, "(%s) ", C_TYPES[kv->type]);
      }
      printc(GREEN, "\"%s\": ", kv->key);
      switch(kv->type) {
        case VALUE_TYPE_NULL: printc(RED, "NULL"); break;
        case VALUE_TYPE_BOOL: printc(RED, "%s", *((bool *)(kv->value)) ? "true" : "false"); break;
        case VALUE_TYPE_UNSIGNED_CHAR: printc(YELLOW, "'%c'", *((unsigned char *)(kv->value))); break;
        case VALUE_TYPE_SIGNED_CHAR: printc(YELLOW, "'%c'", *((signed char *)(kv->value))); break;
        case VALUE_TYPE_UNSIGNED_SHORT_INT: printc(BLUE, "%d", *((unsigned short int *)(kv->value))); break;
        case VALUE_TYPE_UNSIGNED_INT: printc(BLUE, "%u", *((unsigned int *)(kv->value))); break;
        case VALUE_TYPE_UNSIGNED_LONG_INT: printc(BLUE, "%lu", *((unsigned long int *)(kv->value))); break;
        case VALUE_TYPE_UNSIGNED_LONG_LONG_INT: printc(BLUE, "%llu", *((unsigned long long int *)(kv->value))); break;
        case VALUE_TYPE_SIGNED_SHORT_INT: printc(BLUE, "%d", *((signed short int *)(kv->value))); break;
        case VALUE_TYPE_SIGNED_INT: printc(BLUE, "%d", *((signed int *)(kv->value))); break;
        case VALUE_TYPE_SIGNED_LONG_INT: printc(BLUE, "%ld", *((signed long int *)(kv->value))); break;
        case VALUE_TYPE_SIGNED_LONG_LONG_INT: printc(BLUE, "%lld", *((signed long long int *)(kv->value))); break;
        case VALUE_TYPE_FLOAT: printc(BLUE, "%f", *((float *)(kv->value))); break;
        case VALUE_TYPE_DOUBLE: printc(BLUE, "%lf", *((double *)(kv->value))); break;
        case VALUE_TYPE_LONG_DOUBLE: printc(BLUE, "%Lf", *((long double *)(kv->value))); break;
        case VALUE_TYPE_STRING: printc(GREEN, "\"%s\"", (char *)(kv->value)); break;
        case VALUE_TYPE_DICT: DICT_PRINTL((DICT *)(kv->value), level + 1, printType); break;
      }
    }
  }else {
    printc(RED, "NULL");
  }
}

static void _DELETE_KV(DICT_ITEM *kv) {
  if(kv->value != NULL) {
    if(kv->type == VALUE_TYPE_DICT) {
      DICT_CLEAR((DICT *)(kv->value));
    }
    free(kv->value);
  }
  free(kv);
}

DICT * DICT_CREATE() {
  DICT *dict = malloc(sizeof(DICT));
  if(dict != NULL) {
    dict->start = dict->end = NULL;
    dict->size = 0;
  }
  return dict;
}

bool DICT_ADD_KV(DICT *dict, DICT_ITEM *kv) {
  if(dict == NULL || kv == NULL) return false;
  if(dict->size == 0) {
    dict->start = dict->end = kv;
  }else if(dict->size == 1) {
    dict->start->next = dict->end = kv;
  }else {
    dict->end->next = kv;
    dict->end = dict->end->next;
  }
  dict->size++;
  return true;
}

bool _DICT_ADD_NULL(DICT *dict, char *k, void* v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_PRIMITIVE(k, v, VALUE_TYPE_NULL));
}

bool _DICT_ADD_BOOL(DICT *dict, char *k, bool v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_BOOL(k, v));
}

bool _DICT_ADD_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_CHAR(k, v));
}

bool _DICT_ADD_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_SIGNED_CHAR(k, v));
}

bool _DICT_ADD_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(k, v));
}

bool _DICT_ADD_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_INT(k, v));
}

bool _DICT_ADD_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_LONG_INT(k, v));
}

bool _DICT_ADD_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(k, v));
}

bool _DICT_ADD_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_SIGNED_SHORT_INT(k, v));
}

bool _DICT_ADD_SIGNED_INT(DICT *dict, char *k, signed int v, char *src) {
  if(strlen(src) == 3 && src[0] == '\'' && src[2] == '\'') {
    return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_UNSIGNED_CHAR(k, v));
  }else if(strcmp(src, "false") == 0 || strcmp(src, "true") == 0) {
    return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_BOOL(k, v));
  }
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_SIGNED_INT(k, v));
}

bool _DICT_ADD_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_SIGNED_LONG_INT(k, v));
}

bool _DICT_ADD_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(k, v));
}

bool _DICT_ADD_FLOAT(DICT *dict, char *k, float v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_FLOAT(k, v));
}

bool _DICT_ADD_DOUBLE(DICT *dict, char *k, double v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_DOUBLE(k, v));
}

bool _DICT_ADD_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_LONG_DOUBLE(k, v));
}

bool _DICT_ADD_STRING(DICT *dict, char *k, char* v, char *src) {
  return DICT_ADD_KV(dict, _DICT_ITEM_CREATE_STRING(k, v));
}

static DICT_ITEM * _DICT_ITEM_CREATE_DICT(char *k, DICT *newDict) {
  DICT_ITEM *p = malloc(sizeof(DICT_ITEM));
  if(p != NULL) {
    p->value = newDict;
    p->type = VALUE_TYPE_DICT;
    p->key = k;
    p->next = NULL;
  }
  return p;
}

bool _DICT_ADD_DICT(DICT *dict, char *k, DICT *newDict, char *src) {
  return newDict && DICT_ADD_KV(dict, _DICT_ITEM_CREATE_DICT(k, newDict));
}

static DICT_ITEM * _DICT_ITEM_COPY(DICT_ITEM *kv) {
  if(kv == NULL) return NULL;
  if(kv->value == NULL) {
    return _DICT_ITEM_CREATE_PRIMITIVE(kv->key, NULL, kv->type);
  }
  DICT_ITEM *kvCopy;
  switch(kv->type) {
    case VALUE_TYPE_BOOL: kvCopy = _DICT_ITEM_CREATE_BOOL(kv->key, *((bool *)(kv->value))); break;
    case VALUE_TYPE_UNSIGNED_CHAR: kvCopy = _DICT_ITEM_CREATE_UNSIGNED_CHAR(kv->key, *((unsigned char *)(kv->value))); break;
    case VALUE_TYPE_SIGNED_CHAR: kvCopy = _DICT_ITEM_CREATE_SIGNED_CHAR(kv->key, *((signed char *)(kv->value))); break;
    case VALUE_TYPE_UNSIGNED_SHORT_INT: kvCopy = _DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(kv->key, *((unsigned short int *)(kv->value))); break;
    case VALUE_TYPE_UNSIGNED_INT: kvCopy = _DICT_ITEM_CREATE_UNSIGNED_INT(kv->key, *((unsigned int *)(kv->value))); break;
    case VALUE_TYPE_UNSIGNED_LONG_INT: kvCopy = _DICT_ITEM_CREATE_UNSIGNED_LONG_INT(kv->key, *((unsigned long int *)(kv->value))); break;
    case VALUE_TYPE_UNSIGNED_LONG_LONG_INT: kvCopy = _DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(kv->key, *((unsigned long long int *)(kv->value))); break;
    case VALUE_TYPE_SIGNED_SHORT_INT: kvCopy = _DICT_ITEM_CREATE_SIGNED_SHORT_INT(kv->key, *((signed short int *)(kv->value))); break;
    case VALUE_TYPE_SIGNED_INT: kvCopy = _DICT_ITEM_CREATE_SIGNED_INT(kv->key, *((signed int *)(kv->value))); break;
    case VALUE_TYPE_SIGNED_LONG_INT: kvCopy = _DICT_ITEM_CREATE_SIGNED_LONG_INT(kv->key, *((signed long int *)(kv->value))); break;
    case VALUE_TYPE_SIGNED_LONG_LONG_INT: kvCopy = _DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(kv->key, *((signed long long int *)(kv->value))); break;
    case VALUE_TYPE_FLOAT: kvCopy = _DICT_ITEM_CREATE_FLOAT(kv->key, *((float *)(kv->value))); break;
    case VALUE_TYPE_DOUBLE: kvCopy = _DICT_ITEM_CREATE_DOUBLE(kv->key, *((double *)(kv->value))); break;
    case VALUE_TYPE_LONG_DOUBLE: kvCopy = _DICT_ITEM_CREATE_LONG_DOUBLE(kv->key, *((long double *)(kv->value))); break;
    case VALUE_TYPE_STRING: kvCopy = _DICT_ITEM_CREATE_STRING(kv->key, (char *)(kv->value)); break;
    case VALUE_TYPE_DICT: kvCopy = _DICT_ITEM_CREATE_PRIMITIVE(kv->key, DICT_COPY(kv->value), VALUE_TYPE_DICT); break;
  }
  return kvCopy;
}

static void _DICT_SHIFT(DICT *dict) {
  if(dict != NULL) {
    if(dict->size > 1) {
      DICT_ITEM *tmpKv = dict->start->next;
      _DELETE_KV(dict->start);
      dict->start = tmpKv;
      dict->size--;
    }else if(dict->size == 1) {
      _DELETE_KV(dict->start);
      dict->start = NULL;
      dict->size = 0;
    }
  }
}

void DICT_CLEAR(DICT *dict) {
  if(dict != NULL && dict->size > 0) {
    _DICT_SHIFT(dict);
    DICT_CLEAR(dict);
  }
}

static void PRINT_REPEAT(char * str, int times) {
  for(int i = 0; i < times; i++) {
    printf("%s", str);
  }
}

void DICT_PRINTL(DICT *dict, int level, bool printType) {
  printc(WHITE, "{\n");
  if(dict == NULL) {
    PRINT_REPEAT("  ", level + 1);
    printc(RED, "NULL\n");
  }else if(dict->size == 0) {
    PRINT_REPEAT("  ", level + 1);
    printc(YELLOW, "empty\n");
  }else {
    DICT_ITEM *tmpKv = dict->start;
    for(int i = 0;i < dict->size; i++) {
      _DICT_ITEM_PRINT(tmpKv, level, printType);
      tmpKv = tmpKv->next;
      i != dict->size - 1 && printf(",");
      printc(WHITE, "\n");
    }
  }
  PRINT_REPEAT("  ", level);
  printc(WHITE, "}");
}

void DICT_PRINT(DICT *dict) {
  DICT_PRINTL(dict, 0, false);
}

void DICT_PRINTD(DICT *dict) {
  DICT_PRINTL(dict, 0, true);
}

void * DICT_GET(DICT *dict, char *k) {
  if(dict == NULL || dict->size == 0) return NULL;
  DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) return tmpKv->value;
    tmpKv = tmpKv->next;
  }
  return NULL;
}

bool DICT_INCLUDES(DICT *dict, char *k) {
  if(dict == NULL || dict->size == 0) return false;
  DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) return true;
    tmpKv = tmpKv->next;
  }
  return false;
}

DICT * DICT_COPY(DICT *dict) {
  if(dict == NULL) return NULL;
  DICT *dictCopy = DICT_CREATE();
  DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    DICT_ADD_KV(dictCopy, _DICT_ITEM_COPY(tmpKv));
    tmpKv = tmpKv->next;
  }
  return dictCopy;
}

void * DICT_FOREACH(DICT *dict, void* (*cb)(DICT_ITEM *, int)) {
  if(dict == NULL) return NULL;
  DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    void *ptr = cb(tmpKv, i);
    if(ptr != NULL) return ptr;
    tmpKv = tmpKv->next;
  }
  return NULL;
}

static bool _DICT_UPDATE_PRIMITIVE(DICT *dict, char *k, void *nvp, VALUE_TYPE t) {
  if(dict == NULL) return false;
  DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == VALUE_TYPE_DICT) {
        DICT_CLEAR(tmpKv->value);
      }
      free(tmpKv->value);
      tmpKv->value = nvp;
      tmpKv->type = t;
      break;
    }
    tmpKv = tmpKv->next;
  }
  if(!keyExists) {
    free(nvp);
  }
  return keyExists;
}

bool _DICT_UPDATE_NULL(DICT *dict, char *k, void *v, char *src) {
  return _DICT_UPDATE_PRIMITIVE(dict, k, v, VALUE_TYPE_NULL);
}

bool _DICT_UPDATE_BOOL(DICT *dict, char *k, bool v, char *src) {
  bool *nvp = malloc(sizeof(bool));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_BOOL);
}

bool _DICT_UPDATE_UNSIGNED_CHAR(DICT *dict, char *k, unsigned char v, char *src) {
  unsigned char *nvp = malloc(sizeof(unsigned char));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_UNSIGNED_CHAR);
}

bool _DICT_UPDATE_SIGNED_CHAR(DICT *dict, char *k, signed char v, char *src) {
  signed char *nvp = malloc(sizeof(signed char));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_SIGNED_CHAR);
}

bool _DICT_UPDATE_UNSIGNED_SHORT_INT(DICT *dict, char *k, unsigned short int v, char *src) {
  unsigned short int *nvp = malloc(sizeof(unsigned short int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_UNSIGNED_SHORT_INT);
}

bool _DICT_UPDATE_UNSIGNED_INT(DICT *dict, char *k, unsigned int v, char *src) {
  unsigned int *nvp = malloc(sizeof(unsigned int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_UNSIGNED_INT);
}

bool _DICT_UPDATE_UNSIGNED_LONG_INT(DICT *dict, char *k, unsigned long int v, char *src) {
  unsigned long int *nvp = malloc(sizeof(unsigned long int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_UNSIGNED_LONG_INT);
}

bool _DICT_UPDATE_UNSIGNED_LONG_LONG_INT(DICT *dict, char *k, unsigned long long int v, char *src) {
  unsigned long long int *nvp = malloc(sizeof(unsigned long long int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_UNSIGNED_LONG_LONG_INT);
}

bool _DICT_UPDATE_SIGNED_SHORT_INT(DICT *dict, char *k, signed short int v, char *src) {
  signed short int *nvp = malloc(sizeof(signed short int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_SIGNED_SHORT_INT);
}

bool _DICT_UPDATE_SIGNED_INT(DICT *dict, char *k, signed int v, char *src) {
  if(strlen(src) == 3 && src[0] == '\'' && src[2] == '\'') {
    return _DICT_UPDATE_UNSIGNED_CHAR(dict, k, v, src);
  }else if(strcmp(src, "false") == 0 || strcmp(src, "true") == 0) {
    return _DICT_UPDATE_BOOL(dict, k, v, src);
  }
  signed int *nvp = malloc(sizeof(signed int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_SIGNED_INT);
}

bool _DICT_UPDATE_SIGNED_LONG_INT(DICT *dict, char *k, signed long int v, char *src) {
  signed long int *nvp = malloc(sizeof(signed long int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_SIGNED_LONG_INT);
}

bool _DICT_UPDATE_SIGNED_LONG_LONG_INT(DICT *dict, char *k, signed long long int v, char *src) {
  signed long long int *nvp = malloc(sizeof(signed long long int));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_SIGNED_LONG_LONG_INT);
}

bool _DICT_UPDATE_FLOAT(DICT *dict, char *k, float v, char *src) {
  float *nvp = malloc(sizeof(float));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_FLOAT);
}

bool _DICT_UPDATE_DOUBLE(DICT *dict, char *k, double v, char *src) {
  double *nvp = malloc(sizeof(double));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_DOUBLE);
}

bool _DICT_UPDATE_LONG_DOUBLE(DICT *dict, char *k, long double v, char *src) {
  long double *nvp = malloc(sizeof(long double));
  *nvp = v;
  return _DICT_UPDATE_PRIMITIVE(dict, k, nvp, VALUE_TYPE_DOUBLE);
}

bool _DICT_UPDATE_STRING(DICT *dict, char *k, char* v, char *src) {
  DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == VALUE_TYPE_DICT) {
        DICT_CLEAR(tmpKv->value);
      }
      free(tmpKv->value);
      char *sc;
      if(v != NULL) {
        sc = malloc(strlen(v) + 1);
      }
      if(sc != NULL) {
        strcpy(sc, v);
        sc[strlen(v)] = '\0';
      }
      tmpKv->value = (void *)sc;
      tmpKv->type = VALUE_TYPE_STRING;
      break;
    }
    tmpKv = tmpKv->next;
  }
  return keyExists;
}

bool _DICT_UPDATE_DICT(DICT *dict, char *k, DICT *newDict, char *src) {
  DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == VALUE_TYPE_DICT) {
        DICT_CLEAR(tmpKv->value);
      }
      free(tmpKv->value);
      tmpKv->value = (void *)newDict;
      tmpKv->type = VALUE_TYPE_DICT;
      break;
    }
    tmpKv = tmpKv->next;
  }
  return keyExists;
}

bool DICT_REMOVE(DICT *dict, char *k) {
  if(dict == NULL) return false;
  DICT_ITEM *currentKv = dict->start;
  DICT_ITEM *prevKv = NULL;

  for(int i = 0;i < dict->size; i++) {
    if(strcmp(currentKv->key, k) == 0) {
      // if the value is a dict then clear its content first
      if(currentKv->type == VALUE_TYPE_DICT) {
        DICT_CLEAR(currentKv->value);
      }

      if(prevKv == NULL) {
        // start
        prevKv = currentKv->next;
        free(currentKv->value);
        free(currentKv);
        dict->start = prevKv;
      }else if(currentKv->next == NULL) {
        // end
        free(currentKv->value);
        free(currentKv);
        currentKv->value = NULL;
      }else {
        // somewhere in the middle
        prevKv->next = currentKv->next;
        free(currentKv->value);
        free(currentKv);
      }
      dict->size--;
      return true;
    }
    prevKv = currentKv;
    currentKv = currentKv->next;
  }
  return false;
}

bool _DICT_ERROR_UNSUPPORTED_TYPE(DICT *dict, char *k, void *v, char *src) {
  if(strcmp(src, "NULL") == 0 || strcmp(src, "((void *)0)") == 0) {
    if(DICT_INCLUDES(dict, k)) {
      _DICT_UPDATE_NULL(dict, k, v, src);
    }else {
      _DICT_ADD_NULL(dict, k, v, src);
    }
  }else {
    printc(RED, "\nUNSUPPORTED VALUE TYPE [%s] for the key \"%s\"", src, k);
    exit(1);
  }
}

#endif ////////////////////////////////////////////////////////////////////////