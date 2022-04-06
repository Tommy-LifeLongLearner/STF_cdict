#include "stf-dict.h"

int main() {
  STF_DICT *person = STF_DICT_CREATE();
  STF_DICT *num1 = STF_DICT_CREATE();
  STF_DICT *num2 = STF_DICT_CREATE();
  STF_DICT *num3 = STF_DICT_CREATE();

  STF_DICT_ADD(person, "name", "Saadi Toumi Fouad");
  STF_DICT_ADD(person, "unsigned", num1);
  STF_DICT_ADD(person, "signed", num2);
  STF_DICT_ADD(person, "age", 29);
  STF_DICT_ADD(person, "is married", false);
  STF_DICT_ADD(person, "country", "Algeria");
  STF_DICT_ADD(person, "lucky character", 'T');
  STF_DICT_ADD(person, "other character", (signed char)'B');
  STF_DICT_ADD(num2, "floats", num3);
  STF_DICT_ADD(num1, "c1", (unsigned short int)12);
  STF_DICT_ADD(num1, "c2", (unsigned int)15);
  STF_DICT_ADD(num2, "c3", (unsigned long int)19);
  STF_DICT_ADD(num2, "c4", (unsigned long long int)23);
  STF_DICT_ADD(num3, "c9", 12.3);
  STF_DICT_ADD(num3, "c10", 12.4f);
  STF_DICT_ADD(num2, "c5", (signed short int)-14);
  STF_DICT_ADD(num2, "c6", (signed int)-9);
  STF_DICT_ADD(num1, "c7", (signed long int)67);
  STF_DICT_ADD(num1, "c8", (signed long long int)8);

  STF_DICT_UPDATE(num2, "c3", (signed long int)67);
  STF_DICT_UPDATE(num2, "c4", (signed long long int)8);
  STF_DICT_UPDATE(num1, "c7", (unsigned long int)19);
  STF_DICT_UPDATE(num1, "c8", (unsigned long long int)23);

  // debug print (shows types)
  STF_DICT_PRINTD(person);
  // get the `name`'s value from the dict `person`
  printf("\nThe name is: %s\n", (char *)STF_DICT_GET(person, "name"));
  STF_DICT_REMOVE(person, "unsigned");

  // ordinary print
  STF_DICT_PRINT(person);

  STF_DELETE_DICT(person);
  return 0;
}