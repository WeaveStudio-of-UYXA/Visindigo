# C++代码格式标准
**此文件给定此项目应该采取的代码格式标准，未尽项目不做要求**
# 核心构件代码
* Visindigo核心构件代码，例如`VIGeneralBehavior`等，其定义与实现分开编写。
* 核心构件代码采用`CommonEdit`风格书写，即引入CE宏关键字`_Public`，`_Private`，`_Protected`，`def_init`，`def_del`，`def_copy`，`ENUM`等，例如：
  ```C++
  class VIClass :public ...
  {
    _Public void foo(...);
    _Private int VAR1;
    _Public def_init VIClass(...):...(){...}
    _Protected int getVar1();
    _Public ENUM State{
        ...
    }
  }
  ```
  引入`CommonEdit`风格是为了统一核心构件代码的定义部分，确保这部分定义清晰明了，无需翻找上下文。
* 函数使用小驼峰命名法，私有变量采用全大写命名法，变量尽量不公用，使用函数进行访问。确需公有变量的，使用大驼峰命名法。
* 类、枚举使用小驼峰命名法。
    