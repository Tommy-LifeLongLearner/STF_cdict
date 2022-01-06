#include "stf-dict.h"

int main() {
  STF_DICT *person = STF_DICT_CREATE();
  STF_DICT *cars = STF_DICT_CREATE();
  STF_DICT_ADD(person, "name", "Saadi Toumi Fouad");
  STF_DICT_ADD(person, "cars", cars);
  STF_DICT_ADD(person, "age", 29);
  STF_DICT_ADD(person, "country", "Algeria");
  STF_DICT_ADD(person, "Lucky character", "T");
  STF_DICT_ADD(cars, "Volvo", (signed short int)1999);
  STF_DICT_ADD(cars, "BMW", (signed int)2011);
  STF_DICT_ADD(cars, "Fiat", (signed long int)2004);
  STF_DICT_ADD(cars, "Mercedes", (signed long long int)2009);
  STF_DICT_ADD(cars, "Volvo", (signed short int)2999);
  STF_DICT_ADD(cars, "BMW", (signed int)3011);
  STF_DICT_ADD(cars, "Fiat", (signed long int)3004);
  STF_DICT_ADD(cars, "Mercedes", (signed long long int)3009);
  STF_DICT_PRINT(person);
  STF_DELETE_DICT(person);
  return 0;
}