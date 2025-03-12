#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  int pflag = 0;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "p")) != -1)
    switch (c)
      {
      case 'p':
        pflag = 1;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  
  if (pflag) {
    long num_procs = cpu_main();
    printf("Number of processors: %ld\n", num_procs);
  }

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}