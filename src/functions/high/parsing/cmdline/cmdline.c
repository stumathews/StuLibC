#include <cmdline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <debugging.h>
#include <memory.h>
#include <safetychecking.h>
#include <ctype.h>
#include <console.h>

List mandatory_arg_names;
List memory;
static const char* indicators[] = {"--","-","/",NULL};

enum ParseResult interpretArgInPipe();
void print_pipe_line();
char* CMD_GetIndicators()
{
    return (char*) indicators;
}

void CMD_Init()
{
    LIST_Init(&mandatory_arg_names);
    LIST_Init(&memory);
}

void freeArgument(struct LinkedListNode* node)
{
	struct Argument* arg = node->data;
	MEM_DeAlloc(arg);
}
// Frees the in-memory linked list holing all registered arguments.
void CMD_Uninit() 
{
    LIST_ForEach(&memory, freeArgument);
}

void CMD_ShowUsages(char* tagline, char* address, char* description) 
{
    char* license = "Copyright (C) 2010 Free Software Foundation, Inc.\n" \
"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n" \
"This is free software: you are free to change and redistribute it.\n" \
"There is NO WARRANTY, to the extent permitted by law.\n";
    
    // Prints out the first line, the tag line
    printf("%s\n\n", license );
    printf("Usage %s [Options]\n",tagline);
    printf("%s\n", description );

    // Prints out the options:
    printf("Options:\n\n");
    
    // Extract the registered arguments details and print them
    for(int j = 0; j < memory.size;j++)
    {
    	struct Argument* arg = LIST_Get(&memory, j)->data;
        char* display_name = (!STR_IsNullOrEmpty(arg->display) ? arg->display :  arg->name);
        char* description = arg->description;
       
        printf("  --%-23s%s\n", display_name, description);
    }
    printf("\nReport bugs to <%s>.", address );
}

// Linearly search through the linked list of registered arguments
// find the argument that was registered - i.e that is tracked in the memory storage
struct Argument* find(char* name)
{
    // Post condition checks
    CHK_str(name, IS_NOT_EMPTY, (const char*) __FUNCTION__);

    struct Argument* found = NULL;

    for(int j = 0; j < memory.size; j++)
    {
        struct Argument* arg = LIST_Get(&memory, j)->data; // look for our named argument:
        DBG("looking ar argument: %s for %s\n", arg->name, name);
        if(strcmp(arg->name, name) == 0) {
        	DBG("found argument: %s\n", arg->name);
            return arg;
        }
    }
    if(!found){
    	DBG("Could not find %s", name);
    }
    // Give the argument back to the caller
    return found;
}

