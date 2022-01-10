#ifndef __cplusplus /////////////////////////////////////////////////////////////////////
#include "stf-dict.h"

const char *STF_TYPES[] = {"BOOL", "UNSIGNED_CHAR", "SIGNED_CHAR", "UNSIGNED_SHORT_INT", "UNSIGNED_INT", "UNSIGNED_LONG_INT", "UNSIGNED_LONG_LONG_INT", "SIGNED_SHORT_INT", "SIGNED_INT", "SIGNED_LONG_INT", "SIGNED_LONG_LONG_INT", "FLOAT", "DOUBLE", "LONG_DOUBLE", "STRING", "DICT"};

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
      default: printf("%s", output); break;
    }
    vprintf(output, args);
  #endif
  va_end(args);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_PRIMITIVE(char *k, void *nvp, STF_TYPE t) {
  STF_DICT_ITEM *kvNode = malloc(sizeof(STF_DICT_ITEM));
  if(kvNode != NULL) {
    kvNode->value = nvp;
    kvNode->type = t;
    kvNode->key = k;
    kvNode->next = NULL;
  }
  return kvNode;
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_BOOL(char *k, bool v) {
  bool *nvp = malloc(sizeof(bool));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_BOOL);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_CHAR(char *k, unsigned char v) {
  unsigned char *nvp = malloc(sizeof(unsigned char));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_UNSIGNED_CHAR);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_CHAR(char *k, signed char v) {
  signed char *nvp = malloc(sizeof(signed char));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_SIGNED_CHAR);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(char *k, unsigned short int v) {
  unsigned short int *nvp = malloc(sizeof(unsigned short int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_UNSIGNED_SHORT_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_INT(char *k, unsigned int v) {
  unsigned int *nvp = malloc(sizeof(unsigned int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_UNSIGNED_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_INT(char *k, unsigned long int v) {
  unsigned long int *nvp = malloc(sizeof(unsigned long int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_UNSIGNED_LONG_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(char *k, unsigned long long int v) {
  unsigned long long int *nvp = malloc(sizeof(unsigned long long int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_UNSIGNED_LONG_LONG_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_SHORT_INT(char *k, signed short int v) {
  signed short int *nvp = malloc(sizeof(signed short int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_SIGNED_SHORT_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_INT(char *k, signed int v) {
  signed int *nvp = malloc(sizeof(signed int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_SIGNED_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_LONG_INT(char *k, signed long int v) {
  signed long int *nvp = malloc(sizeof(signed long int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_SIGNED_LONG_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(char *k, signed long long int v) {
  signed long long int *nvp = malloc(sizeof(signed long long int));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_SIGNED_LONG_LONG_INT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_FLOAT(char *k, float v) {
  float *nvp = malloc(sizeof(float));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_FLOAT);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_DOUBLE(char *k, double v) {
  double *nvp = malloc(sizeof(double));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_DOUBLE);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_LONG_DOUBLE(char *k, long double v) {
  long double *nvp = malloc(sizeof(long double));
  *nvp = v;
  return _STF_DICT_ITEM_CREATE_PRIMITIVE(k, nvp, STF_TYPE_LONG_DOUBLE);
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_STRING(char *k, char *s) {
  STF_DICT_ITEM *p = malloc(sizeof(STF_DICT_ITEM));
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
    p->type = STF_TYPE_STRING;
    p->key = k;
    p->next = NULL;
  }
  return p;
}

bool _STF_ERROR_UNSUPPORTED_TYPE(STF_DICT *dict, char *k, void *v, char *src) {
  printc(RED, "\nUNSUPPORTED TYPE [%s] in file: %s, line: %d", src, __FILE__, __LINE__);
  exit(1);
}

static void _STF_DICT_ITEM_PRINT(STF_DICT_ITEM *kv, int level, bool printType) {
  STF_PRINT_REPEAT("  ", level + 1);
  if(kv != NULL) {
    if(kv->value == NULL) {
      printc(GREEN, "\"%s\": ", kv->key);
      printc(RED, "NULL");
    }else {
      if(printType) {
        printc(YELLOW, "(%s) ", STF_TYPES[kv->type]);
      }
      printc(GREEN, "\"%s\": ", kv->key);
      switch(kv->type) {
        case STF_TYPE_BOOL: printc(RED, "%s", *((bool *)(kv->value)) ? "true" : "false"); break;
        case STF_TYPE_UNSIGNED_CHAR: printc(YELLOW, "'%c'", *((unsigned char *)(kv->value))); break;
        case STF_TYPE_SIGNED_CHAR: printc(YELLOW, "'%c'", *((signed char *)(kv->value))); break;
        case STF_TYPE_UNSIGNED_SHORT_INT: printc(BLUE, "%d", *((unsigned short int *)(kv->value))); break;
        case STF_TYPE_UNSIGNED_INT: printc(BLUE, "%u", *((unsigned int *)(kv->value))); break;
        case STF_TYPE_UNSIGNED_LONG_INT: printc(BLUE, "%lu", *((unsigned long int *)(kv->value))); break;
        case STF_TYPE_UNSIGNED_LONG_LONG_INT: printc(BLUE, "%llu", *((unsigned long long int *)(kv->value))); break;
        case STF_TYPE_SIGNED_SHORT_INT: printc(BLUE, "%d", *((signed short int *)(kv->value))); break;
        case STF_TYPE_SIGNED_INT: printc(BLUE, "%d", *((signed int *)(kv->value))); break;
        case STF_TYPE_SIGNED_LONG_INT: printc(BLUE, "%ld", *((signed long int *)(kv->value))); break;
        case STF_TYPE_SIGNED_LONG_LONG_INT: printc(BLUE, "%lld", *((signed long long int *)(kv->value))); break;
        case STF_TYPE_FLOAT: printc(BLUE, "%f", *((float *)(kv->value))); break;
        case STF_TYPE_DOUBLE: printc(BLUE, "%lf", *((double *)(kv->value))); break;
        case STF_TYPE_LONG_DOUBLE: printc(BLUE, "%Lf", *((long double *)(kv->value))); break;
        case STF_TYPE_STRING: printc(GREEN, "\"%s\"", (char *)(kv->value)); break;
        case STF_TYPE_DICT: STF_DICT_PRINTL((STF_DICT *)(kv->value), level + 1, printType); break;
      }
    }
  }else {
    printc(RED, "NULL");
  }
}

static void _STF_DELETE_KV(STF_DICT_ITEM *kv) {
  if(kv->value != NULL) {
    if(kv->type == STF_TYPE_DICT) {
      STF_DICT_CLEAR((STF_DICT *)(kv->value));
    }
    free(kv->value);
  }
  free(kv);
}

STF_DICT * STF_DICT_CREATE() {
  STF_DICT *dict = malloc(sizeof(STF_DICT));
  if(dict != NULL) {
    dict->start = dict->end = NULL;
    dict->size = 0;
  }
  return dict;
}

bool STF_DICT_ADD_KV(STF_DICT *dict, STF_DICT_ITEM *kv) {
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

bool _STF_DICT_ADD_BOOL(STF_DICT *dict, char *k, bool v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_BOOL(k, v));
}

bool _STF_DICT_ADD_UNSIGNED_CHAR(STF_DICT *dict, char *k, unsigned char v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_CHAR(k, v));
}

bool _STF_DICT_ADD_SIGNED_CHAR(STF_DICT *dict, char *k, signed char v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_SIGNED_CHAR(k, v));
}

bool _STF_DICT_ADD_UNSIGNED_SHORT_INT(STF_DICT *dict, char *k, unsigned short int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(k, v));
}

bool _STF_DICT_ADD_UNSIGNED_INT(STF_DICT *dict, char *k, unsigned int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_INT(k, v));
}

bool _STF_DICT_ADD_UNSIGNED_LONG_INT(STF_DICT *dict, char *k, unsigned long int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_INT(k, v));
}

bool _STF_DICT_ADD_UNSIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, unsigned long long int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(k, v));
}

bool _STF_DICT_ADD_SIGNED_SHORT_INT(STF_DICT *dict, char *k, signed short int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_SIGNED_SHORT_INT(k, v));
}

bool _STF_DICT_ADD_SIGNED_INT(STF_DICT *dict, char *k, signed int v, char *src) {
  if(strlen(src) == 3 && src[0] == '\'' && src[2] == '\'') {
    return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_UNSIGNED_CHAR(k, v));
  }else if(strcmp(src, "false") == 0 || strcmp(src, "true") == 0) {
    return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_BOOL(k, v));
  }
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_SIGNED_INT(k, v));
}

bool _STF_DICT_ADD_SIGNED_LONG_INT(STF_DICT *dict, char *k, signed long int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_SIGNED_LONG_INT(k, v));
}

bool _STF_DICT_ADD_SIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, signed long long int v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(k, v));
}

bool _STF_DICT_ADD_FLOAT(STF_DICT *dict, char *k, float v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_FLOAT(k, v));
}

bool _STF_DICT_ADD_DOUBLE(STF_DICT *dict, char *k, double v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_DOUBLE(k, v));
}

bool _STF_DICT_ADD_LONG_DOUBLE(STF_DICT *dict, char *k, long double v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_LONG_DOUBLE(k, v));
}

bool _STF_DICT_ADD_STRING(STF_DICT *dict, char *k, char* v, char *src) {
  return STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_STRING(k, v));
}

static STF_DICT_ITEM * _STF_DICT_ITEM_CREATE_DICT(char *k, STF_DICT *newDict) {
  STF_DICT_ITEM *p = malloc(sizeof(STF_DICT_ITEM));
  if(p != NULL) {
    p->value = newDict;
    p->type = STF_TYPE_DICT;
    p->key = k;
    p->next = NULL;
  }
  return p;
}

bool _STF_DICT_ADD_DICT(STF_DICT *dict, char *k, STF_DICT *newDict, char *src) {
  return newDict && STF_DICT_ADD_KV(dict, _STF_DICT_ITEM_CREATE_DICT(k, newDict));
}

static STF_DICT_ITEM * _STF_DICT_ITEM_COPY(STF_DICT_ITEM *kv) {
  if(kv == NULL) return NULL;
  if(kv->value == NULL) {
    return _STF_DICT_ITEM_CREATE_PRIMITIVE(kv->key, NULL, kv->type);
  }
  STF_DICT_ITEM *kvCopy;
  switch(kv->type) {
    case STF_TYPE_BOOL: kvCopy = _STF_DICT_ITEM_CREATE_BOOL(kv->key, *((bool *)(kv->value))); break;
    case STF_TYPE_UNSIGNED_CHAR: kvCopy = _STF_DICT_ITEM_CREATE_UNSIGNED_CHAR(kv->key, *((unsigned char *)(kv->value))); break;
    case STF_TYPE_SIGNED_CHAR: kvCopy = _STF_DICT_ITEM_CREATE_SIGNED_CHAR(kv->key, *((signed char *)(kv->value))); break;
    case STF_TYPE_UNSIGNED_SHORT_INT: kvCopy = _STF_DICT_ITEM_CREATE_UNSIGNED_SHORT_INT(kv->key, *((unsigned short int *)(kv->value))); break;
    case STF_TYPE_UNSIGNED_INT: kvCopy = _STF_DICT_ITEM_CREATE_UNSIGNED_INT(kv->key, *((unsigned int *)(kv->value))); break;
    case STF_TYPE_UNSIGNED_LONG_INT: kvCopy = _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_INT(kv->key, *((unsigned long int *)(kv->value))); break;
    case STF_TYPE_UNSIGNED_LONG_LONG_INT: kvCopy = _STF_DICT_ITEM_CREATE_UNSIGNED_LONG_LONG_INT(kv->key, *((unsigned long long int *)(kv->value))); break;
    case STF_TYPE_SIGNED_SHORT_INT: kvCopy = _STF_DICT_ITEM_CREATE_SIGNED_SHORT_INT(kv->key, *((signed short int *)(kv->value))); break;
    case STF_TYPE_SIGNED_INT: kvCopy = _STF_DICT_ITEM_CREATE_SIGNED_INT(kv->key, *((signed int *)(kv->value))); break;
    case STF_TYPE_SIGNED_LONG_INT: kvCopy = _STF_DICT_ITEM_CREATE_SIGNED_LONG_INT(kv->key, *((signed long int *)(kv->value))); break;
    case STF_TYPE_SIGNED_LONG_LONG_INT: kvCopy = _STF_DICT_ITEM_CREATE_SIGNED_LONG_LONG_INT(kv->key, *((signed long long int *)(kv->value))); break;
    case STF_TYPE_FLOAT: kvCopy = _STF_DICT_ITEM_CREATE_FLOAT(kv->key, *((float *)(kv->value))); break;
    case STF_TYPE_DOUBLE: kvCopy = _STF_DICT_ITEM_CREATE_DOUBLE(kv->key, *((double *)(kv->value))); break;
    case STF_TYPE_LONG_DOUBLE: kvCopy = _STF_DICT_ITEM_CREATE_LONG_DOUBLE(kv->key, *((long double *)(kv->value))); break;
    case STF_TYPE_STRING: kvCopy = _STF_DICT_ITEM_CREATE_STRING(kv->key, (char *)(kv->value)); break;
  }
  return kvCopy;
}

static void _STF_DICT_SHIFT(STF_DICT *dict) {
  if(dict != NULL) {
    if(dict->size > 1) {
      STF_DICT_ITEM *tmpKv = dict->start->next;
      _STF_DELETE_KV(dict->start);
      dict->start = tmpKv;
      dict->size--;
    }else if(dict->size == 1) {
      _STF_DELETE_KV(dict->start);
      dict->start = NULL;
      dict->size = 0;
    }
  }
}

void STF_DICT_CLEAR(STF_DICT *dict) {
  if(dict != NULL && dict->size > 0) {
    _STF_DICT_SHIFT(dict);
    STF_DICT_CLEAR(dict);
  }
}

static void STF_PRINT_REPEAT(char * str, int times) {
  for(int i = 0; i < times; i++) {
    printf("%s", str);
  }
}

void STF_DICT_PRINTL(STF_DICT *dict, int level, bool printType) {
  printc(WHITE, "{\n");
  if(dict == NULL) {
    STF_PRINT_REPEAT("  ", level + 1);
    printc(RED, "NULL\n");
  }else if(dict->size == 0) {
    STF_PRINT_REPEAT("  ", level + 1);
    printc(YELLOW, "empty\n");
  }else {
    STF_DICT_ITEM *tmpKv = dict->start;
    for(int i = 0;i < dict->size; i++) {
      _STF_DICT_ITEM_PRINT(tmpKv, level, printType);
      tmpKv = tmpKv->next;
      i != dict->size - 1 && printf(",");
      printc(WHITE, "\n");
    }
  }
  STF_PRINT_REPEAT("  ", level);
  printc(WHITE, "}");
}

void STF_DICT_PRINT(STF_DICT *dict) {
  STF_DICT_PRINTL(dict, 0, false);
}

void STF_DICT_PRINTD(STF_DICT *dict) {
  STF_DICT_PRINTL(dict, 0, true);
}

void * STF_DICT_GET(STF_DICT *dict, char *k) {
  if(dict == NULL || dict->size == 0) return NULL;
  STF_DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) return tmpKv->value;
    tmpKv = tmpKv->next;
  }
  return NULL;
}

bool STF_DICT_INCLUDES(STF_DICT *dict, char *k) {
  if(dict == NULL || dict->size == 0) return false;
  STF_DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) return true;
    tmpKv = tmpKv->next;
  }
  return false;
}

STF_DICT * STF_DICT_COPY(STF_DICT *dict) {
  if(dict == NULL) return NULL;
  STF_DICT *dictCopy = STF_DICT_CREATE();
  STF_DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    STF_DICT_ADD_KV(dictCopy, _STF_DICT_ITEM_COPY(tmpKv));
    tmpKv = tmpKv->next;
  }
  return dictCopy;
}

