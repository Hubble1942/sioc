@ECHO OFF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: (c) by Christian Ewald
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Scans the project folder for sources to include into the build.
:: Must be run each time a source file has been added/removed.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

PUSHD %~dp0

py -3 tools/sourcescanner.py

POPD
