IF(KDE4_FOUND)
	INSTALL(FILES _irc.protocol DESTINATION ${SERVICES_INSTALL_DIR})
	INSTALL(FILES _irc6.protocol DESTINATION ${SERVICES_INSTALL_DIR})
ENDIF(KDE4_FOUND)
