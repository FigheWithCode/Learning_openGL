# LearnOpenGL

跟着 [LearnOpenGL](https://learnopengl.com) 用 C++ 做的练习仓库。当前进度到变换（Transformations）：窗口、三角形、着色器、纹理和矩阵变换都有对应可执行程序。

使用 **CMake** 构建，OpenGL **3.3 Core Profile**。窗口由 **GLFW** 创建，函数加载用仓库里的 **GLAD**，纹理用 **stb_image**，矩阵用 **GLM**。按 `Esc` 关闭窗口。

## 依赖

- CMake 3.16+
- C++17 编译器（gcc / clang）
- GLFW 3
- GLM
- 本机 OpenGL 驱动

GLAD 和 stb 已经在 `third_party/`，不用再下载。

Arch Linux：

```bash
sudo pacman -S cmake glfw glm gcc
```

Debian / Ubuntu：

```bash
sudo apt install cmake libglfw3-dev libglm-dev build-essential
```

## 编译

在项目根目录：

```bash
cmake -B build
cmake --build build
```

可执行文件在 `build/`。只编某一个：

```bash
cmake --build build --target Hello_Triangle
```

CLion 默认输出在 `cmake-build-debug/`，把下面命令里的 `build` 换成这个目录即可。

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
./build/HOMEWORK_SHADER
./build/SHADER_EXERCISE_LAST
./build/Texture_Learn
./build/Texture_Homework_1
./build/Texture_Homework_2
./build/Transforming_Learning
./build/Trans
```

从 `HOMEWORK_SHADER` 起，着色器是按绝对路径从源码目录读的。纹理程序还会读 `/home/Gal/Projects/textures_Pictures/` 里的图片（`wall.jpg`、`awesomeface.png`、`超时空辉夜姬.jpg`、`雪乃.jpg`）。换机器或改仓库位置时，要改对应 `.cpp` 里的路径。

## 目录结构

```text
learnopengl/
├── CMakeLists.txt
├── src/
│   ├── Windows.cpp                      # 创建窗口
│   ├── Hello_Triangle.cpp               # 三角形
│   ├── Shader.cpp                       # uniform 变色
│   ├── Shader_more_conttrib.cpp         # 顶点颜色插值
│   ├── Shader/Shader.h                  # 从文件加载着色器的类
│   ├── LearningTexture/                 # 纹理
│   ├── Transform_Learning/              # 变换
│   ├── Exercise/                        # 练习
│   └── Homework/                        # 作业
└── third_party/
    ├── glad/
    ├── stb/
    └── glm/
```

## 程序对照

| 可执行文件 | 源码 | 内容 |
| --- | --- | --- |
| `hello_window` | `src/Windows.cpp` | 创建 GLFW 窗口，青绿色背景 |
| `Hello_Triangle` | `src/Hello_Triangle.cpp` | 画一个白色三角形 |
| `exercise` | `src/Exercise/exercise.cpp` | 同时开两个窗口，背景色不同 |
| `exercise_1` | `src/Exercise/exercise_1.cpp` | 用 EBO 画矩形（两个三角形） |
| `homework_0` | `src/Homework/homework_0.cpp` | 一组顶点画两个橙色三角形 |
| `homework_0_1` | `src/Homework/homework_0_1.cpp` | 两个 VAO、两套着色器，蓝色和橙色三角形 |
| `Shader` | `src/Shader.cpp` | `uniform` 控制颜色，绿色随时间变化 |
| `Shader_more_conttrib` | `src/Shader_more_conttrib.cpp` | 顶点颜色传到片段着色器并插值 |
| `HOMEWORK_SHADER` | `src/Homework/Homework_Shader/` | 用 `Shader` 类从文件加载着色器，画彩色三角形 |
| `SHADER_EXERCISE_LAST` | `src/Exercise/Exercise_Shader/` | `uniform` 做水平偏移，并改变蓝色分量 |
| `Texture_Learn` | `src/LearningTexture/` | 矩形上混合两张纹理 |
| `Texture_Homework_1` | `src/Homework/Homework_texture/Texture_1/` | 方向键上下改变两张纹理的混合比例 |
| `Texture_Homework_2` | `src/Homework/Homework_texture/texture_2/` | 四个角使用不同的纹理坐标，只显示纹理中心一小块 |
| `Transforming_Learning` | `src/Transform_Learning/` | 矩形平移到右下角并绕 Z 轴旋转 |
| `Trans` | `src/Homework/Homework_Transform/` | 一个矩形旋转，另一个按时间缩放，各自贴不同纹理 |

## 学习顺序

1. Hello Window：`hello_window`
2. Hello Triangle：`Hello_Triangle`，然后 `exercise`、`exercise_1`、`homework_0`、`homework_0_1`
3. Shaders：`Shader`、`Shader_more_conttrib`、`HOMEWORK_SHADER`、`SHADER_EXERCISE_LAST`
4. Textures：`Texture_Learn`、`Texture_Homework_1`、`Texture_Homework_2`
5. Transformations：`Transforming_Learning`、`Trans`

## 参考

- [LearnOpenGL](https://learnopengl.com)
- [LearnOpenGL 中文版](https://learnopengl-cn.github.io)