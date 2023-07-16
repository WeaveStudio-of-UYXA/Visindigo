# Visindigo Script
VisindigoScript是基于VSE虚拟机运行的脚本。其语法风格类似于Python，具体细节参考了Python和ES，总体思路相似于C++

VisindigoScript同时允许动态类型和静态类型，具体取决于是否在代码中使用类型标记符。

# 新建对象
新建对象语法为
```
var [var_name] = [const_value]
var [var_name] = new [class_name](para)
var [var_name] = [var_name_b]
```
这就是说，在新建对象上，VScript类似ES，以下范例都是对的：
* var a = 3
* var s = "str"
* var c = new cls()
* var d = a

通过以上方法建立的对象是动态类型的，除非用类型标记符显式的给定类型，例如：
* var a:int = 3
* var s:str = "str"
* var c:cls = new cls()

如果您尝试
* var s:str = new cls()

他可能会通过VISC（十分智障的默认VIS到VSEVM指令的编译器），但是运行时则会告警
> 对象 s 的赋值操作不支持类型错误的对象 cls


# 新建函数
你可以使用`fn`、`function`、`def`这三个关键字中的任意一个定义函数，以`def`为例，则形如：
```
def funcName(para):
    [body]
```
这和Python是完全一样的。

如果您也希望限定类型，那么可以采用也和Python完全一样的类型标注语法
```
def funcName(para:type)->rtn_type:
    [body]
```
Python中的类型标注仅仅是标注，但是VScript会检查参数和返回值类型是否是标记的类型，如果不是，运行时会报错。

需要注意，如果函数标注了返回类型但最后未执行return语句，函数会默认返回一个`None`。

您还能引入非Python的概念，通过关键字`as`，例如：
```
def funcName(para:type)->rtn_type as [permission] [-static] [polymorphic]
```

例如定义受保护的静态函数则有
```
def foo(a:int)->int as protected static:
```
例如定义公开虚函数则有
```
def foo(a:int)->int as public virtual:
```
如果您希望代码更加靠近自然语句，您可以在最后加上一个`function`，这不会影响解析，例如：
```
def getObjectName()->str as public function:
```

请注意，`as`关键字后出现的任何单词（除`function`）都必须是所谓“函数修饰词”，即限于：
* public \ private \ protected
* static
* virtual \ override \ final

以上三类关键字每一类只能同时出现一个，具体顺序不做规定，例如对于上文第一个foo函数，还可以写做：
```
def foo(a:int)->int as static protected function:
```

# 定义类