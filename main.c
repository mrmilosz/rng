#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

const int sizeof_double = sizeof(double);
int file_descriptors[2];
double read_random_number(void);

int main(void)
{
   pid_t child_pid;
   double random_number;

   pipe(file_descriptors);

   // Fork!
   if ((child_pid = fork()) == -1)
   {
      perror("fork");
      exit(1);
   }

   // Child process (Python)
   if (child_pid == 0)
   {
      close(file_descriptors[0]);
      dup2(file_descriptors[1], 1);
      close(file_descriptors[1]);

      execl("./rng.py", "python", (char *)NULL);
   }

   // Parent (us)
   else
   {
      close(file_descriptors[1]);

      // REPLACE ME WITH PASSING read_random_number TO TEST SUITE
      int i;
      for (i = 0; i < 20; ++i)
      {
         random_number = read_random_number();
         printf("Received double: %f\n", random_number);
      }
      // END REPLACE ME

      close(file_descriptors[0]);
   }

   return 0;
}

double read_random_number()
{
   int byte_count;
   double random_number;

   byte_count = read(file_descriptors[0], (char *)&random_number, sizeof_double);

   if (byte_count * 8 < sizeof_double)
   {
      close(file_descriptors[0]);
   }

   return random_number;
}
