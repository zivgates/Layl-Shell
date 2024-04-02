# Registry Command


Syntax: `reg *dowhat *hkey *regpath ^valuename (only for -w) ^datatype (only for -w) ^action (opt) (only for -w)`

Edits The Windows Registry

dowhat path can be -c to create a reg, -d to delete, and -w to write

hkey can be HKCR, HKCU, HKLM, HKU, or HKCC

path is the path to the registry key