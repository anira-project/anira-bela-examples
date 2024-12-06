# ==============================================================================
# Install the executable
# ==============================================================================

# for CMAKE_INSTALL_INCLUDEDIR and others definition
include(GNUInstallDirs)

if (ANIRA_WITH_INSTALL)
    list(APPEND CUSTOM_RPATH "$ORIGIN/../lib")
else()
    list(APPEND CUSTOM_RPATH "/root/anira/lib")
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        INSTALL_RPATH "${CUSTOM_RPATH}"
)

# install the target
install(TARGETS ${PROJECT_NAME}
    # these get default values from GNUInstallDirs
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
)
