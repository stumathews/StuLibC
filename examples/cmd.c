#include <stulibc.h>

char* tagline = "Usage: cmd [optios]";

void help();
void forward();
void forwardby(char*);
void exitf();

char* logfilename = "cmd.log";

int main( int argc, char** argv )
{
    LIB_Init();
  
    DBG_WriteLineToFile("==Starting==", logfilename, MINOR );
    DBG_WriteLineToFile("Create arguments and link to argument handlers",logfilename, MINOR );
    LOG_LogLineToFile("Hello",logfilename);

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
    DBG_WriteLineToFile("Registers arguments with the library",logfilename, MINOR);
    CMD_AddArgument(arg1);
    CMD_AddArgument(arg2);
    CMD_AddArgument(arg3);
    CMD_AddArgument(&arg4);

    


    if( argc > 1 )
    {
        DBG_WriteLineToFile("Parse and execute handler functions for arguments provided in argv", logfilename, MINOR);
        bool skip_first_argument = true;
        CMD_Parse(argc, argv,skip_first_argument);
    }
    else
    {
        DBG_WriteLineToFile("Prints usage with tagline", logfilename, MINOR);
        CMD_ShowUsages(tagline);
    }

//    LIB_Uninit();

}

void help()
{
    DBG_WriteLineToFile("Showing help.", logfilename, MINOR);
    CMD_ShowUsages(tagline);
}

void forward() 
{ 
    DBG_WriteLineToFile("Showing forward command", logfilename, MINOR);
    printf("formward!\n"); 
}

void forwardby( char* arg )
{
    DBG_WriteLineToFile("Showing forward by command", logfilename, MINOR);
    int num = atoi(arg);
    printf("formward by %s\n", arg);
    for( int i = 0; i < num-1;i++)
    {
        printf("%d\t", i);
    }
}

void exitf()
{
    DBG_WriteLineToFile("Showing exitf command", logfilename, MINOR);
    printf("Exit!\n");
}
