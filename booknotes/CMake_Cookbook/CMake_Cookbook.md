# CMake Cookbook

构建**OBJECT**库

先生成`message`的`OBJECT`对象库
```CMake
add_library(message-objs
    OBJECT
    message.h message.cpp
)
```

使用对象库获取**静态库**(`message-static`)和**动态库**(`message-shared`)：

生成**静态库**
```CMake
add_library(message-static
    STATIC
    $<TARGET_OBJECTS:message-objs>
)
```
生成**动态库**
```CMake
add_library(message-static
    SHARED
    $<TARGET_OBJECTS:message-objs>
)
```
生成结果(Windows上)：
```
-a---          12/24/2024  8:42 AM         166444 libmessage-shared.dll
-a---          12/24/2024  8:42 AM           1716 libmessage-shared.dll.a
-a---          12/24/2024  8:42 AM          81250 libmessage-static.a
-a---          12/24/2024  8:25 AM          81250 libmessage.a
```

生成同名库，而不是`message-static`和`message-shared`：
```CMake
add_library(message-objs
    OBJECT
    message.h message.cpp
)

add_library(message-shared
    SHARED
    $<TARGET_OBJECTS:message-objs>
)

# 设置动态库输出名
set_target_properties(message-shared
    PROPERTIES
    OUTPUT_NAME "message"
)

add_library(message-static
    STATIC
    $<TARGET_OBJECTS:message-objs>
)

# 设置静态库输出名
set_target_properties(message_static
    PROPERTIES
    OUTPUT_NAME "message"
)
```


## 使用条件语句控制编译

**逻辑变量**的种类：
* 逻辑变量为`1`、`ON`、`YES`、`true`、`Y`或非零数时，则运行时的逻辑变量将为`true`。
* 逻辑变量为`0`、`OFF`、`NO`、`false`、`N`、`IGNORE`、`NOTFOUND`、空字符串，或者以`-NOTFOUND`为后缀，则逻辑变量为`false`。

例子：
```CMake
set(CMAKE_CXX_STANDARD 23)
set(USE_LIBRARY OFF)

message(STATUS "Compile sources into a library: ${USE_LIBRARY}")

set(BUILD_SHARED_LIBS OFF)

message(STATUS "Compile sources into a shared library: ${BUILD_SHARED_LIBS}")

list(APPEND _sources message.h message.cpp)

if(USE_LIBRARY) # USE_LIBRARY 值为 ON 时，构建并使用库
    add_library(message ${_sources})
    add_executable(cookbook cookbook.cpp)
    target_link_libraries(cookbook message)
else()          # USE_LIBRARY 值为 OFF 时，不单独构建库，直接使用
    add_executable(cookbook cookbook.cpp ${_sources})
endif()
```

## 为用户提供可选项

`option()`，以选项的形式显式逻辑开关，用于外部设置，从而切换构建系统的行为：

`option(USE_LIBRARY "Compile sources into a library" OFF)`，
此时`USE_LIBRARY`的默认值为`OFF`，用户可以在`CLI`中使用`-D`来指定`USE_LIBRARY`的值：

`cmake -D USE_LIBRARY=ON ..`手动指定`USE_LIBRARY`的值为`ON`。

语法:`option(<option_variable> "help string" [initial value])`：
* `<option_variable>`：选项的的变量的名称。
* `"help string"`：记录选项的字符串。
* `[initial value]`：选项的默认值。


当设置`USE_LIBRARY`为`ON`时，而`MAKE_STATIC_LIBRARY`或`MAKE_SHARED_LIBRARY`的值为`OFF`是没有意义的。

因此，可以设置这些选项之间的依赖，只有当某个变量的值符合要求时，另一个变量的值才有效：
```CMake
include(CMakeDependentOption)

cmake_dependent_option(
    MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
    "USE_LIBRARY" ON
)

cmake_dependent_option(
    MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
    "USE_LIBRARY" ON
)
```
此处，当`USE_LIBRARY`的值为`ON`时，`MAKE_STATIC_LIBRARY`的默认值为`OFF`，否则`MAKE_SHARED_LIBRARY`的默认值为`ON`：
`cmake -D USE_LIBRARY=OFF -D MAKE_SHARED_LIBRARY=ON ..`，不会构建库，因为`USE_LIBRARY`仍然为`OFF`。

