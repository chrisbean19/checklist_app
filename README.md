# Checklist App

This is a checklist app developed in C++.

## Dependencies

This app uses OpenGL, GLFW, GLAD, and ImGui for rendering, windows, and text. GLFW is prebuilt, and the other libraries are included as headers or compiled inside the app.

## Build

To build in Windows with G++, from the project folder run:
`g++ src/main.cpp src/glad.c src/imgui.cpp src/imgui_draw.cpp src/imgui_tables.cpp src/imgui_widgets.cpp src/imgui_impl_glfw.cpp src/imgui_impl_opengl3.cpp -Iinclude/imgui -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -o build/main.exe`

## Run

To run in Windows, from the project folder run:
`./build/main.exe`
