#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  settickets(100);
  int rc = fork();
  if (rc == 0)
  {
      int grc = fork();
      if(grc == 0)
      {
        settickets(2);
        for(int i = 0; i< 2000; i++)
          printf(1, "A");
      }
      else
      {
        settickets(3000);
        for(int i = 0; i< 2000; i++)
          printf(1, "B");
        settickets(1);
        wait();
      }
  }
  else
  {
    for(int i = 0; i< 2000; i++)
    printf(1, "C");
    wait();
      printf(1, "\n");
  }
  exit();
}
