# Learning_openGL
这是用来记录我学习opengl的过程所创建的仓库
# LearnOpenGL

跟着 [LearnOpenGL](https://learnopengl.com) 用 C++ 做的练习代码。

使用 **CMake** 构建，OpenGL 3.3 Core Profile，窗口和上下文由 **GLFW** 创建，函数加载用自带的 **GLAD**，纹理加载用 **stb_image**。

按 `Esc` 可以关闭窗口。

## 依赖

- CMake 3.16+
- C++17 编译器（gcc / clang）
- GLFW 3
- 本机 OpenGL 驱动

GLAD 和 stb 已经放在 `third_party/`，不用再单独下载。

Arch Linux：

```bash
sudo pacman -S cmake glfw gcc
```

Debian / Ubuntu：

```bash
sudo apt install cmake libglfw3-dev build-essential
```

## 编译

在项目根目录执行：

```bash
cmake -B build
cmake --build build
```

生成的可执行文件在 `build/` 里。

只编译某一个程序：

```bash
cmake --build build --target Hello_Triangle
```

## 运行

```bash
./build/hello_window
./build/Hello_Triangle
./build/exercise
./build/exercise_1
./build/homework_0
./build/homework_0_1
./build/Shader
./build/Shader_more_conttrib
./build/Shader_Class
./build/HOMEWORK_SHADER
./build/SHADER_EXERCISE_LAST
./build/Texture_Learn
```

> 部分程序（`Shader_Class`、`HOMEWORK_SHADER`、`SHADER_EXERCISE_LAST`、`Texture_Learn`）会从源码目录读取着色器文件，路径目前写在代码里。如果克隆到别的机器，需要改这些路径，或从对应源码目录运行。

## 目录结构

```text
learnopengl/
├── CMakeLists.txt
├── src/
│   ├── Windows.cpp                 # 创建窗口
│   ├── Hello_Triangle.cpp          # 三角形
│   ├── Shader.cpp                  # uniform 变色
│   ├── Shader_more_conttrib.cpp    # 顶点颜色插值
│   ├── Shader_Class/               # 着色器类封装
│   ├── LearningTexture/            # 纹理
│   ├── Exercise/                   # 练习
│   └── Homework/                   # 作业
└── third_party/
    ├── glad/                       # OpenGL 加载器
    └── stb/                        # stb_image
```

## 程序对照

| 可执行文件 | 源码 | 内容 |
| --- | --- | --- |
| `hello_window` | `src/Windows.cpp` | 创建 GLFW 窗口，清空为青绿色背景 |
| `Hello_Triangle` | `src/Hello_Triangle.cpp` | 绘制白色三角形 |
| `exercise` | `src/Exercise/exercise.cpp` | 同时打开两个窗口，背景色不同 |
| `exercise_1` | `src/Exercise/exercise_1.cpp` | 用 EBO 画两个三角形 |
| `homework_0` | `src/Homework/homework_0.cpp` | 用一组顶点画两个三角形 |
| `homework_0_1` | `src/Homework/homework_0_1.cpp` | 两个 VAO / 两套着色器，蓝、橙两个三角形 |
| `Shader` | `src/Shader.cpp` | `uniform` 控制颜色，随时间变绿 |
| `Shader_more_conttrib` | `src/Shader_more_conttrib.cpp` | 顶点颜色传到片段着色器并插值 |
| `Shader_Class` | `src/Shader_Class/` | 从文件加载着色器，彩色三角形 |
| `HOMEWORK_SHADER` | `src/Homework/Homework_Shader/` | 着色器类作业 |
| `SHADER_EXERCISE_LAST` | `src/Exercise/Exercise_Shader/` | 用 uniform 做位置偏移和颜色变化 |
| `Texture_Learn` | `src/LearningTexture/` | 给矩形贴纹理 |

## 学习顺序

建议按 LearnOpenGL 章节顺序运行：

1. Hello Window → `hello_window`
2. Hello Triangle → `Hello_Triangle`，然后看 `exercise` / `homework_0`
3. Shaders → `Shader` → `Shader_more_conttrib` → `Shader_Class`
4. Textures → `Texture_Learn`

## 参考

- [LearnOpenGL](https://learnopengl.com)
- [LearnOpenGL 中文版](https://learnopengl-cn.github.io)
