#include "types.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[])
{
  if(argc !=2)
  {
    printf(2, "Usage: lotteryTesting n\n");
    exit();
  }
  int n = atoi(argv[1]);
  settickets(300);
  int rc = fork();
  if(rc < 0)
  {
    printf(2, "fork error\n");
    exit();
  }
  if (rc == 0)
  {
      rc = fork();
      if(rc < 0)
      {
        printf(2, "fork error\n");
        exit();
      }
      if(rc == 0)
      {
        rc = fork();
        if(rc < 0)
        {
          printf(2, "fork error\n");
          exit();
        }
        if(rc == 0) //process 4
        {
          settickets(100);
          for(int j= 0; j<10; j++)
          {
            volatile int count = 0;
            for(int i = 0; i< n; i++) count++;
          }
        }
        else //process 3
        {
          settickets(200);
          for(int j= 0; j<10; j++)
          {
            volatile int count = 0;
            for(int i = 0; i< n; i++) count++;
          }
          wait();
        }

      }
      else //process 2
      {
        settickets(300);
        for(int j= 0; j<10; j++)
        {
          volatile int count = 0;
          for(int i = 0; i< n; i++) count++;
        }
        wait();
      }
  }
  else //process 1
  {
    int numChecks = 20;
    settickets(150);
    volatile int count = 0;
    for(int i = 0; i< n/5; i++) count++;
    struct pstat * * stats = malloc(sizeof(struct pstat *)*numChecks);
    for(int i = 0; i< numChecks; i++)
    {
      struct pstat *test = malloc(sizeof(struct pstat));
      getpinfo(test);
      stats[i] = test;
      for(int k = 0; k<1; k++)
      {
        volatile int count = 0;
        for(int j = 0; j< n; j++) count++;
      }

    }

    wait();
    for(int i=0; i<numChecks; i++)
    {
      struct pstat * test = stats[i];
      printf(1, "--------------------------------------------------\n");
      for (int j=0; j<20; j++)
      {
        if(test->inuse[j])
        {
          printf(1, "pid: %d; numTickets: %d; ticks: %d\n", test->pid[j], test->tickets[j], test->ticks[j]);
        }
      }
    }
  }

  exit();
}