void * STF_DICT_FOREACH(STF_DICT *dict, void* (*cb)(STF_DICT_ITEM *, int)) {
  if(dict == NULL) return NULL;
  STF_DICT_ITEM *tmpKv = dict->start;
  for(int i = 0;i < dict->size; i++) {
    void *ptr = cb(tmpKv, i);
    if(ptr != NULL) return ptr;
    tmpKv = tmpKv->next;
  }
  return NULL;
}

static bool _STF_DICT_UPDATE_PRIMITIVE(STF_DICT *dict, char *k, void *nvp, STF_TYPE t) {
  if(dict == NULL) return false;
  STF_DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == STF_TYPE_DICT) {
        STF_DICT_CLEAR(tmpKv->value);
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

bool _STF_DICT_UPDATE_BOOL(STF_DICT *dict, char *k, bool v, char *src) {
  bool *nvp = malloc(sizeof(bool));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_BOOL);
}

bool _STF_DICT_UPDATE_UNSIGNED_CHAR(STF_DICT *dict, char *k, unsigned char v, char *src) {
  unsigned char *nvp = malloc(sizeof(unsigned char));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_UNSIGNED_CHAR);
}

bool _STF_DICT_UPDATE_SIGNED_CHAR(STF_DICT *dict, char *k, signed char v, char *src) {
  signed char *nvp = malloc(sizeof(signed char));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_SIGNED_CHAR);
}

