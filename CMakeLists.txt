cmake_minimum_required(VERSION 2.8)
project( ExtractPatchesForRecolorization )

SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB SRC	
	  "main.cpp"
 
          "functions/*.hpp"
	  "headers/*.hpp"
)


add_executable( ExtractPatchesForRecolorization
		${SRC})


target_link_libraries( ExtractPatchesForRecolorization
		       ${OpenCV_LIBS} )

#You may want to change this for you own purpose
add_custom_command(TARGET ExtractPatchesForRecolorization POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"D:/lib/opencv/build/x64/vs2017/install/x64/vc15/bin/"
"$<TARGET_FILE_DIR:ExtractPatchesForRecolorization>"
)
