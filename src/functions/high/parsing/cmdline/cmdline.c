#include <cmdline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <debugging.h>
#include <memory.h>

struct memory { // In memory linked list holding all registered arguments user submits via addArgument*() functions
    struct Argument* argument;
    struct memory* next;
};

struct memory* last_alloc_memory = NULL;
struct memory* first_alloc_memory = NULL;

void CMD_Uninit() // Frees the im-memory linked list holing all registered arguments.
{
    struct memory* node = first_alloc_memory;
    while(node != NULL) {
        struct memory* free_me = node;
        node = node->next;
        free(free_me);
    }
}

void print_memory_map() // debugging utility to print pipe_line
{
    struct memory* node = first_alloc_memory;
    struct Argument* found = NULL;
    while(node!=NULL) {
        DBG("Name:%s, Description: %s\n",node->argument->name, node->argument->description);
        node = node->next;
        if(node == NULL) DBG("Last node reached.\n");
    }
}

struct Argument* find(char* name)// find the argument that was registered - ie that is tracked in the memory storage
{
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

void storeArgument(struct Argument* argument) // stores the argument in memory map
{
    if(last_alloc_memory == NULL) {
        last_alloc_memory = (struct memory*) malloc(sizeof(struct memory));
        last_alloc_memory->argument = argument;
        last_alloc_memory->next = NULL;
        first_alloc_memory = last_alloc_memory;
    } else {
        struct memory* tmp = (struct memory*) malloc(sizeof(struct memory));
        last_alloc_memory->next = tmp;
        tmp->argument = argument;
        tmp->next = NULL;
        last_alloc_memory = tmp;
    }
}

void CMD_AddArgument(struct Argument* argument) // public interface that the user calls to register an argument
{
    storeArgument(argument);
}


enum EnumPipeParts {ARG_INDICATOR, ARG_NAME,VALUE_INDICATOR,VALUE};// pipe line ["--","StoreSomething","=","2"]
char* pipe_line[3]; // [ARG_INDICATOR, ARG_NAME, VALUE]

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

bool push_into_pipe(char* arg, char* next_part)   // determine what type of part this is. Returns true if a fully formed pipe is created.
{
    short argLength = strlen(arg);
    short nextArgLength = strlen(next_part);
    char* tmpArg = (char*) malloc(SIZEOFCHAR * argLength +1);
    char* tmpNextArg = (char*) malloc(SIZEOFCHAR * nextArgLength +1);
DBG("Push into pipe()\n");
    // Prepare space
    strcpy(tmpArg, arg);
    strcpy(tmpNextArg, next_part);
    char* indicator = NULL;
    char* indicators[] = {"--","-","/",NULL};
    // Determine if this is the beginning of a new argument
    indicator = STR_BeginsWithEither(indicators,tmpArg);
    if(!(STR_IsNullOrEmpty(indicator))) {
DBG("Check for indicator...\n");
        pipe_line[ARG_INDICATOR] = indicator;
        char* tmpArgName = STR_Without(indicator, tmpArg); // such that --help becomes help or help=something
DBG("tmpArgname is %s\n",tmpArgName);
        pipe_line[ARG_NAME] = tmpArgName;
DBG("arname pipe line is %s\n",pipe_line[ARG_NAME]);
        //check if the name is attached to a value indicated by a value indicator.(help=something)
        if( STR_Contains("=",tmpArg)){
DBG("After STR_Contains...\n");
	 if( !STR_EndsWith("=",tmpArg)) {
DBG("After STR_CEndsWith...\n");
            char* tmpValue = (char*) malloc(SIZEOFCHAR * (strlen(tmpArg) - strlen(indicator) - 1)); // extract the value as in "something" from help=something
            pipe_line[VALUE] = STR_FromLast("=",tmpArg,tmpValue);
            tmpArgName = STR_Without("=", tmpArgName);
            tmpArgName = STR_Without(pipe_line[VALUE], tmpArgName);
            pipe_line[ARG_NAME] = tmpArgName;
            return finish_pipe();
	 }
        }
        if(!STR_IsNullOrEmpty(STR_BeginsWithEither(indicators, tmpNextArg)))  // if the next argument that will be sent to us is a arg indicator, then this pipe is finished.
            return finish_pipe();
        else
            return false;
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
    for(int i = 0; i < argc; i++) {
        struct Argument* arg = NULL;
        char* peek_next = i+1 < argc ? argv[i+1]:"";
        if(push_into_pipe(argv[i],peek_next) == true) { // if pipe full(true), interpret argunent and find it in stored list of registered arguments(in-memory map)
            struct Argument* argument = find(pipe_line[ARG_NAME]);
            if(argument != NULL) { // we found a matching registerd argument.
                char* value = "";
                if(pipe_line[VALUE] != NULL)
                    value = pipe_line[VALUE]; // get the argument's value out of the pipe line...
                if(argument->isValueMandatory && STR_IsNullOrEmpty(pipe_line[VALUE])) {
                    DBG("Argument '%s' expects a value but none was provided.\n",argument->name);
                    continue;
                }
                if(argument->handler == NULL) continue;
                argument->handler(value); // fire off the user's event for handling this argument
            } else {
                DBG("Could not find argument Pipe [%s|%s|%s|%s]\n", pipe_line[ARG_INDICATOR],pipe_line[ARG_NAME],pipe_line[VALUE_INDICATOR],pipe_line[VALUE]);
            }
            clear_pipe();// move on to getting the next argument from cmdline
        }
    }
}

