@echo off

pushd \Debug
cl -Zi ..\ProjectLife\main.cpp user32.lib
popd