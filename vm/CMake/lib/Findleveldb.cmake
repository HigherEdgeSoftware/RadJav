message (STATUS "Searching for leveldb...")

set (leveldb_SOURCE $ENV{leveldb_SOURCE} CACHE PATH "leveldb path")
fixPath (leveldb_SOURCE)
set (leveldb_SEARCH_PATHS ${leveldb_SOURCE} ${RADJAV_DEPENDENCIES})

searchForHeader (leveldb db.h "${leveldb_SEARCH_PATHS}" TRUE)
searchForLibrary (leveldb leveldb leveldb "${leveldb_SEARCH_PATHS}")

if (NOT WIN32)
	searchForLibrary (leveldb memenv memenv "${leveldb_SEARCH_PATHS}")
endif ()

hasLibBeenFound (leveldb)
