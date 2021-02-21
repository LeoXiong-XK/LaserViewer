INCLUDE_DIRECTORIES(.)

SET(LIDAR_SRC lidar.cpp rOc_serial.cpp TimeOut.cpp opencv_writer.cpp)
ADD_LIBRARY(lidar ${LIDAR_SRC})