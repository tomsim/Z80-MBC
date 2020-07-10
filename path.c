#include <stdio.h>

int main(int argc, char *argv[])
{
  unsigned int *preword=(unsigned int *)0xEABE;
  unsigned char *prebyte=(unsigned char *)0xEABD;
  unsigned char *target=(unsigned char *)0xFC38;
  if (*prebyte!=0xC2 || *preword!=0xEB60 || argc>2)
    {
      printf("Warning! This does not appear to be a matching version of the CP/M CCP. This program will not continue.\n");
      return 9;
    }
  if (argc==1)
    {
      printf("Usage: path [drive] - Set drive letter to search if program not found on current disk; use @ to inhibit search\nCurrent status:");
      if (*target==0) printf("Off\n");
      else printf("Drive %c:\n",*target+'A'-1);
      return 0;
    }
  if (argc==2)
    {
      unsigned char drive=argv[1][0];
      if (drive>='a' && drive<='p') drive-=('a'-'A');
      if (drive<'@'|| drive>'P')
	{
	  printf("Illegal drive. No change.\n");
	  return 7;
	}
      *target=drive-'@';
      printf("Path set %c:\n",*target+'A'-1);
      return 0;
    }
  // should not get here
  return 10;
}
  
