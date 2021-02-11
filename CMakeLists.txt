cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
 #set(CMAKE_CXX_STANDARD 20)


project(ProjetPhong)

add_executable(ProjetPhong vendor/glad/src/glad.c src/main.cpp src/Shader.cpp src/Shader.h src/Helpers/FileHelper.cpp src/Helpers/FileHelper.h src/Mesh.cpp src/Mesh.h src/Dragon.h src/Engine.cpp src/Engine.h src/Object.cpp src/Object.h src/Camera.cpp src/Camera.h src/Texture.cpp src/Texture.h src/stb_image.h src/Transform.cpp src/Transform.h src/Material.cpp src/Material.h src/Light.cpp src/Light.h)
target_compile_features(ProjetPhong PRIVATE cxx_std_20)

target_include_directories(ProjetPhong PRIVATE
		"vendor/glad/include"
		"vendor/glfw-3.3.2/include"
		"vendor/glm-0.9.9.8")

target_link_directories(ProjetPhong PRIVATE
		"vendor/glfw-3.3.2/lib")

target_link_libraries(ProjetPhong PRIVATE
		glfw3)

add_custom_command(TARGET ProjetPhong PRE_BUILD
		COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")