// Al Williams Hackaday
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Specific for MPC Z80 -- does not use BIOS/BDOS calls but talks directly to IOS


int main(int argc, char *argv[])
{
  if (argc<2 || argc>4)
    {
      printf("Usage: FORMAT DRIVE [LABEL] [/S] where DRIVE is 0-3\nUse /S to do a system generation using the current\ndrive 0 system tracks (default for drive 0)");
      return 1;
    }
  unsigned sysgen=0;
  unsigned char sys[2*32*128];  // 8k Buffer for system tracks
  unsigned sec=0;
  unsigned disknr=atoi(argv[1]);
  unsigned int track, c, sector, i, j;
  unsigned int percent=0;
  char label[13];
  int argind=2;
  if (disknr<0||disknr>3)
    {
      printf("Unknown disk drive\n");
      return 1;
    }
  while (argc>argind)
    {
      if (argv[argind][0]=='/')
	{
	if ((argv[argind][1]=='s'|| argv[argind][1]=='S'))
	  {
	  sysgen=1;
	  argind++;
	  continue;
	  }
        else
	  {
	  printf("Unknown option: argv[argind]\n");
	  return 1;
	  }
	}
      strcpy(label+1,argv[argind]);  // label name
      argind++;
    }
      
  label[0]=(char)0x20;  // label marker for directory
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
  printf("This will format drive %d (%c:) as volume %s and destroy all contents on the drive. Are you sure? ",disknr,'A'+disknr,label+1);
  for (i=strlen(label);i<sizeof(label)-1;i++) label[i]=' '; // blank pad
  label[sizeof(label)-1]=(char)1;  // not '1' but 1  -- label marker

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
		  byte=0xE5;
		  if ((sysgen && track==2) || (sysgen==0 && track==0))
		    {
		      if (sector==1 && i<sizeof(label)) byte=label[i];
		    }
   	          else
		    if (sysgen && track<2) byte=sys[(track*32+sector-1)*128+i];
		  outp(12,byte);
		} // end outp loop
	}  // end sector
    } // end track 
  printf("Done\n");
  return 0;
}
  
