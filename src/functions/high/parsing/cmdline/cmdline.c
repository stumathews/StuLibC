#include <cmdline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <debugging.h>
#include <memory.h>
#include <safetychecking.h>
#include <ctype.h>
#include <linuxlist.h>
#include <console.h>

struct MandatoryArgList mandatory_args;
struct memory* last_alloc_memory = NULL;
struct memory* first_alloc_memory = NULL;
static const char* indicators[] = {"--","-","/",NULL};

enum ParseResult interpretArgInPipe();

char* CMD_GetIndicators()
{
    return (char*) indicators;
}

void CMD_Init()
{
    INIT_LIST_HEAD( &mandatory_args.list );
}
// Frees the im-memory linked list holing all registered arguments.
void CMD_Uninit() 
{
    struct memory* node = first_alloc_memory;
    while(node != NULL) 
    {
        struct memory* free_me = node;
        node = node->next;
        free(free_me);
    }
}

void CMD_ShowUsages(char* tagline, char* address, char* description) 
{
    struct memory* node = first_alloc_memory;
    struct Argument* found = NULL;

    char* license = "Copyright (C) 2010 Free Software Foundation, Inc.\n\
                     License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
                     This is free software: you are free to change and redistribute it.\n\
                     There is NO WARRANTY, to the extent permitted by law.\n";
    
    // Prints out the first line, the tag line
    printf("%s\n\n", license );
    printf("Usage %s [Options]\n",tagline);
    printf("%s\n", description );

    // Prints ouf the options:
    printf( "Options:\n\n");
    
    // Extract the registered arguments detials and print them
    while(node!=NULL) 
    {
        char* display_name = (!STR_IsNullOrEmpty(node->argument->display) ? node->argument->display :  node->argument->name);
        char* description = node->argument->description;
       
        printf("  --%-23s%s\n", display_name, description);
        
        node = node->next;
    }
    printf("\nReport bugs to <%s>.", address );
}

// Linearly search through the linked list of registered arguments
// find the argument that was registered - ie that is tracked in the memory storage
struct Argument* find(char* name)
{
    // Post condition chceks
    CHECK_STRING_BASICS(name);

    struct memory* node = first_alloc_memory;
    struct Argument* found = NULL;

    while(node!=NULL)
    {
        // look for our named argument:
        if(strcmp(node->argument->name, name) == 0) 
        {
            found = node->argument;
            return found;
        }

        node = node->next;
    }
    // Give the argument back to the caller
    return found;
}

// Register an argument
void CMD_AddArgument(struct Argument* argument) 
{
    if(last_alloc_memory == NULL) 
    {
        // Create the first registered argument
        last_alloc_memory = (struct memory*) Alloc(sizeof(struct memory));
        last_alloc_memory->argument = argument;
        last_alloc_memory->next = NULL;

        // Also track the first registered argument
        first_alloc_memory = last_alloc_memory;
    } 
    else 
    {
        // Create the next argument to be reigistered and store it in the linked list
        struct memory* tmp = (struct memory*) Alloc(sizeof(struct memory));
        last_alloc_memory->next = tmp;
        tmp->argument = argument;
        tmp->next = NULL;

        // Set the last registered argument
        last_alloc_memory = tmp;
    }

    // Ok we have a new argument, lets see if its a mandatory one, and if so add it to known mandatoryargs list
    if( last_alloc_memory->argument->isMandatory )
    {
        struct MandatoryArgList* tmp = malloc( sizeof( struct MandatoryArgList ) );
        tmp->arg_name = last_alloc_memory->argument->name;
        list_add( &(tmp->list), &(mandatory_args.list));
    }
}



// Pipe line is a structure that represents the parts of an argument.
// Strings that make up a argument are pushed into a pipe one at a time until the pipe is full.
// An example of this would be the following: --Name=Steven or -help
// The consistients of the argument are broken down into four components and a pipe is made up of these parts:
// -----------------------------------------------------
// [ arg-indicator | arg name | value indicator | value]
// -----------------------------------------------------  
// Arg indicator: --, -,/ characters
// Arg name: any valid alphabetic name
// Value indicator: character that represents a vaue if following: =
// Value: the string following the value 
// Example:
// -----------------------------------------------------
// [ -- | NumberOfEyes | = | 2
// -----------------------------------------------------  
enum EnumPipeParts { ARG_INDICATOR, ARG_NAME,VALUE_INDICATOR,VALUE} ;     // pipe line ["--","StoreSomething","=","2"]

// Main pipe line aka the current pipe
char* pipe_line[] = {"","","","",""}; // [ARG_INDICATOR, ARG_NAME, VALUE]

// Convenience function to indicate the the pipe is finished - make the code more readable to retrn finish_pipe() instead of true
bool finish_pipe()
{
    return true;
}

// Reset the contents of the pipe
static void clear_pipe() // reset pipe array structure/variable
{
    pipe_line[ARG_INDICATOR] = NULL;
    pipe_line[ARG_NAME] = NULL;
    pipe_line[VALUE] = NULL;
}

// convienience function to create a new argument structure for user
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

