# CMakeLists for src/modules/reguser

SET(kvireguser_MOC_HDRS
	RegisteredUserEntryDialog.h
	RegistrationWizard.h
	RegisteredUsersDialog.h
)

SET(kvireguser_SRCS
	libkvireguser.cpp
	RegisteredUserEntryDialog.cpp
	RegistrationWizard.cpp
	RegisteredUsersDialog.cpp
)

# After this call, files will be moc'ed to moc_kvi_*.cpp
QT4_WRAP_CPP(kvireguser_MOC_SRCS ${kvireguser_MOC_HDRS})

SET(kvi_module_name kvireguser)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/module.rules.txt)
