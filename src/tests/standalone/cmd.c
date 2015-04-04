#include <stulibc.h>

char* tagline = "Usage: cmd [optios]";

void help();
void forward();
void forwardby(char*);
void exitf();

int main( int argc, char** argv )
{
    LIB_Init();
   
    // Create arguments and link to argument handlers 
    struct Argument* arg1 = CMD_CreateNewArgument("help","", "Print usage", false, false, help);
    struct Argument* arg2 = CMD_CreateNewArgument("forward","", "Moves forward", false, false, forward); 
    struct Argument* arg3 = CMD_CreateNewArgument("forward-by","forward-by <number>", "Moves forward by num", false, true, forwardby);
    struct Argument arg4 = (struct Argument){ 
                                              .name = "exit",
                                              .display="",
                                              .description="exit the program",
                                              .isMandatory=false,
                                              .isValueMandatory = false,
                                              .handler = exitf
                                            };
    // Registers arguments with the library
    CMD_AddArgument(arg1);
    CMD_AddArgument(arg2);
    CMD_AddArgument(arg3);
    CMD_AddArgument(&arg4);

    if( argc > 1 )
    {
        // Parse and execute handler functions for arguments provided in argv
        CMD_Parse(argc, argv);
    }
    else
    {
        // Prints usage with tagline
        CMD_ShowUsages(tagline);
    }

}

void help()
{
    CMD_ShowUsages(tagline);
}

void forward() 
{ 
    printf("formward!\n"); 
}

void forwardby( char* arg )
{
    int num = atoi(arg);
    printf("formward by %s\n", arg);
    for( int i = 0; i < num-1;i++)
    {
        printf("%d\t", i);
    }
}

void exitf()
{
    printf("Exit!\n");
}