// retuns true of the current pipe is full
// a full pipe is if an argument has a indicator such as -- and a name such as 'help' as in '--help' and does not have a value indicator following the name ie. a '=' sign OR
// has a value indicator and a value following it which is not a argument indicator 
bool push_into_pipe(char* arg, char* next_part)   // determine what type of part this is. Returns true if a fully formed pipe is created.
{
    CHECK_STRING( arg, IS_NOT_EMPTY );

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

    // What is our indicator?
    if(!(STR_IsNullOrEmpty(indicator))) 
    {
        pipe_line[ARG_INDICATOR] = indicator;
		char* result = MEM_Alloc(SIZEOFCHAR * strlen(tmpArg));
        char* tmpArgName = STR_Without(indicator, tmpArg, result); // such that --help becomes help or help=something

        pipe_line[ARG_NAME] = tmpArgName;

        //check if the name is attached to a value indicated by a value indicator.(help=something)
        if( STR_Contains("=\0",tmpArg) &&  !STR_EndsWith("=\0",tmpArg)) 
        {
            char* tmpValue = (char*) Alloc(SIZEOFCHAR * (strlen(tmpArg) - strlen(indicator) - 1)); // extract the value as in "something" from help=something
        
            pipe_line[VALUE] = STR_FromLast("=",tmpArg,tmpValue);
			result = STR_Without("=", tmpArgName, result);
			result = STR_Without(pipe_line[VALUE], tmpArgName, result);
            pipe_line[ARG_NAME] = tmpArgName;
        
            return finish_pipe();
        }
        DBG("tmpNextArgs is %s", tmpNextArg);
       
        // if the next argument that will be sent to us is a arg indicator, then this pipe is finished, as its the beginning of te next argument
        if(!STR_IsNullOrEmpty(STR_BeginsWithEither(indicators, tmpNextArg)) || STR_IsNullOrEmpty(tmpNextArg)) 
        {
            return finish_pipe();
        }
        else
        {
            // pipe not finished, expecting a value next
            return false ;
        }
    } 
    else 
    { 
        // this is a value, this indicates the end of a pipe, thus it is finished
        pipe_line[VALUE] = tmpArg;
        return finish_pipe();
    }
}

void print_pipe_line()
{
    DBG("Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
}

enum ParseResult ensure_mandatory_args_present( int argc, char** argv,bool skip_first_arg)
{

    struct list_head *pos;
    struct MandatoryArgList* tmp = malloc( sizeof( struct MandatoryArgList ));


    list_for_each( pos, &mandatory_args.list){
        tmp = list_entry( pos, struct MandatoryArgList, list );
        bool found = false;
        // Look for this mandatory arg in all the args:

        for(int i = 0; i < argc; i++) 
        {

            if( skip_first_arg && i == 0 )
                continue;

            char* peek_next = i+1 < argc ? argv[i+1]:"";
            char* arg_name = argv[i];

            // skip to next argument if this is empty
            if( strcmp(arg_name,"") == 0 ) continue;

            // Push this string into the pipe line and check if this completes the argument/pipline: 
            bool pushResult = push_into_pipe(arg_name, peek_next);
            bool isPipeReady = (pushResult == true);

            if(isPipeReady) 
            { 
                if( strcmp( tmp->arg_name,pipe_line[ARG_NAME]) == 0 )
                {
                    found = true;
                    break;
                }
            }
        }

        if(!found)
        {
            printf("Error: Mandatory Argument '%s' not provided.\n",tmp->arg_name);
            return MANDATORY_MISSING;
        }
    }
    return PARSE_SUCCESS;
}
// Take each argument string passed in put it into the pipe line so as incrementally create a full argument such as "--help=something" into its seperate parts
enum ParseResult CMD_Parse(int argc,char** argv, bool skip_first_arg)
{
    // inefficient
    enum ParseResult man_ret =  ensure_mandatory_args_present( argc, argv, skip_first_arg);
    if( man_ret != PARSE_SUCCESS) return man_ret;

    for(int i = 0; i < argc; i++) 
    {
        
        if( skip_first_arg && i == 0 )
            continue;

        char* peek_next = i+1 < argc ? argv[i+1]:"";
        char* arg_name = argv[i];

        // skip to next argument if this is empty
        if( strcmp(arg_name,"") == 0 ) continue;
      
        // Push this string into the pipe line and check if this completes the argument/pipline: 
        bool pushResult = push_into_pipe(arg_name, peek_next);
        bool isPipeReady = (pushResult == true);

        if(isPipeReady) 
        { 
            // gets the argument from the pipe and finds it in the registered arguments. 
            // Also runs the argument handler
            enum ParseResult parseResult = interpretArgInPipe();
            if( parseResult == EXPECTED_VALUE )
                return EXPECTED_VALUE;
            else if ( parseResult == NO_HANDLER || parseResult == PARSE_SUCCESS )
                continue;
        }
    }
    return PARSE_SUCCESS;
}


// gets the argument from the pipe and finds it in the registered arguments. Also runs the argument handler
enum ParseResult interpretArgInPipe()
{
    // Generally, if pipeline is full(true), interpret argunent and 
    // find it in stored list of registered arguments(in-memory map)...
    
    // look for argument currently stored in the pipeline in the list of registered arguments 
    struct Argument* argument = find(pipe_line[ARG_NAME]);
    if(argument != NULL) 
    {
        // we found a matching registerd argument.
        char* value = NULL;

        // is this a argumenent that needsd a value?
        if(argument->isValueMandatory)
        {
            if( !STR_IsNullOrEmpty(pipe_line[VALUE]))
            {
                value = pipe_line[VALUE]; // get the argument's value out of the pipe line...
            }
            else
            {
                printf("Error: Argument '%s' expects a value but none was provided.\n",argument->name);
                return EXPECTED_VALUE;
            }
        }
        // run the value        
        if(argument->handler != NULL)
        {
            argument->handler(value); // fire off the user's event for handling this argument
        }
        else
        {
            DBG("No handler could be run for argument %s%s",pipe_line[ARG_INDICATOR],argument->name);
            return NO_HANDLER;
        }
    } 
    else
    {
        DBG("Could not find argument Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
        printf("Could find argument '%s'\n", pipe_line[ARG_NAME]);
    }

    clear_pipe();// move on to getting the next argument from cmdline, and clear the contents of the assembly line(pipeline)
    return PARSE_SUCCESS;
}
