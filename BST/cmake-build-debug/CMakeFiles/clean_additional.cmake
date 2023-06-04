# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BST_autogen"
  "CMakeFiles\\BST_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BST_autogen.dir\\ParseCache.txt"
  )
endif()
