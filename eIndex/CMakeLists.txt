# CMakeList.txt : CMake project for eIndex, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("eIndex")

# Add source to this project's executable.
add_executable (eIndex "eIndex.cpp" "eIndex.h" "general_fun.cpp" "general_fun.h" "help_fun.cpp" "help_fun.h" "settings.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET eIndex PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.


# Nakopirovanie DB suborov do build adresara (aby isli otvorit vzdy a vsetkym)
configure_file(${CMAKE_SOURCE_DIR}/users.txt ${CMAKE_BINARY_DIR}/users.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/subjects.txt ${CMAKE_BINARY_DIR}/subjects.txt COPYONLY)