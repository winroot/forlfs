AUX_SOURCE_DIRECTORY(. SRC_LIST)
AUX_SOURCE_DIRECTORY(../src/model SRC_PROTO)
AUX_SOURCE_DIRECTORY(../src/service SRC_SERVICE)

LIST(APPEND SRC_LIST ${SRC_PROTO} ${SRC_SERVICE})

ADD_EXECUTABLE(witness_tool ${SRC_LIST})


TARGET_LINK_LIBRARIES(witness_tool ${LIBS})

INSTALL(TARGETS witness_tool RUNTIME DESTINATION  ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)
