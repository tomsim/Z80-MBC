// Al Williams Hackaday
#include <stdio.h>
#include <stdlib.h>

// Specific for MPC Z80 -- does not use BIOS/BDOS calls but talks directly to IOS


int main(int argc, char *argv[])
{
  if (argc!=2&&argc!=3)
    {
      printf("Usage: FORMAT DRIVE [S] where DRIVE is 0-3\nUse S to do a system generation using the current\ndrive 0 system tracks (default for drive 0)");
      return 1;
    }
  unsigned sysgen=0;
  unsigned char sys[2*32*128];  // 8k Buffer for system tracks
  unsigned sec=0;
  unsigned disknr=atoi(argv[1]);
  unsigned int track, c, sector, i, j;
  unsigned int percent=0;
  if (disknr<0||disknr>3)
    {
      printf("Unknown disk drive\n");
      return 1;
    }
  if (argc==3)
    {
      if (*argv[2]=='S' || *argv[2]=='s')
	sysgen=1;
      else
	{
	  printf("Unknown option\n");
	  return 1;
	}
    }

  if (disknr==0) sysgen=1;
  if (sysgen)
    {
      printf("Reading system tracks...\n");
      for (track=0;track<2;track++)
	{
	  for (sector=1;sector<=32;sector++)
	    {
	      outp(9,0);
	      outp(10,track);
	      outp(11,sector);
	      for (i=0;i<128;i++)
		sys[(track*32+sector-1)*128+i]=inp(6);
	    }
	}
    }
  printf("This will format drive %d (%c:) and destroy all contents on the drive. Are you sure? ",disknr,'A'+disknr);
  do {
    c=getchar();
    if (c=='n' || c=='N'||c==27||c==3) return 1;
  } while (c!='y' && c!='Y');
  printf("\nFormatting...\n");
  for (track=0;track<32;track++)
    {
      printf("%d%%\r",percent);
      percent=track*100/32;
      for (sector=1;sector<=32;sector++)
	{
	  unsigned byte=0xE5;
	  outp(9,disknr);
	  outp(10,track);
	  outp(11,sector);
	  for (i=0;i<128;i++)
		{
		  if (sysgen && track<2) byte=sys[(track*32+sector-1)*128+i];
		  outp(12,byte);
		} // end outp loop
	}  // end sector
    } // end track 
  printf("Done\n");
  return 0;
}
  
