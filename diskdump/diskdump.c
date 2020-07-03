#include <stdio.h>
#include <stdlib.h>

unsigned int check(unsigned int v)
{
  return (~v+1)&0xFF;
}


int main(int argc, char *argv[])
{
  if (argc!=2)
    {
      printf("Usage: DISKDUMP DRIVE where DRIVE is 0-3\n");
      return 1;
    }
  unsigned char buf[128];
  unsigned sec=0;
  unsigned disknr=atoi(argv[1]);
  printf("Dumping disk %d\n",disknr);
  unsigned int track, subtrack, sector, i, j;
  unsigned int csum, addr;
  printf("Ready terminal capture and press Enter:");
  getchar();
  for (track=0;track<32;track+=8)
    {
      printf("************ Section %d\n",sec++);
      printf(":00%04X09%02X\n",disknr,check(9+disknr));
      csum=check(2+4+(track<16?0:1));
      printf(":02000004%04X%02X\n",track<16?0:1,csum);
      for (subtrack=0;subtrack<8;subtrack++)
	{
	  for (sector=1;sector<=32;sector++)
	    {
	      outp(9,disknr);
	      outp(10,track+subtrack);
	      outp(11,sector);
	      for (i=0;i<128;i++)
		{
		  buf[i]=inp(6);
		}
	      for (i=0;i<128;i+=32)
		{
		  addr=((track+subtrack)*32+(sector-1))*128+i;
		  printf(":20%04X00",addr);
		  csum=32+(addr>>8)+(addr&0xFF);
		  for (j=0;j<32;j++)
		    {
		      csum=csum+buf[i+j];
		      printf("%02X",buf[i+j]);
		    }
		  printf("%02X\n",check(csum));
		}
	    }
	}
      printf(":00000001FF\n\n\n");
    }
  printf("Done\n");
  return 0;
}
  
