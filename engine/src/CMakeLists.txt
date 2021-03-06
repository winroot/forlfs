FILE(GLOB_RECURSE ALL_SRC_FILES *.cpp *.c *.cc)
AUX_SOURCE_DIRECTORY(../../utils/src/ UTILS)

LIST(APPEND ALL_SRC_FILES ${UTILS})
SET(MAIN_SRC ${ALL_SRC_FILES})

LIST(REMOVE_ITEM ALL_SRC_FILES sample.cpp.bak)
SET(LIB_SRC ${ALL_SRC_FILES})

ADD_LIBRARY(${PROJECT_NAME} STATIC ${LIB_SRC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS})

IF (ENABLE_CUDA)
    set(CUDA_NVCC_FLAGS ${CMAKE_CXX_FLAGS_RELEASE};${CUDA_NVCC_FLAGS}; -DUSE_CUDA)
    file(GLOB_RECURSE CUDA_FILES *.cu)
    set(PROJECT_ENGINE_CUDA_LIB ${PROJECT_NAME}_cuda)
    cuda_add_library(${PROJECT_ENGINE_CUDA_LIB} ${CUDA_FILES})
    target_link_libraries(${PROJECT_NAME} ${PROJECT_ENGINE_CUDA_LIB})
ENDIF ()

SET(CMAKE_CXX_FLAGS_DEBUG " $ENV{CXXFLAGS} -std=c++11 -DDEBUG -DUSE_CUDA -DDLIB_NO_GUI_SUPPORT -g  -w")
SET(CMAKE_CXX_FLAGS_RELEASE " $ENV{CXXFLAGS} -std=c++11 -DNDEBUG -DUSE_CUDA -DDLIB_NO_GUI_SUPPORT -O3 -w")

INSTALL(DIRECTORY model engine log DESTINATION ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/dist/include/matrix_engine FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY processor DESTINATION ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/dist/include/matrix_engine FILES_MATCHING PATTERN "processor.h")
INSTALL(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../lib/matrix_engine/${PLATFORM})
INSTALL(TARGETS ${PROJECT_ENGINE_CUDA_LIB} ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../lib/matrix_engine/${PLATFORM})
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/dist/include/matrix_engine DESTINATION ${PROJECT_SOURCE_DIR}/../include/)
