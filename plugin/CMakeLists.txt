cmake_minimum_required(VERSION 3.16)
project(msla-thumbs VERSION 0.1.0)

set(QT_MIN_VERSION "6.7.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(KF6 REQUIRED COMPONENTS KIO)
kcoreaddons_add_plugin(msla-thumbs SOURCES include/previews/lib.rs.cc src/msla_thumbs.cpp INSTALL_NAMESPACE "kf6/thumbcreator")
target_link_libraries(msla-thumbs ${CMAKE_CURRENT_SOURCE_DIR}/include/libpreviews.a KF6::KIOGui)
