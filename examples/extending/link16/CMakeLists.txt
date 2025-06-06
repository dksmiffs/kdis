#
# Headers & Sources
#
set(KDIS_EXAMPLES_EXTENDING_LINK16_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/KDIS)
set(KDIS_EXAMPLES_EXTENDING_LINK16_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

list(
  APPEND
  KDIS_HEADERS
  ${KDIS_EXAMPLES_EXTENDING_LINK16_HEADERS_DIR}/DataTypes/Enums/EnumLink16.hpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_HEADERS_DIR}/Extras/PDU_FactoryLink16.hpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_HEADERS_DIR}/PDU/Link16/Link16_Signal_PDU.hpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_HEADERS_DIR}/PDU/Link16/Link16_Transmitter_PDU.hpp
)
list(
  APPEND
  KDIS_SOURCES
  ${KDIS_EXAMPLES_EXTENDING_LINK16_SOURCES_DIR}/DataTypes/Enums/EnumLink16.cpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_SOURCES_DIR}/Extras/PDU_FactoryLink16.cpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_SOURCES_DIR}/PDU/Link16/Link16_Signal_PDU.cpp
  ${KDIS_EXAMPLES_EXTENDING_LINK16_SOURCES_DIR}/PDU/Link16/Link16_Transmitter_PDU.cpp
)

#
# Library
#
add_library(${PROJECT_NAME}_examples_extending_link16 ${KDIS_HEADERS} ${KDIS_SOURCES})
add_library(
  ${PROJECT_NAME}_examples_extending_link16::${PROJECT_NAME}_examples_extending_link16 ALIAS
  ${PROJECT_NAME}_examples_extending_link16
)
target_include_directories(
  ${PROJECT_NAME}_examples_extending_link16
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}
)
target_compile_definitions(
  ${PROJECT_NAME}_examples_extending_link16
  PRIVATE DIS_VERSION=${DIS_VERSION}
          $<$<BOOL:${KDIS_USE_ENUM_DESCRIPTORS}>:KDIS_USE_ENUM_DESCRIPTORS>
          $<$<BOOL:${BUILD_SHARED_LIBS}>:KDIS_EXPORTS>
)
# TODO target_compile_options( ${PROJECT_NAME}_examples_extending_link16 PRIVATE
# $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic
# -Werror> )
set_target_properties(
  ${PROJECT_NAME}_examples_extending_link16 PROPERTIES VERSION ${PROJECT_VERSION}
)
