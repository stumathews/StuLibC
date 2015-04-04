#include <cmdline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <debugging.h>
#include <memory.h>
#include <safetychecking.h>
#include <ctype.h>

struct memory { // In memory linked list holding all registered arguments user submits via addArgument*() functions
    struct Argument* argument;
    struct memory* next;
};

struct memory* last_alloc_memory = NULL;
struct memory* first_alloc_memory = NULL;
static const char* indicators[] = {"--","-","/",NULL};

char* CMD_GetIndicators()
{
    return (char**) indicators;
}

void CMD_Uninit() // Frees the im-memory linked list holing all registered arguments.
{
    struct memory* node = first_alloc_memory;
    while(node != NULL) {
        struct memory* free_me = node;
        node = node->next;
        free(free_me);
    }
}

void CMD_ShowUsages(char* tagline) // debugging utility to print pipe_line
{
    struct memory* node = first_alloc_memory;
    struct Argument* found = NULL;
    printf("%s\n",tagline);
    printf( "Options:\n");
    while(node!=NULL) {
    char* display_name = (!STR_IsNullOrEmpty(node->argument->display) ? node->argument->display :  node->argument->name);
    char* description = node->argument->description;
        printf("  --%-23s%s\n", display_name, description);
        DBG("Name:%s, Description: %s\n",node->argument->name, node->argument->description);
        node = node->next;
        if(node == NULL) DBG("Last node reached.\n");
    }
}

struct Argument* find(char* name)// find the argument that was registered - ie that is tracked in the memory storage
{
    CHECK_STRING_BASICS(name);

    struct memory* node = first_alloc_memory;
    struct Argument* found = NULL;
    while(node!=NULL) {
        if(strcmp(node->argument->name, name) == 0) {
            found = node->argument;
            return found;
        }
        node = node->next;
    }
    return found;
}

void CMD_AddArgument(struct Argument* argument) // public interface that the user calls to register an argument
{
    if(last_alloc_memory == NULL) {
        DBG("Alloc'ing");
        last_alloc_memory = (struct memory*) Alloc(sizeof(struct memory));
        last_alloc_memory->argument = argument;
        last_alloc_memory->next = NULL;
        first_alloc_memory = last_alloc_memory;
        DBG("done allocing");
    } else {
        struct memory* tmp = (struct memory*) Alloc(sizeof(struct memory));
        last_alloc_memory->next = tmp;
        tmp->argument = argument;
        tmp->next = NULL;
        last_alloc_memory = tmp;
    }
}


enum EnumPipeParts {ARG_INDICATOR, ARG_NAME,VALUE_INDICATOR,VALUE};// pipe line ["--","StoreSomething","=","2"]
char* pipe_line[3] = {"","","",""}; // [ARG_INDICATOR, ARG_NAME, VALUE]

bool finish_pipe() // to to read method that returns true which means the pipe is finished.
{
    return true;
}

static void clear_pipe() // reset pipe array structure/variable
{
    pipe_line[ARG_INDICATOR] = NULL;
    pipe_line[ARG_NAME] = NULL;
    pipe_line[VALUE] = NULL;
}

struct Argument* CMD_CreateNewArgument( char* name, char* display, char* description, bool isMandatory, bool isValueMandatory, void (*handler)(char* arg))
{
    struct Argument* newArgument = (struct Argument*) malloc( sizeof(struct Argument) );
    strcpy(newArgument->name,name);
    strcpy(newArgument->display, display);
    strcpy(newArgument->description,description);
    newArgument->isMandatory = isMandatory;
    newArgument->isValueMandatory = isValueMandatory;
    newArgument->handler = handler;
    return newArgument;
}

