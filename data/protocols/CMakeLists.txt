IF(KDE4_FOUND)
	INSTALL(FILES _irc.protocol
          DESTINATION ${SERVICES_INSTALL_DIR}
          RENAME irc.protocol
          )
	INSTALL(FILES _irc6.protocol
          DESTINATION ${SERVICES_INSTALL_DIR}
          RENAME irc6.protocol
          )
ENDIF(KDE4_FOUND)
