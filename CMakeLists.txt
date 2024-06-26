cmake_minimum_required(VERSION 3.16)

project(altv-installer-for-linux VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick LinguistTools)

qt_standard_project_setup()

qt_add_executable(appaltv-installer-for-linux
    main.cpp
    vdf_parser.hpp
    utilities.h
)

qt_add_qml_module(appaltv-installer-for-linux
    URI altv-installer-for-linux
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES components/TitleBar.qml
    QML_FILES components/StackViewComponent.qml
    QML_FILES pages/InstallLocationPage.qml
    QML_FILES components/InstallerRadioButton.qml
    QML_FILES components/InstallerButtonLeft.qml
    QML_FILES components/InstallerButtonRight.qml
    QML_FILES components/InstallerDropDown.qml
    QML_FILES components/FolderPickerButton.qml
    QML_FILES components/InstallerCheckBox.qml
    QML_FILES pages/ShortcutsPage.qml
    QML_FILES components/InstallerPlatformButton.qml
    QML_FILES pages/GameLocationPage.qml
    QML_FILES pages/ConfirmPage.qml
    QML_FILES pages/DownloadPage.qml
    QML_FILES components/InstallerProgressBar.qml

    RESOURCES
    images/leftArrow.svg
    images/rightArrow.svg
    images/arrowDown.svg
    images/folderIcon.svg
    images/error.svg
    images/warning.svg
    SOURCES configuration.h configuration.cpp
    SOURCES downloaderinstaller.h downloaderinstaller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appaltv-installer-for-linux PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appaltv-installer-for-linux
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appaltv-installer-for-linux
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appaltv-installer-for-linux
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