// Register an argument
void CMD_AddArgument(struct Argument* argument) 
{
	LIST_Add(&memory, argument);
    if(argument->isMandatory) {
        LIST_Add(&mandatory_arg_names,argument->name);
        DBG("Adding new argument: %s as mandatory.\n", argument->name);
    }

    DBG("Adding new argument: %s\n", argument->name);
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
enum EnumPipeParts { ARG_INDICATOR, ARG_NAME, VALUE_INDICATOR, VALUE} ;     // pipe line ["--","StoreSomething","=","2"]

// Main pipe line aka the current pipe
char* pipe_line[] = {"","","","",""}; // [ARG_INDICATOR, ARG_NAME,VALUE_INDICATOR,  VALUE]

// Convenience function to indicate the the pipe is finished - make the code more readable to retrn finish_pipe() instead of true
bool finish_pipe()
{
	DBG("Pipe is finished: ");
	print_pipe_line();
    return true;
}

// Reset the contents of the pipe
static void clear_pipe() // reset pipe array structure/variable
{
    pipe_line[ARG_INDICATOR] = NULL;
    pipe_line[ARG_NAME] = NULL;
    pipe_line[VALUE] = NULL;
    DBG("Clearing the pipe\n");
}

// convienience function to create a new argument structure for user
struct Argument* CMD_CreateNewArgument(char* name, char* display, char* description, bool isMandatory, bool isValueMandatory, void (*handler)(char* arg))
{
    struct Argument* newArgument = (struct Argument*) malloc(sizeof(struct Argument) );
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
    
    bool isValidIndicator = false;
    const char* indicator = NULL;
    const char* indicators[] = {"--","-","/",NULL};
    
    // Determine if this is the beginning of a new argument
    indicator = STR_BeginsWithEither(indicators,arg, 3);

    DBG("Detected indicator as %s \n", indicator);

    isValidIndicator = !(STR_IsNullOrEmpty(indicator));
    if(isValidIndicator)
    {
        pipe_line[ARG_INDICATOR] = (char*) indicator;
		char* clean_arg_name = malloc(SIZEOFCHAR * strlen(arg));
		clean_arg_name = STR_Without(indicator, arg, clean_arg_name); // such that --help becomes help or help=something
        pipe_line[ARG_NAME] = clean_arg_name;

        DBG("Added argument name to pipeline: %s\n", pipe_line[ARG_NAME]);

        //check if the name is attached to a value indicated by a value indicator.(help=something)
        if(STR_Contains("=", arg) && !STR_EndsWith("=", arg))
        {
        	DBG("Name=Value argument detected.\n");
        	DBG("Extracting value....\n");

        	char* tmpValue = (char*) malloc(SIZEOFCHAR * (strlen(arg) - strlen(indicator) - 1)); // extract the value as in "something" from help=something
        	pipe_line[VALUE] = STR_FromLast("=", arg, tmpValue);
            DBG("value is %s\n", pipe_line[VALUE]);


            clean_arg_name = STR_Without("=", pipe_line[ARG_NAME], clean_arg_name);
            clean_arg_name = STR_Without(pipe_line[VALUE], pipe_line[ARG_NAME], clean_arg_name);

            pipe_line[ARG_NAME] = clean_arg_name;
            DBG("arg is %s\n", clean_arg_name);

            DBG("Name '%s' is attached to value %s\n", pipe_line[ARG_NAME], pipe_line[VALUE]);
        
            return finish_pipe();
        }
       
        // if the next argument that will be sent to us is a arg indicator, then this pipe is finished, as its the beginning of te next argument
        return !STR_IsNullOrEmpty(STR_BeginsWithEither(indicators, next_part, 3)) || STR_IsNullOrEmpty(next_part) ? finish_pipe(): false;
    } 
    else 
    { // this is a value, this indicates the end of a pipe, thus it is finished
    	DBG("Indicator is value: %s \n", indicator);
        pipe_line[VALUE] = arg;
        DBG("pipline value: %s \n", pipe_line[VALUE]);
        return finish_pipe();
    }
}

void print_pipe_line()
{
    DBG("Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
}

enum ParseResult ensure_mandatory_args_present(int argc, char** argv, bool skip_first_arg)
{
	printf("%d count of mandatory args\n", mandatory_arg_names.size);
	for(int j = 0; j < mandatory_arg_names.size; j++) {
        char* mandatoryName = LIST_Get(&mandatory_arg_names, j)->data;
        bool found = false;
        DBG("Looking for mandatory arg %s\n", mandatoryName);
        DBG("Look for this mandatory arg %s in all the args:", mandatoryName);

        for(int i = 0; i < argc; i++) {
            char* peek_next = i+1 < argc ? argv[i+1]: "";
            char* arg_name = argv[i];

        	DBG("found this: %s\n", argv[i]);
        	bool isFirstArg = (i == 0);

            if(skip_first_arg && isFirstArg) {
            	DBG("Skipping first argument, %s", argv[i]);
            	continue;
            }

            // skip to next argument if this is empty
            if(strcmp(arg_name,"") == 0) {
            	DBG("Skipping argument, %s as is empty", arg_name);
            	continue;
            }

            // Push this string into the pipe line and check if this completes the argument/pipline: 
            bool pushResult = push_into_pipe(arg_name, peek_next);
            bool isPipeReady = (pushResult == true);

            if(isPipeReady) {
            	DBG("Checking pipeline for match:\n");
            	print_pipe_line();
                if(strcmp(mandatoryName, pipe_line[ARG_NAME]) == 0) {
                    found = true;
                    DBG("Found mandatory arg %s in arg list as expected\n", mandatoryName);
                    break;
                }
            }
        } // loop again to push next arg into pipe

        if(!found) {
            printf("Error: Mandatory Argument '%s' not provided.\n", mandatoryName);
            return MANDATORY_MISSING;
        }
    }
    return PARSE_SUCCESS;
}
// Take each argument string passed in put it into the pipe line so as incrementally create a full argument such as "--help=something" into its seperate parts
enum ParseResult CMD_Parse(int argc, char** argv, bool skip_first_arg)
{
    // inefficient
    enum ParseResult man_ret =  ensure_mandatory_args_present(argc, argv, skip_first_arg);
    if(man_ret != PARSE_SUCCESS) return man_ret;

    for(int i = 0; i < argc; i++) {
        if(skip_first_arg && i == 0) {
        	DBG("Skipping firs argument %s\n", argv[i]);
            continue;
        }
        DBG("argument is %s\n", argv[i]);

        char* peek_next = i + 1 < argc ? argv[i+1] : "";
        char* arg_name = argv[i];

        // skip to next argument if this is empty
		if( strcmp(arg_name,"") == 0 ) {
			DBG("Skipping argument, %s as is empty", arg_name);
			continue;
		}
      
        // Push this string into the pipe line and check if this completes the argument/pipline: 
        bool pushResult = push_into_pipe(arg_name, peek_next);
        bool isPipeReady = (pushResult == true);

        if(isPipeReady) {
            // gets the argument from the pipe and finds it in the registered arguments. 
            // Also runs the argument handler
            enum ParseResult parseResult = interpretArgInPipe();
            if(parseResult == EXPECTED_VALUE) {
                return EXPECTED_VALUE;
            } else if (parseResult == NO_HANDLER || parseResult == PARSE_SUCCESS) {
                continue; // next arg!
            }
            clear_pipe();
        }
    }
    return PARSE_SUCCESS;
}


// gets the argument from the pipe and finds it in the registered arguments. Also runs the argument handler
enum ParseResult interpretArgInPipe()
{
    struct Argument* argument = find(pipe_line[ARG_NAME]);
    if(argument != NULL) {
        // we found a matching registerd argument.
        char* value = pipe_line[VALUE];

        // is this a argumenent that needs a value?
        if(argument->isValueMandatory) {
            if(!STR_IsNullOrEmpty(pipe_line[VALUE])) {
                value = pipe_line[VALUE]; // get the argument's value out of the pipe line...
            } else {
            	printf("Error: Argument '%s' expects a value but none was provided.\n",argument->name);
                return EXPECTED_VALUE;
            }
        }

        // run the value        
        if(argument->handler != NULL) {
        	DBG("Running handler for argument %s\n", pipe_line[ARG_NAME]);
            argument->handler(value); // fire off the user's event for handling this argument
        } else {
            DBG("No handler could be run for argument %s%s",pipe_line[ARG_INDICATOR],argument->name);
            return NO_HANDLER;
        }
    } else {
        DBG("Could not find argument Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
        printf("Could find argument '%s'\n", pipe_line[ARG_NAME]);
    }

    clear_pipe();// move on to getting the next argument from cmdline, and clear the contents of the assembly line(pipeline)
    return PARSE_SUCCESS;
}
