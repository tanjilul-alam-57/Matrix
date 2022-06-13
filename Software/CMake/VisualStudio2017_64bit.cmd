@echo off
setlocal

rem define build parameters
set ARCHITECTURE=x64
set VISUAL_STUDIO=msvc2017
set GENERATOR=Visual Studio 15 2017 Win64

rem call script general for all ARCHITECTURE and Visual Studio versions
call %~dp0\VisualStudio_general.cmd
