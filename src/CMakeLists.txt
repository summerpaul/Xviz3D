
find_package(Eigen3 CONFIG REQUIRED)

set(XVIZ_ALL_DIRS
    "basis"
    "event"
    "camera"
    "opengl"
    "shader"

)

foreach(dir ${XVIZ_ALL_DIRS})
    file(GLOB_RECURSE header_files "${dir}/*.h" "${dir}/*.hpp" "${dir}/*.hxx")
    list(APPEND ALL_HEADERS ${header_files})
    file(GLOB_RECURSE src_files "${dir}/*.cpp" )
    list(APPEND ALL_SRCS ${src_files})
endforeach()


add_library(Xviz3dLib  ${ALL_SRCS} ${ALL_HEADERS})
target_link_libraries(Xviz3dLib    
    glad::glad  
    implot::implot 
    imgui::imgui
    imguizmo::imguizmo
    )
