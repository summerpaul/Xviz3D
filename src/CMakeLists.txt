add_executable(demo main.cpp
                    app/app.cpp 
                    ui/main_layer.cpp
                    window/window.cpp
                    )
target_link_libraries(demo   
    glad::glad  
    imgui::imgui)