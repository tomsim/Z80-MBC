list
1 REM Patch MPC-Z80 CP/M 2.2 For 4 disk drives
2 REM Al Williams - Hackaday
5 REM config (we could use as little as 3+16*3+31*2=113 bytes
7 WADD=6 : WDATA=0: WADD1=0
9 REM I was going to "TSR" but vector at 0005 gets reset on warm boot so
10 ATOP=&HFD90 : REM Unused memory for patch
14 REM OLDDPA = LXI instruction for DPA, N1, N2 = references to 2 drives
15 OLDDPA=&HFBA5 : N1=&HFB44 : N2= &HFB97 
20 IF PEEK(OLDDPA)<>&H11 OR PEEK(N1)<>2 OR PEEK(N2)<>2 THEN GOTO 6000
25 WADD=OLDDPA+1:GOSUB 1000: OLDDP=WDATA
30 IF OLDDP<>64051! THEN GOTO 6000
115 REM set NDISKS
120 POKE N1,4
125 POKE N2,4
145 PRINT "Old DPBASE=";HEX$(OLDDP)
150 REM set up all 4 DBH - Copy DPH0 one time, then copy DPH1 3x and patch
160 WADD=OLDDP: WADD1=ATOP+3: GOSUB 2000
170 WADD=OLDDP+16: WADD1=ATOP+19: GOSUB 2000
180 WADD=OLDDP+16: WADD1=ATOP+35: GOSUB 2000
190 WADD=OLDDP+16: WADD1=ATOP+51: GOSUB 2000
200 REM patch ALL for DPH 2, and 3
210 WDATA=ATOP+68: WADD=ATOP+49: GOSUB 1050
215 REM 32 is actually one too large
220 WDATA=ATOP+68+32: WADD=ATOP+65:GOSUB 1050
222 WADD=OLDDPA+1: WDATA=ATOP+3: GOSUB 1050 : REM Set new DPBASE
224 REM uncomment next line for diagnostics
225 REM gosub 5000
230 PRINT "Patch Complete! Good luck!"
240 SYSTEM
1000 REM peekw: read word at address wadd to wdata
1010 WDATA=PEEK(WADD)+PEEK(WADD+1)*256
1020 RETURN
1050 REM pokew: write word at address wadd with wdata
1055 GOSUB 3000
1060 POKE WADD,LVAL
1070 POKE WADD+1,HVAL
1080 RETURN
2000 REM copy16: copy 16bytes at wadd to wadd1
2010 FOR I=0 TO 15
2020 POKE WADD1+I,PEEK(WADD+I)
2030 NEXT I
2040 RETURN
3000 REM hexcvt - split wdata into hval and lval with no overflow
3010 V$="000" + HEX$(WDATA)
3020 V$=RIGHT$(V$,4)
3030 HVAL=VAL("&H" + LEFT$(V$,2))
3040 LVAL=VAL("&H" + RIGHT$(V$,2))
3060 RETURN
5000 REM sanity check
5011 WADD=&HFBA5: PRINT "@FBA5:";HEX$(PEEK(WADD))
5012 WADD=&HFBA6: GOSUB 1000: PRINT "@FBA6:";HEX$(WDATA)
5015 FOR I=0 TO 63
5020 WADD=ATOP+I: WDATA=PEEK(WADD): PRINT "@";HEX$(WADD);":";HEX$(WDATA)
5025 NEXT I
5030 RETURN
6000 PRINT "Error! Version mismatch or already patched. Cowardly not patching."
6010 STOP
