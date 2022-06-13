@echo off
setlocal

rem these build parameters must be set by the caller:
rem VISUAL_STUDIO, e. g. "msvc2013"
rem ARCHITECTURE, e. g. "x64"
rem GENERATOR, e. g. "Visual Studio 12 2013 Win64"

rem concatenate build directory
set BUILDRESULTS=%~dp0\..\..\BuildResults\%VISUAL_STUDIO%_%ARCHITECTURE%

rem create build directory and push into it
if not exist %BUILDRESULTS% mkdir %BUILDRESULTS%
pushd %BUILDRESULTS%

rem run CMake to build the solution
echo running CMake...
rem cmake.exe -G "%GENERATOR%" -T %TOOLSET% ../../VisaDll
cmake.exe -G "%GENERATOR%" ../../Software

popd

pause