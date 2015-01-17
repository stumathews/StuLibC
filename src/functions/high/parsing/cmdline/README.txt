command line parsing
--------------------


examples


myprogram.exe -enableOption
myprogram.exe -setOptionTo "something" "also this" "anthis" andThis 4 
myProgram.exe -setOption="something"
myProgram.exe -setOption=5
myProgram.exe --setOption=something
myProgram.exe /t something
myProgram.exe /t
myProgram.exe /t:something
myProgram.exe /t /s
myProgram.exe /ts
myProgram.ede -h

myProgram.exe [something] [something] [something]
myProgram.exe [something],[something]
myProgram.exe arguments.txt

int main( int argc, char** argv );

argv[argc] = {"-enableOption","5","--setOption=","5", "--setOptionTo", "=", "\"something\""}

arg indicators e{"-","--","/","-"}
arg values_indicators follow argindicators and are either 1. attached after arg argument name with value indicators(=,:,space) eg (--setSometehing=true), --setSomething:4, -h 3)

general format:

arg_indicator+arg_name+value_indicator value 
-h=5
--t fish

within the program, all we are worried about is handling the correct argument name and its associated value.

if( enabledOption )
  get value

** note some argument might not need a value and some might require one:

-closeWhen finished (no value should be provided)
-CloseInSeconds 4    (this is mandatory that a value is provided)

arguments values can be mantatory or not
values should not start with argument indicators

some arguments themselves might always need to be present (mandatory arguments)

concepts
-------------

mandatory Argument
non-mandatory argument
argument requires value
argument doesn't require value
argument indicators
argument names
value indicators
values

handling of arguments/ registering arguments when setting up in program:
-------------------------------------------------------------------------

struct NewArgument
{
  Name;
  Description;
  PresenceMandatory;
  ValueMandatory;
  void (*handler)(char* value)
}

CMD_addArgument( {.Name="setSomething", .PresenceMandatory=true, .ValueMandatory=false, .Description="Cool little cat", setSomething} )
CMD_addArgument( {.Name="setSomethingElse", .PresenceMandatory=false, .ValueMandatory=true, .description="apiece of descriptive text", setSomethingElse} )
CMD_addArgument( {.Name="CloseAutomatically", .PresenceMandatory=false, .ValueMandatory=false, CloseAutomatically} )
CMD_AddArguments(struct NewArgumnts[]);
CMD_parse_and_handle(argc, argv)

internally store a list of the mandatory arguments - 

if not arguments are provided (argc == 0 ) print usage using descrition within NewArgument structures registered with the addArgument() function above.

foreach( detect_next_argument(line_of_args) )
{
  save argument within list of FoundArguments
  save any argument provided determine that one was not provided
  check to see if any argument is missing a value or is providing too much
  * defer handlingof non-mandatory arguments within Foundarguments *  
  check to see if it is a mandatory argument, and thus note that it is provided.
  run_mandatory_gument_handler - record this mandatory argument is present


}

for all mandatory arguments tht are not provided, tell the user and bail out.

if(all mandatory arguments handled andaccounted for)
{ 
// runAllFoundNonMandatoryArguments
if argument needed and not provided bail out.
if argument found pass it to handler else set it as NULL and pass it to handler.
run handler.

}








