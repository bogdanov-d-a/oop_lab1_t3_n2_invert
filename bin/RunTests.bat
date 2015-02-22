@echo off

set loopIter=1
:LoopStart

Invert.exe %loopIter%.in > %loopIter%.tmp
fc %loopIter%.tmp %loopIter%.out

if %loopIter% lss 2 (
	set /a loopIter=%loopIter%+1
	goto LoopStart
)

pause
