#include <stdio.h>
#include <timing.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <testing.h>



void test_TIME_GetCPUTimeTaken()
{
  clock_t startTime = TIME_StartCPURecord();
  int increase_me = 0;
  // intensive work  
  short loop1_max= 70;
  short loop2_max = 25;
  for( int i = 0; i< loop1_max; i++ )
  {
    increase_me += i*increase_me;
  }
  clock_t endTime = TIME_StartCPURecord();
  clock_t timeTaken = TIME_GetCPUTimeTakenInSeconds( startTime, endTime);
  
  
  clock_t startTime2 = TIME_StartCPURecord();
  clock_t endTime2 = TIME_StartCPURecord();
  clock_t timeTaken2 = TIME_GetCPUTimeTakenInSeconds( startTime2, endTime2);
  DBG("It has taken %lu seconds(and %lu units) to complete %d loop operation.\n", timeTaken, TIME_GetCPUTimeTakenInUnits(startTime,endTime), loop1_max);
  DBG("It has taken %lu seconds(and %lu units) to complete that %d loop operation.\n", timeTaken2, TIME_GetCPUTimeTakenInUnits(startTime2, endTime2), loop2_max);



}

void test_TIME_StartCPURecord()
{
  clock_t time = TIME_StartCPURecord();
//  assert( time > 0 );
}

void test_TIME_StopCPURecord()
{
  clock_t time = TIME_StartCPURecord();

  //assert( time > 0 );
}

int main( int argc, char** argv )
{
  struct TestDefinition tests[] = {
    test_TIME_GetCPUTimeTaken, "test_TIME_GetTimeTaken()",
    test_TIME_StartCPURecord, "test_TIME_StartRecord()",
    test_TIME_StopCPURecord, "test_TIME_StopRecord()"
  };
  run_tests( tests,3);
  return 0;
}
