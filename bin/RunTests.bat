@echo off

set loopIter=1
:LoopStart

del %loopIter%.tmp >nul 2>&1
Invert.exe %loopIter%.in > %loopIter%.tmp
fc %loopIter%.tmp %loopIter%.out
del %loopIter%.tmp

if %loopIter% lss 2 (
	set /a loopIter=%loopIter%+1
	goto LoopStart
)

pause
