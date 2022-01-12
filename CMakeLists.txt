cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(StereoMatchGPU)

set(PRJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${PRJ_DIR}/CMAKE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PRJ_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PRJ_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${PRJ_DIR}/bin)

include(FindGLEW)
include(FindGLUT)
include(FindFreeGlut)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${CUDA_TOOLKIT_INCLUDE})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIR})
include_directories(${FreeGlut_INCLUDE_DIR})
include_directories(${PRJ_DIR}/src)
include_directories(E:/Code/CUDAStereoMatching/SDK/cub-1.7.0)

# 配置GPU计算参数
set(CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -gencode arch=compute_30,code=sm_30
    )

add_definitions(-DREAL_TYPE_FP32)

FILE(GLOB_RECURSE StereoINCLUDES "src/*.h")
FILE(GLOB_RECURSE StereoSOURCES "src/*.cpp")
FILE(GLOB_RECURSE StereoSOURCES_CU "src/*.cu")

FILE(GLOB_RECURSE KERNEL_INCLUDES "src/Kernels/*.h")
FILE(GLOB_RECURSE KERNEL_SOURCES_CU "src/Kernels/*.cu")

FILE(GLOB_RECURSE DELAUNAY_INCLUDES "src/delaunay/*.h")
FILE(GLOB_RECURSE DELAUNAY_SOURCES "src/delaunay/*.cpp")

FILE(GLOB_RECURSE GDEL2D_INCLUDES "src/delaunay/gDel2D/*.h")
FILE(GLOB_RECURSE GDEL2D_CPU_INCLUDES "src/delaunay/gDel2D/CPU/*.h")
FILE(GLOB_RECURSE GDEL2D_CPU_SOURCES "src/delaunay/gDel2D/CPU/*.cpp")
FILE(GLOB_RECURSE GDEL2D_GPU_INCLUDES "src/delaunay/gDel2D/GPU/*.h")
FILE(GLOB_RECURSE GDEL2D_GPU_SOURCES "src/delaunay/gDel2D/GPU/*.cu")

#source_group("Stereo Match Header Files" Files ${StereoINCLUDES})
#source_group("Stereo Match Source Files" Files ${StereoSOURCES})
#source_group("Stereo Match Cuda Source Files" Files ${StereoSOURCESCU})
#source_group("Kernel Header Files" Files ${KERNEL_INCLUDES})
#source_group("Kernel Source Files" Files ${KERNEL_SOURCES_CU})
#source_group("Delaunay Header Files" Files ${DELAUNAY_INCLUDES})
#source_group("Delaunay Source Files" Files ${DELAUNAY_SOURCES})
#source_group("gDel2D CPU Header Files" Files ${GDEL2D_CPU_INCLUDES})
#source_group("gDel2D CPU Source Files" Files ${GDEL2D_CPU_SOURCES})
#source_group("gDel2D GPU Header Files" Files ${GDEL2D_GPU_INCLUDES})
#source_group("gDel2D GPU Source Files" Files ${GDEL2D_GPU_SOURCES})

CUDA_ADD_EXECUTABLE(${PROJECT_NAME}
	${StereoINCLUDES}
	${StereoSOURCES}
	${StereoSOURCES_CU}
	${KERNEL_INCLUDES}
	${KERNEL_SOURCES_CU}
	${DELAUNAY_INCLUDES}
	${DELAUNAY_SOURCES}
	${GDEL2D_INCLUDES}
	${GDEL2D_CPU_INCLUDES}
	${GDEL2D_CPU_SOURCES}
	${GDEL2D_GPU_INCLUDES}
	${GDEL2D_GPU_SOURCES}
    )

#set(CMAKE_VERBOSE_MAKEFILE "ON")
target_link_libraries(${PROJECT_NAME} 
	${OpenCV_LIBS} 
	${OPENGL_LIBRARIES} 
	${GLEW_LIBRARIES} 
	${GLUT_LIBRARY} 
	${FreeGlut_LIBRARY}
	)

#add_executable(Example ./example/Main.cpp)
#target_link_libraries(Example ${PROJECT_NAME})



