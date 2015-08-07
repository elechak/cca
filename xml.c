

#include "xml.h"


struct XMLParser * XMLParser_new(){
    struct XMLParser * self = malloc(sizeof(*self));
    self->tags          = NULL;
    self->data          = NULL;
    self->onError       = NULL;
    self->startElement  = NULL;
    self->endElement    = NULL;
    self->characters    = NULL;
    return self;
}

void XMLParser_free(XMLParser self){
    if (self->tags) free(self->tags);
    if (self->data) free(self->data);
}


void parsexml(struct XMLParser * self, char * string){

    self->tags = malloc(1024);
    char *cursor = string;
    char *start  = NULL;
    char *end    = NULL;
    unsigned long length;



    while(1){
        if (! *cursor) break;

        /* find the start of the next tag */
        start = strchr(cursor, '<');
        if (! start ) goto error;

        /* if there are characters between the cursor and the next start tag call character handler */
        if (start != cursor){
            length = (unsigned long)start - (unsigned long)cursor ;
            self->data=realloc(self->data, length +1 );
            memcpy(self->data, cursor, length);
            self->data[length] = '\0';
            if (self->characters)
                self->characters(self);
        }
        end = strchr(cursor, '>');

        if (! end) goto error;

        cursor = end+1;

        // copy element data into self->data
        length = (unsigned long)end - (unsigned long)start ;
        self->data=realloc(self->data,length);
        memcpy(self->data , start+1 , length-1);
        self->data[length-1] = '\0';



        if (  *(self->data) == '?' ){

        }else if (  *(self->data) == '!' ){

        }else if (  *(self->data) == '/' ){

            // END ELEMENT
            if (self->endElement) self->endElement(self); // call the handler
            start = strrchr(self->tags, '.'); // go up one level in self->tags
            *start = '\0';

        }else{
            // START ELEMENT
            length = strcspn(self->data, " >");
            strcat(self->tags, ".");
            strncat(self->tags,self->data,length);
            if (self->startElement) self->startElement(self); // call the handler

            // check to see if the is a single tag element
            if ( self->data[strlen(self->data) -1 ] == '/'){
                if (self->endElement) self->endElement(self);
                start = strrchr(self->tags, '.');
                *start = '\0';
            }
        }

        continue;
        error:
            if (self->onError) self->onError(self);
    }

}






