cmake_minimum_required(VERSION 3.16)
project(learnopengl C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(hello_window
        src/Windows.cpp
  third_party/glad/src/glad.c
)

target_include_directories(hello_window PRIVATE
  third_party/glad/include
)

target_link_libraries(hello_window PRIVATE
  glfw
  OpenGL::GL
)


add_executable(Hello_Triangle
        src/Hello_Triangle.cpp
        third_party/glad/src/glad.c
)

target_include_directories(Hello_Triangle PRIVATE
        third_party/glad/include
)

target_link_libraries(Hello_Triangle PRIVATE
        glfw
        OpenGL::GL
)


add_executable(exercise
        src/Exercise/exercise.cpp
        third_party/glad/src/glad.c
)

target_include_directories(exercise PRIVATE
        third_party/glad/include
)

target_link_libraries(exercise PRIVATE
        glfw
        OpenGL::GL
)



add_executable(exercise_1
        src/Exercise/exercise_1.cpp
        third_party/glad/src/glad.c
)

target_include_directories(exercise_1 PRIVATE
        third_party/glad/include
)

target_link_libraries(exercise_1 PRIVATE
        glfw
        OpenGL::GL
)


add_executable(homework_0
        src/Homework/homework_0.cpp
        third_party/glad/src/glad.c
)
target_include_directories(homework_0 PRIVATE
        third_party/glad/include
)
target_link_libraries(homework_0 PRIVATE
        glfw
        OpenGL::GL
)



add_executable(homework_0_1
        src/Homework/homework_0_1.cpp
        third_party/glad/src/glad.c
)
target_include_directories(homework_0_1 PRIVATE
        third_party/glad/include
)
target_link_libraries(homework_0_1 PRIVATE
        glfw
        OpenGL::GL
)

add_executable(Shader
        src/Shader.cpp
        third_party/glad/src/glad.c
)
target_include_directories(Shader PRIVATE
        third_party/glad/include
)
target_link_libraries(Shader PRIVATE
        glfw
        OpenGL::GL
)

add_executable(Shader_more_conttrib
        src/Shader_more_conttrib.cpp
        third_party/glad/src/glad.c
)
target_include_directories(Shader_more_conttrib PRIVATE
        third_party/glad/include
)
target_link_libraries(Shader_more_conttrib PRIVATE
        glfw
        OpenGL::GL
)

add_executable(Shader_Class
        src/Shader_Class/SHADER_lAST.cpp
        src/Shader_Class/SHADER.cpp
        third_party/glad/src/glad.c
)
target_include_directories(Shader_Class PRIVATE
        src/Shader_Class
        third_party/glad/include
)
target_link_libraries(Shader_Class PRIVATE
        glfw
        OpenGL::GL
)

add_executable(HOMEWORK_SHADER
        src/Homework/Homework_Shader/Shader.cpp
        src/Homework/Homework_Shader/SHADER.cpp
        third_party/glad/src/glad.c
)
target_include_directories(HOMEWORK_SHADER PRIVATE
        src/Homework/Homework_Shader
        third_party/glad/include
)
target_link_libraries(HOMEWORK_SHADER PRIVATE
        glfw
        OpenGL::GL
)

add_executable(SHADER_EXERCISE_LAST
        src/Exercise/Exercise_Shader/Exercise_Shader.cpp
        src/Exercise/Exercise_Shader/HOMEWORK_SHADER.cpp
        third_party/glad/src/glad.c
)
target_include_directories(SHADER_EXERCISE_LAST PRIVATE
        src/Exercise/Exercise_Shader
        third_party/glad/include
)
target_link_libraries(SHADER_EXERCISE_LAST PRIVATE
        glfw
        OpenGL::GL
)

add_executable(Texture_Learn
        src/LearningTexture/Texture.cpp
        src/LearningTexture/TEXTURES.cpp
        third_party/glad/src/glad.c
)
target_include_directories(Texture_Learn PRIVATE
        src/LearningTexture
        third_party/glad/include
        third_party/stb
)
target_link_libraries(Texture_Learn PRIVATE
        glfw
        OpenGL::GL
)