## 指定编译器

`CMAKE_<LANG>_COMPILER`变量用来指定编译器，`LANG`的可指定值`C`、`C++`......

可以通过指定`CLI`的`-D`选项：
`cmake -D CMAKE_CXX_COMPILER=clang++`。此外，在`Linux`中，可以通过指定环境变量中的`CXX`(C++编译器)、`CC`(C编译器)来指定编译器：`export CXX=clang++ cmake ..`

## 获取 CMake 的配置信息
`cmake --system-information information.txt`，将配置信息写入`information.txt`文件，或者`cmake --system-information`直接在终端中输出信息。

其他的可与编译器交互的变量：
* `CMAKE_<LANG>_COMPILER_LOADED`：如果为项目启用了语言`<LANG>`，则将设置为`TRUE`。
* `CMAKE_<LANG>_COMPILER_ID`：编译器标识字符串，编译器供应商所特有。例如，`GCC`用于GNU编译器集合，
`AppleClang`用于`macOS`上的`Clang`,	`MSVC`用于`Microsoft	Visual Studio`编译器。注意，不能保证为所有编译器或语言定义此变量。
* `CMAKE_COMPILER_IS_GNU<LANG>`:如果语言`<LANG>`是`GNU`编译器集合的一部分，则将此逻辑变量设置为`TRUE`。注意变量名的`<LANG>`部分遵循`GNU`约定：C语言为`CC`，C++语言为`C++`，Fortran语言为`G77`。
* `CMAKE_<LANG>_COMPILER_VERSION`:此变量包含一个字符串，该字符串给定语言的编译器版本。版本信息在`major[.minor[.patch[.tweak]]]`中给出。但是，对于`CMAKE_<LANG>_COMPILER_ID`，不能保证所有编译器或语言都定义了此变量。

获取当前编译器相关的信息：
```CMake
message(STATUS "Is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")
if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Is the C++ from GUN? ${CMAKE_COMPILER_IS_GNUCXX}")
    message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

message(STATUS "Is the C compiler loaded? ${CMAKE_C_COMPILER_LOADED}")
if(CMAKE_C_COMPILER_LOADED)
    message(STATUS "The C compiler ID is: ${CMAKE_C_COMPILER_ID}")
    message(STATUS "Is the C++ from GNU? ${CMAKE_COMPILER_IS_GUNCC}")
    message(STATUS "The C compiler version is: ${CMAKE_C_COMPILER_VERSION}")
endif()
```

## 切换构建类型

可选的构建类型：
* 1.`Debug`：用于在没有优化的情况下，使用带有调试符号构建库或可执行文件。
* 2.`Release`：用于构建的优化的库或可执行文件，不包含调试符号。
* 3.`RelWithDebInfo`：用于构建较少的优化库或可执行文件，包含调试符号。
* 4.`MinSizeRel`：用于不增加目标代码大小的优化方式，来构建库或可执行文件。

设置默认构建类型：
```CMake
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
```
注：该变量被设置为缓存变量，可以通过缓存进行编辑，缓存文件中关于`CMAKE_BUILD_TYPE`的内容：
```CMake
//build type
CMAKE_BUILD_TYPE:STRING=Release
```

获取相关的编译标志：
```CMake
message(STATUS "C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C flags, Release configuration with debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags, Release configuration with debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "C++ flags, minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
```

`Visual Studio`支持复合配置生成器，即可以同时处理多个构建配置。

`CMAKE_CONFIGURATION_TYPES`变量可以对生成器的可用配置类型进行调整：`CMAKE_CONFIGURATION_TYPES="Release;Debug;RelWithDebInfo"`，还可以包括其它的构建类型，此处将为`Release`、`Debug`和`RelWithDebInfo`配置生成构建树，并且可以使用`--config`标志来指定构建哪一个类型配置：`cmake --build . --config Release`，指定`Release`类型构建。


