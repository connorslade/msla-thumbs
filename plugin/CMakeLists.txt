cmake_minimum_required(VERSION 3.16)
project(msla-thumbs VERSION 0.1.0)

set(QT_MIN_VERSION "6.7.0")
set(KF_MIN_VERSION "6.0.0")


# ECM setup
find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(QtVersionOption)
include(ECMSetupVersion)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMDeprecationSettings)
include(ECMOptionalAddSubdirectory)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    XmlGui
    I18n
)

find_package(DolphinVcs REQUIRED)
set_package_properties(DolphinVcs PROPERTIES
    DESCRIPTION "the Dolphin version control plugin library"
    URL "https://commits.kde.org/dolphin"
    TYPE REQUIRED
    PURPOSE "Provides the version control plugin interface."
)

ecm_set_disabled_deprecation_versions(
    QT 6.5
    KF 5.240
)

add_definitions(-DTRANSLATION_DOMAIN=\"msla-thumbs\")

kcoreaddons_add_plugin(msla-thumbs
    SOURCES include/previews/lib.rs.cc src/msla_thumbs.cpp
    INSTALL_NAMESPACE "kf6/thumbcreator"
)
target_link_libraries(msla-thumbs
    KF6::KIOGui
    Qt::Gui
)
