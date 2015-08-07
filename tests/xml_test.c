
#include "../xml.h"
#include "test_header.h"



char buffer[1024];
char tags[1024];


void startElement(XMLParser self){
    //printf("start %s\n", self->data);
    strcpy(buffer, self->data);
    strcpy(tags, self->tags);
}

void endElement(XMLParser self){
    //printf("end  %s\n", self->data);
    strcpy(buffer, self->data);
    strcpy(tags, self->tags);
}


int main(int argc, char **argv){
    TITLE("XML PARSER TEST");
    char * xml;
    XMLParser parser = XMLParser_new();
    parser->startElement = startElement;
    parser->endElement = endElement;


    //char * xml = "<a> hello <b c=\"d e f\"/> <g>erik</g> </a>";


    START("start elemement")
        xml = "<erik>";
        parsexml(parser, xml);
        TEST( strcmp(buffer,"erik") ==0);
        TEST( strcmp(tags,".erik") ==0);
    END


    START("multiple start elemement")
        xml = "<a><b><c><d>";
        parsexml(parser, xml);
        TEST( strcmp(buffer,"d") ==0);
        TEST( strcmp(tags,".a.b.c.d") ==0);
    END

    START("start and end elemement")
        xml = "<a></a>";
        parsexml(parser, xml);
        TEST( strcmp(parser->data,"/a") ==0);
        TEST( strcmp(parser->tags,"") ==0);
    END


    //~ START("start and end elemement")
        //~ xml = "<a/>";
        //~ parsexml(parser, xml);
        //~ TEST( strcmp(parser->data,"/a") ==0);
        //~ TEST( strcmp(parser->tags,"") ==0);
    //~ END





    return 0;
}
