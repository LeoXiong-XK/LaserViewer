INCLUDE_DIRECTORIES(#${LASER_VIEW_SOURCE_DIR}/dep/freeglut/include
                    ${LASER_VIEW_SOURCE_DIR}/dep/lidar/include
                    ${LASER_VIEW_SOURCE_DIR}/src/base
                    )

LINK_DIRECTORIES(#${LASER_VIEW_SOURCE_DIR}/dep/freeglut/lib
                 ${LASER_VIEW_SOURCE_DIR}/dep/lidar/lib
                 ${LASER_VIEW_SOURCE_DIR}/src/base
                 )

ADD_SUBDIRECTORY(base)

#ADD_EXECUTABLE (sdk_demo sdk_demo.cpp)
#TARGET_LINK_LIBRARIES (sdk_demo lidar)

ADD_EXECUTABLE(rangeView RangeViewer.cpp )
TARGET_LINK_LIBRARIES(rangeView lidar)