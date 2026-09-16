# Find mbelib-neo from explicit header/static-library paths, or from its
# installed CMake package when no paths are supplied.

set(LIBMBE_NEO_INCLUDE_DIR "" CACHE PATH "Directory containing mbelib-neo/mbelib.h")
set(LIBMBE_NEO_LIBRARY "" CACHE FILEPATH "Path to the mbelib-neo static library")
set(LIBMBE_NEO_FOUND FALSE)
set(LIBMBE_NEO_PKGCONFIG_REQUIRES "")

if (LIBMBE_NEO_INCLUDE_DIR OR LIBMBE_NEO_LIBRARY)
    if (NOT LIBMBE_NEO_INCLUDE_DIR OR NOT LIBMBE_NEO_LIBRARY)
        message(FATAL_ERROR "Set both LIBMBE_NEO_INCLUDE_DIR and LIBMBE_NEO_LIBRARY for a direct mbelib-neo build")
    endif()
    if (NOT EXISTS "${LIBMBE_NEO_INCLUDE_DIR}/mbelib-neo/mbelib.h")
        message(FATAL_ERROR "LIBMBE_NEO_INCLUDE_DIR must contain mbelib-neo/mbelib.h")
    endif()
    if (NOT EXISTS "${LIBMBE_NEO_LIBRARY}")
        message(FATAL_ERROR "LIBMBE_NEO_LIBRARY does not exist: ${LIBMBE_NEO_LIBRARY}")
    endif()

    set(LIBMBE_NEO_FOUND TRUE)
    if (NOT TARGET LibMbeNeo::LibMbeNeo)
        add_library(LibMbeNeo::LibMbeNeo STATIC IMPORTED)
        set_target_properties(LibMbeNeo::LibMbeNeo PROPERTIES
            IMPORTED_LOCATION "${LIBMBE_NEO_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${LIBMBE_NEO_INCLUDE_DIR}"
            INTERFACE_COMPILE_DEFINITIONS MBE_STATIC
        )
    endif()
else()
    find_package(mbe-neo 2 CONFIG QUIET)
    if (TARGET mbe_neo::mbe_shared)
        set(LIBMBE_NEO_FOUND TRUE)
        set(LIBMBE_NEO_PKGCONFIG_REQUIRES "libmbe-neo")
        if (NOT TARGET LibMbeNeo::LibMbeNeo)
            add_library(LibMbeNeo::LibMbeNeo INTERFACE IMPORTED)
            set_target_properties(LibMbeNeo::LibMbeNeo PROPERTIES
                INTERFACE_LINK_LIBRARIES mbe_neo::mbe_shared
            )
        endif()
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibMbeNeo REQUIRED_VARS LIBMBE_NEO_FOUND)

mark_as_advanced(LIBMBE_NEO_INCLUDE_DIR LIBMBE_NEO_LIBRARY)
