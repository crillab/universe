if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/crillab-universe-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package crillab-universe)

install(
    DIRECTORY
    include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT crillab-universe_Development
)

install(
    TARGETS crillab-universe_crillab-universe
    EXPORT crillab-universeTargets
    RUNTIME #
    COMPONENT crillab-universe_Runtime
    LIBRARY #
    COMPONENT crillab-universe_Runtime
    NAMELINK_COMPONENT crillab-universe_Development
    ARCHIVE #
    COMPONENT crillab-universe_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)


if (VCPKG_TARGET_TRIPLET)
# Allow package maintainers to freely override the path for the configs
set(
    crillab-universe_INSTALL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/share/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
else ()
set(
    crillab-universe_INSTALL_CMAKEDIR "${CMAKE_INSTALL_INCLUDEDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
endif ()

mark_as_advanced(crillab-universe_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${crillab-universe_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT crillab-universe_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${crillab-universe_INSTALL_CMAKEDIR}"
    COMPONENT crillab-universe_Development
)

install(
    EXPORT crillab-universeTargets
    NAMESPACE crillab-universe::
    DESTINATION "${crillab-universe_INSTALL_CMAKEDIR}"
    COMPONENT crillab-universe_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
