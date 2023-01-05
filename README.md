# Lua Embedded

> **NOTE:** <br>
> This project is actively developed and still working in progress.

**Lua Embedded** is a Lua fork that is specially optimized for embedded devices. Most of the original Lua features are preserved to ensure the maximum compatiblity. For complete information about Lua, visit [Lua.org](https://www.lua.org/).

## Major Modifications
* Disabled some uncommonly used built-in libraries.
* Extracted some system functions to the platform adaptor layer.
* Removed the dependencies of some system functions (eg. `time`), while maintaining the correctness of related functionalities.

## Build

TBD
