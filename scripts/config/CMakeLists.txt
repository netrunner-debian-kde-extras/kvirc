# CMakeLists for scripts/config
# Create bin
IF(WANT_COEXISTENCE)
	SET(KVIRC_CONFIG ${PACKAGE}${VERSION_MAJOR}-config)
ELSE()
	SET(KVIRC_CONFIG ${PACKAGE}-config)
ENDIF()

# Install target
IF(UNIX)
	IF(NOT APPLE)
		# This files are useless because apple bundles are movable
		# Assume linux
		INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${KVIRC_CONFIG} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
	ENDIF()
ENDIF()
