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







