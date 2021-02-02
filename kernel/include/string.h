#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <Types.h>

char chr(uint32 code);

void strcpy(char* dest, const char* src);
void strcat(char *dest, const char *src);

void strlower(char* in);

uint32 strlen(const char* subj);

void bzero(char* subj, uint32 size);

uint32 strcmp(const char* a, const char* b);

char* strtok(char* s, const char *delim);


#endif // STRING_H_INCLUDED
