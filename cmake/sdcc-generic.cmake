set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER sdcc)
set(CMAKE_OBJCOPY sdobjcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_PACKIHX packihx CACHE INTERNAL "packihx tool")

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".lib")
set(CMAKE_IMPORT_LIBRARY_PREFIX )
set(CMAKE_IMPORT_LIBRARY_SUFFIX )
set(CMAKE_EXECUTABLE_SUFFIX ".ihx")
set(CMAKE_LINK_LIBRARY_SUFFIX ".lib")
set(CMAKE_DL_LIBS "")
set(CMAKE_C_OUTPUT_EXTENSION ".rel")

get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
find_program(SDCCLIB_EXECUTABLE sdcclib PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
find_program(SDCCLIB_EXECUTABLE sdcclib)
set(CMAKE_AR "${SDCCLIB_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian" FORCE)

if(NOT DEFINED CMAKE_C_FLAGS_INIT)
    set(CMAKE_C_FLAGS_INIT "-mstm8 -lstm8 --std-c11 --opt-code-size")
endif()

if(NOT DEFINED CMAKE_EXE_LINKER_FLAGS_INIT)
    set (CMAKE_EXE_LINKER_FLAGS_INIT "")
endif()

set(CMAKE_C_COMPILE_OBJECT  "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <OBJECTS> --out-fmt-ihx -o  <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>")

set(CMAKE_C_CREATE_STATIC_LIBRARY
        "\"${CMAKE_COMMAND}\" -E remove <TARGET>"
        "<CMAKE_AR> -a <TARGET> <LINK_FLAGS> <OBJECTS> ")

set(CMAKE_C_CREATE_SHARED_LIBRARY "")
set(CMAKE_C_CREATE_MODULE_LIBRARY "")

add_definitions(-D__SDCC__)
