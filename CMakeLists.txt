cmake_minimum_required(VERSION 2.8)
project( colorizationPatchesExtractor )

SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB SRC	
	  "main.cpp"
 
          "functions/*.hpp"
	  "headers/*.hpp"
)


add_executable( colorizationPatchesExtractor 
		${SRC})


target_link_libraries( colorizationPatchesExtractor 
		       ${OpenCV_LIBS} )

add_custom_command(TARGET colorizationPatchesExtractor POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"D:/lib/opencv/build/x64/vs2017/install/x64/vc15/bin/"
"$<TARGET_FILE_DIR:colorizationPatchesExtractor>"
)