bool push_into_pipe(char* arg, char* next_part)   // determine what type of part this is. Returns true if a fully formed pipe is created.
{
    CHECK_STRING( arg, IS_NOT_EMPTY );
    //CHECK_STRING( next_part, IS_NOT_EMPTY);

    short argLength = strlen(arg);
    short nextArgLength = strlen(next_part);
    char* tmpArg = (char*) Alloc(SIZEOFCHAR * argLength +1);
    char* tmpNextArg = (char*) Alloc(SIZEOFCHAR * nextArgLength +1);
    
    // Prepare space
    strcpy(tmpArg, arg);
    strcpy(tmpNextArg, next_part);
    char* indicator = NULL;
    char* indicators[] = {"--","-","/",NULL};
    
    // Determine if this is the beginning of a new argument
    indicator = STR_BeginsWithEither(indicators,tmpArg);
    DBG("indicator is %s", indicator);
    
    if(!(STR_IsNullOrEmpty(indicator))) 
    {
        pipe_line[ARG_INDICATOR] = indicator;
        char* tmpArgName = STR_Without(indicator, tmpArg); // such that --help becomes help or help=something
        DBG("arg is %s", tmpArgName);
        pipe_line[ARG_NAME] = tmpArgName;
        //check if the name is attached to a value indicated by a value indicator.(help=something)
        if( STR_Contains("=\0",tmpArg) &&  !STR_EndsWith("=\0",tmpArg)) {
            char* tmpValue = (char*) Alloc(SIZEOFCHAR * (strlen(tmpArg) - strlen(indicator) - 1)); // extract the value as in "something" from help=something
            pipe_line[VALUE] = STR_FromLast("=",tmpArg,tmpValue);
            tmpArgName = STR_Without("=", tmpArgName);
            tmpArgName = STR_Without(pipe_line[VALUE], tmpArgName);
            pipe_line[ARG_NAME] = tmpArgName;
            return finish_pipe();
        }
        DBG("tmpNextArgs is %s", tmpNextArg);
       
        if(!STR_IsNullOrEmpty(STR_BeginsWithEither(indicators, tmpNextArg)) || STR_IsNullOrEmpty(tmpNextArg))  // if the next argument that will be sent to us is a arg indicator, then this pipe is finished.
        {
            DBG("Finishing pipe");
            return finish_pipe();
        }
        else
        {
            DBG("pip not finished");
            return false;
        }
    } else { // this is a value, this indicates the end of a pipe, thus it is finished
        pipe_line[VALUE] = tmpArg;
        return finish_pipe();
    }
}

void print_pipe_line()
{
    DBG("Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
}

void CMD_Parse(int argc,char** argv)
{
    for(int i = 0; i < argc; i++) 
    {
        DBG("parsing %s\n", argv[i]);
        
        struct Argument* arg = NULL;
        char* peek_next = i+1 < argc ? argv[i+1]:"";
        char* arg_name = argv[i];

        // skip to next argument if this is empty
        if( strcmp(arg_name,"") == 0 ) continue;
       
        bool pushResult = push_into_pipe(arg_name, peek_next);
        bool isPipeReady = pushResult == true;

        if(isPipeReady) 
        { 
            // gets the argument from the pipe and finds it in the registered arguments. Also runs the argument handler
            interpretArgInPipe(arg);
        }
    }
}

void interpretArgInPipe(struct Argument* arg)
{
    // if ipe full(true), interpret argunent and find it in stored list of registered arguments(in-memory map)
    struct Argument* argument = find(pipe_line[ARG_NAME]);
    if(argument != NULL) 
    {
        // we found a matching registerd argument.
        char* value = NULL;
        if(pipe_line[VALUE] != NULL)
            value = pipe_line[VALUE]; // get the argument's value out of the pipe line...
             
            if(argument->isValueMandatory && STR_IsNullOrEmpty(pipe_line[VALUE]))
            {
                printf("Error: Argument '%s' expects a value but none was provided.\n",argument->name);
                return;
            }
                
            if(argument->handler != NULL)
            {
                DBG("pipe_line[VALUE] = '%s'",pipe_line[VALUE]);

                argument->handler(value); // fire off the user's event for handling this argument
            }
            else
            {
                return;
            }
    } 
    else
    {
        DBG("Could not find argument Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
    }

    clear_pipe();// move on to getting the next argument from cmdline
}
