# CMakeLists for data/deftheme/MinimalDark-1.0.0

FILE(GLOB images "${CMAKE_CURRENT_SOURCE_DIR}/*.png")
FILE(GLOB themefiles "${CMAKE_CURRENT_SOURCE_DIR}/*.kvc")
LIST(APPEND files ${images} ${themefiles})

IF(UNIX)
	IF(APPLE)
		INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/Contents/Resources/themes/MinimalDark-1.0.0/)
	ELSE()
		# Assume linux
		INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/kvirc/${VERSION_BRANCH}/themes/MinimalDark-1.0.0/)
	ENDIF()
ELSEIF(WIN32)
	INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/themes/MinimalDark-1.0.0/)
ENDIF()
