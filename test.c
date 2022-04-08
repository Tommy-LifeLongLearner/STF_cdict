#include "c_dict.h"

int main() {
  DICT *person = DICT_CREATE();
  DICT *num1 = DICT_CREATE();
  DICT *num2 = DICT_CREATE();
  DICT *num3 = DICT_CREATE();

  DICT_ADD(person, "name", "Saadi Toumi Fouad");
  DICT_ADD(person, "unsigned", num1);
  DICT_ADD(person, "signed", num2);
  DICT_ADD(person, "age", 29);
  DICT_ADD(person, "is married", false);
  DICT_ADD(person, "country", "Algeria");
  DICT_ADD(person, "lucky character", 'T');
  DICT_ADD(person, "other character", (signed char)'B');
  DICT_ADD(num2, "floats", num3);

  DICT *personCopy = DICT_COPY(person);
  
  DICT_ADD(num1, "c1", (unsigned short int)12);
  DICT_ADD(num1, "c2", (unsigned int)15);
  DICT_ADD(num2, "c3", (unsigned long int)19);
  DICT_ADD(num2, "c4", (unsigned long long int)23);
  DICT_ADD(num3, "c9", 12.3);
  DICT_ADD(num3, "c10", 12.4f);
  DICT_ADD(num2, "c5", (signed short int)-14);
  DICT_ADD(num2, "c6", (signed int)-9);
  DICT_ADD(num1, "c7", (signed long int)67);
  DICT_ADD(num1, "c8", (signed long long int)8);

  DICT_UPDATE(num2, "c3", (signed long int)67);
  DICT_UPDATE(num2, "c4", (signed long long int)8);
  DICT_UPDATE(num1, "c7", (unsigned long int)19);
  DICT_UPDATE(num1, "c8", (unsigned long long int)23);

  DICT_PRINTD(personCopy);

  // debug print (shows types)
  DICT_PRINTD(person);
  // get the `name`'s value from the dict `person`
  printf("\nThe name is: %s\n", (char *)DICT_GET(person, "name"));
  DICT_ADD(person, "name", NULL);
  DICT_REMOVE(person, "unsigned");

  // ordinary print
  DICT_PRINT(person);

  DICT_DELETE(person);
  DICT_DELETE(personCopy);
  return 0;
}