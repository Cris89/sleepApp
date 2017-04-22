# - Check for the presence of HEEL
#
# The following variables are set when HEEL is found:
#  HAVE_HEEL       = Set to true, if all components of HEEL
#                          have been found.
#  HEEL_INCLUDES   = Include path for the header files of HEEL
#  HEEL_LIBRARIES  = Link these to use HEEL


set(HEEL_SOURCE_PATH /home/cris/projects/sleepApp/margot_heel_if )
set(HEEL_BUILD_PATH /home/cris/projects/sleepApp/margot_heel_if/build )
set(HEEL_INSTALL_PATH /usr/local )


## -----------------------------------------------------------------------------
## Check for the header files

find_path (HEEL_INCLUDES margot.hpp
  PATHS /usr/local/include /usr/include ${HEEL_INSTALL_PATH}/include ${HEEL_SOURCE_PATH} ${CMAKE_EXTRA_INCLUDES}
  )

## -----------------------------------------------------------------------------
## Check for the library

find_library (HEEL_LIBRARIES libmargot_heel_if.a margot_heel_if
  PATHS /usr/local/lib /usr/lib /lib ${HEEL_INSTALL_PATH}/lib ${HEEL_BUILD_PATH} ${CMAKE_EXTRA_LIBRARIES}
  )

## -----------------------------------------------------------------------------
## Actions taken when all components have been found

if (HEEL_INCLUDES AND HEEL_LIBRARIES)
  set (HAVE_HEEL TRUE)
else (HEEL_INCLUDES AND HEEL_LIBRARIES)
  if (NOT HEEL_FIND_QUIETLY)
    if (NOT HEEL_INCLUDES)
      message (STATUS "Unable to find HEEL header files!")
    endif (NOT HEEL_INCLUDES)
    if (NOT HEEL_LIBRARIES)
      message (STATUS "Unable to find HEEL library files!")
    endif (NOT HEEL_LIBRARIES)
  endif (NOT HEEL_FIND_QUIETLY)
endif (HEEL_INCLUDES AND HEEL_LIBRARIES)

if (HAVE_HEEL)
  if (NOT HEEL_FIND_QUIETLY)
    message (STATUS "Found components for HEEL")
    message (STATUS "HEEL_INCLUDES .... = ${HEEL_INCLUDES}")
    message (STATUS "HEEL_LIBRARIES ... = ${HEEL_LIBRARIES}")
  endif (NOT HEEL_FIND_QUIETLY)
else (HAVE_HEEL)
  if (HEEL_FIND_REQUIRED)
    message (FATAL_ERROR "Could not find HEEL!")
  endif (HEEL_FIND_REQUIRED)
endif (HAVE_HEEL)

mark_as_advanced (
  HAVE_HEEL
  HEEL_LIBRARIES
  HEEL_INCLUDES
  )
