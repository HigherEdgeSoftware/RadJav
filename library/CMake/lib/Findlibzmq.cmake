message (STATUS "Searching for libzmq...")

set (libzmq_SOURCE $ENV{libzmq_SOURCE} CACHE PATH "libzmq path")
fixPath (libzmq_SOURCE)
set (libzmq_SEARCH_PATHS ${libzmq_SOURCE} ${RADJAV_DEPENDENCIES})

searchForHeader (libzmq zmq.h "${libzmq_SEARCH_PATHS}" FALSE)
#searchForLibrary (libzmq libzmq libzmq "${libzmq_SEARCH_PATHS}")

hasLibBeenFound (libzmq)

