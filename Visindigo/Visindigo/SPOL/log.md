# 基本单元

* 变量声明
  * 变量创建 var 
* 变量赋值
  * 变量赋值 =
* 变量枚举
  * 函数参数列举
  * 条件表达式
* 调用函数
  * 任意函数
  * 逻辑函数（if-else,while,for,switch-case）

# 标准语法范例

def fun1(var b,var c)
    return b+c

def main()
    var a = fun1(3, 4)

# 语法抽象

* 一切括号均抽象为列表，函数名称后的一个单元视为此函数参数，故有 def fun(para)