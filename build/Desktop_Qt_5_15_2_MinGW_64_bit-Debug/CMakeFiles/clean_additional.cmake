# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Zora_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Zora_autogen.dir\\ParseCache.txt"
  "Zora_autogen"
  )
endif()