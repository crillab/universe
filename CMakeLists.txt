cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)


if(COMPILE_GMP)
  list(APPEND VCPKG_MANIFEST_FEATURES "arbitrary-precision")
endif()

project(
    crillab-universe
    VERSION 0.1.0
    DESCRIPTION "mUlti laNguage unIfied intErface foR conStraint solvErs"
    HOMEPAGE_URL "https://github.com/crillab/universe"
    LANGUAGES CXX
)

set(PROJECT_VENDOR "Falque Thibault" "Wallon Romain")
set(PROJECT_CONTACT "falque@cril.fr" "wallon@cril.fr")


include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

find_package(crillab-easyjni REQUIRED)

if (COMPILE_GMP)
  find_package(PkgConfig REQUIRED)
endif()

add_compile_options()

file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/source/**.cpp)

file(GLOB_RECURSE HEADERS
        ${PROJECT_SOURCE_DIR}/include/**.hpp
        )

add_library(
    crillab-universe_crillab-universe
    ${SOURCES} ${HEADERS}
)

add_library(crillab-universe::crillab-universe ALIAS crillab-universe_crillab-universe)
target_link_libraries(crillab-universe_crillab-universe crillab-easyjni::crillab-easyjni)

if (COMPILE_GMP)
    pkg_check_modules(gmpxx REQUIRED IMPORTED_TARGET gmpxx)
    target_link_libraries(crillab-universe_crillab-universe PkgConfig::gmpxx)
endif()


if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crillab-universe_crillab-universe PUBLIC CRILLAB_UNIVERSE_STATIC_DEFINE)
endif()

set_target_properties(
    crillab-universe_crillab-universe PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME crillab-universe
    OUTPUT_NAME crillab-universe
)

target_include_directories(
    crillab-universe_crillab-universe ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/crillab-universe>"
)

target_include_directories(
    crillab-universe_crillab-universe SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(crillab-universe_crillab-universe PUBLIC cxx_std_20)


# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT crillab-universe_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of crillab-universe"
  )
endif()

include(cmake/dev-mode.cmake)