bool _STF_DICT_UPDATE_UNSIGNED_SHORT_INT(STF_DICT *dict, char *k, unsigned short int v, char *src) {
  unsigned short int *nvp = malloc(sizeof(unsigned short int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_UNSIGNED_SHORT_INT);
}

bool _STF_DICT_UPDATE_UNSIGNED_INT(STF_DICT *dict, char *k, unsigned int v, char *src) {
  unsigned int *nvp = malloc(sizeof(unsigned int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_UNSIGNED_INT);
}

bool _STF_DICT_UPDATE_UNSIGNED_LONG_INT(STF_DICT *dict, char *k, unsigned long int v, char *src) {
  unsigned long int *nvp = malloc(sizeof(unsigned long int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_UNSIGNED_LONG_INT);
}

bool _STF_DICT_UPDATE_UNSIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, unsigned long long int v, char *src) {
  unsigned long long int *nvp = malloc(sizeof(unsigned long long int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_UNSIGNED_LONG_LONG_INT);
}

bool _STF_DICT_UPDATE_SIGNED_SHORT_INT(STF_DICT *dict, char *k, signed short int v, char *src) {
  signed short int *nvp = malloc(sizeof(signed short int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_SIGNED_SHORT_INT);
}

bool _STF_DICT_UPDATE_SIGNED_INT(STF_DICT *dict, char *k, signed int v, char *src) {
  if(strlen(src) == 3 && src[0] == '\'' && src[2] == '\'') {
    return _STF_DICT_UPDATE_UNSIGNED_CHAR(dict, k, v, src);
  }else if(strcmp(src, "false") == 0 || strcmp(src, "true") == 0) {
    return _STF_DICT_UPDATE_BOOL(dict, k, v, src);
  }
  signed int *nvp = malloc(sizeof(signed int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_SIGNED_INT);
}

bool _STF_DICT_UPDATE_SIGNED_LONG_INT(STF_DICT *dict, char *k, signed long int v, char *src) {
  signed long int *nvp = malloc(sizeof(signed long int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_SIGNED_LONG_INT);
}

bool _STF_DICT_UPDATE_SIGNED_LONG_LONG_INT(STF_DICT *dict, char *k, signed long long int v, char *src) {
  signed long long int *nvp = malloc(sizeof(signed long long int));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_SIGNED_LONG_LONG_INT);
}

bool _STF_DICT_UPDATE_FLOAT(STF_DICT *dict, char *k, float v, char *src) {
  float *nvp = malloc(sizeof(float));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_FLOAT);
}

bool _STF_DICT_UPDATE_DOUBLE(STF_DICT *dict, char *k, double v, char *src) {
  double *nvp = malloc(sizeof(double));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_DOUBLE);
}

bool _STF_DICT_UPDATE_LONG_DOUBLE(STF_DICT *dict, char *k, long double v, char *src) {
  long double *nvp = malloc(sizeof(long double));
  *nvp = v;
  return _STF_DICT_UPDATE_PRIMITIVE(dict, k, nvp, STF_TYPE_DOUBLE);
}

bool _STF_DICT_UPDATE_STRING(STF_DICT *dict, char *k, char* v, char *src) {
  STF_DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == STF_TYPE_DICT) {
        STF_DICT_CLEAR(tmpKv->value);
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
      tmpKv->type = STF_TYPE_STRING;
      break;
    }
    tmpKv = tmpKv->next;
  }
  return keyExists;
}

bool _STF_DICT_UPDATE_DICT(STF_DICT *dict, char *k, STF_DICT *newDict, char *src) {
  STF_DICT_ITEM *tmpKv = dict->start;
  bool keyExists = false;
  for(int i = 0;i < dict->size; i++) {
    if(strcmp(tmpKv->key, k) == 0) {
      keyExists = true;
      if(tmpKv->type == STF_TYPE_DICT) {
        STF_DICT_CLEAR(tmpKv->value);
      }
      free(tmpKv->value);
      tmpKv->value = (void *)newDict;
      tmpKv->type = STF_TYPE_DICT;
      break;
    }
    tmpKv = tmpKv->next;
  }
  return keyExists;
}

bool STF_DICT_REMOVE(STF_DICT *dict, char *k) {
  if(dict == NULL) return false;
  STF_DICT_ITEM *currentKv = dict->start;
  STF_DICT_ITEM *prevKv = NULL;

  for(int i = 0;i < dict->size; i++) {
    if(strcmp(currentKv->key, k) == 0) {
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

#endif ////////////////////////////////////////////////////////////////////////