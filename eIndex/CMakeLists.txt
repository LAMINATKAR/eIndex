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
add_executable (eIndex "eIndex.cpp" "eIndex.h" "general_fun.cpp" "general_fun.h" "edit_sub_fun.cpp" "edit_sub_fun.h"
        edit_sub_fun.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET eIndex PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.


# Nakopirovanie DB suborov do build adresara (aby isli otvorit vzdy a vsetkym)
configure_file(${CMAKE_SOURCE_DIR}/users.txt ${CMAKE_BINARY_DIR}/users.txt COPYONLY)

set(PREDMET_SUBORY
        subjects.txt
        BPC-MAT1.txt
        BPC-ZKR.txt
        BPC-PC1T.txt
        BPC-KOM.txt
        BPC-PNA.txt
)

foreach(subor IN LISTS PREDMET_SUBORY)
  configure_file(${CMAKE_SOURCE_DIR}/${subor} ${CMAKE_BINARY_DIR}/${subor} COPYONLY)
endforeach()
