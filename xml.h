


#ifndef _XML_
#define _XML_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAG_STARTSWITH(string)     if (strncmp(string,self->tags,strlen(string)) ==0)
#define TAG_ENDSWITH(string)     if (strncmp(string,(self->tags) + (strlen(self->tags)-strlen(string)),strlen(string)) ==0)
#define MATCH(string)     if ((*string == *line) && (strcmp(string,line) == 0))
#define SEND(string)    send(sd, string, strlen(string),0);




struct XMLParser{
    char  * tags;
    char * data;
    void (*onError) (struct XMLParser * self);
    void (*startElement) (struct XMLParser * self);
    void (*endElement) (struct XMLParser * self);
    void (*characters) (struct XMLParser * self);
};
typedef struct XMLParser * XMLParser;

struct XMLParser * XMLParser_new();
void XMLParser_free(XMLParser self);
void parsexml(struct XMLParser * self, char * string);
#endif





