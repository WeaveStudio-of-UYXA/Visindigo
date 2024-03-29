# Application Remote Call Protocol
ARCP是适用于应用程序远程调用过程的协议，此协议具有以下特点：
1. 总体按RIFF思路设计
2. 按函数调用设计报文格式
3. 明文传输，不加密
4. 传输数据类型严格序列化，可以快速解析
5. 要求一切可读的字符串都是UTF-8编码
6. 务必注意所有uint类型的数据段都是**小端序**，其他char[]类型的数据段都是**原始序**

因此，不应该通过ARCP传输隐私数据，或直接向互联网进行公开。ARCP应当仅被用作本地程序间或受信任的安全远程连接中的远程程序间的通信协议。

# ARCP 报文组成
ARCP报文由若干的Chunk组成，每一个Chunk都遵循一个通用格式，称为Data Chunk。特别的，第一个Chunk是一种名为ARCP Chunk的特化后的Data Chunk，用于标识ARCP报文的类型和版本。而第二个Chunk根据报文类型不同，有不同的格式，分为CALL Chunk和RETN Chunk，分别用于调用和返回。CALL Chunk和RETN Chunk都是Data Chunk的特化，它们的格式在Data Chunk的基础上显示规定了一些字段，用于标识函数名、参数数量、状态码等信息。

## Data Chunk

* uint32 ：数据段长度L1（字节）
* uint16：类型名长度L2（字节）
* char[ L1 ] ：数据段
* char[ L2 ] ：类型名

其中的数据段和类型名都是可选的，如果不需要某个部分，将对应的L1或L2设置为0即可。但无论如何，Chunk的长度至少为48位，即6字节。

## ARCP Chunk
这是一种特殊的Data Chunk，作为ARCP报文的头部，用于标识ARCP报文的类型和版本，其格式如下：
* uint32：固定为 8（注意为小端序）
* uint16：协议版本号长度 2
* uint64：“ARCP\r\n\r\n"的字面连续值0x415243500D0A0D0A（注意为小端序）
* uint16：协议版本号

以版本号为0x0001的ARCP Chunk为例，其内容应该固定如下的16个字节：

0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0A, 0x0D   
> 8 0 0 0 2 0 \n \r
>
0x0A, 0x0D, 0x50, 0x43, 0x52, 0x41, 0x01, 0x00
>  \n \r P C R A 1 0

## CALL Chunk
在调用时，第二个Chunk为 CALL Chunk，它也是一个符合Data Chunk格式但有具体内容定义的区块，即：
* uint32：固定为 8 （注意为小端序）
* uint16：函数名长度L2（字节）
* uint32：“CALL”的字面连续值0x43414C4C（注意为小端序）
* uint32：参数数量N（字节）
* char[ L2 ] ：函数名

此Chunk后方N个Chunk为 Data Chunk。
参数数量N必须和后方的Chunk数量相同，这影响对方的解析策略，如果对方按N解析后，下一个Chunk不是ARCP Chunk（即下一报），则对方有权断开连接。

N可以为0。

## Retn Chunk
在返回时，第二个Chunk为 RETN Chunk，它和CALL Chunk类似，其格式如下：
* uint32：固定为 8 （注意为小端序）
* uint16：状态码长度 2
* uint32：“RETN" 的字面连续值0x5245544E（注意为小端序）
* uint32：返回值数量N（字节）
* uint16：状态码

此Chunk后方N个Chunk为 Data Chunk。
返回值数量N必须和后方的Chunk数量相同，这影响对方的解析策略，如果对方按N解析后，下一个Chunk不是ARCP Chunk（即下一报），则对方有权断开连接。

N可以为0。

# ARCP CHUNK 匹配标准
1. 前14个字节是上文中描述的固定内容
2. 最后2字节是版本号且是本地支持的版本号
3. 是第一个Chunk


# 状态码
ARCP状态码用于返回时标识调用的执行状态，或在解析过程中标识解析的执行状态。状态码分为通识状态码、调用状态码和解析状态码。
## 通识状态码
通识状态码不仅用于ARCP报文中，也在ARCP终端内部使用。
| 0x00** 通识状态码 | 描述 |
| --- | --- |
| 0x0000 | 成功 |
| 0x0001 | 未知错误 |
| 0x0002 | 内部异常 |
| 0x0003 | 链接断开 |

## 调用状态码
调用状态码用于表示调用的执行状态，一般见于ARCP报文中。
| 0x01** 调用状态码 | 描述 |
| --- | --- |
| 0x0101 | 未知函数 |
| 0x0102 | 参数类型不匹配 |
| 0x0103 | 参数数量不匹配 |
| 0x0104 | 对方抛出异常 |
| 0x0105 | 应向第一个返回值出示的函数名重新调用函数（重定向） |
| 0x0106 | 此函数已经注册，但未实现 |

## 解析状态码
解析状态码用于表示解析过程中的错误，一般在ARCP终端内部使用。
| 0x02** 解析状态码 | 描述 |
| --- | --- |
| 0x0201 | Chunk 解析错误 |
| 0x0202 | 没有CALL Chunk |
| 0x0203 | 没有RETN Chunk |
| 0x0204 | CALL Chunk或RETN Chunk不合法 |
| 0x0205 | 报文头部长度不是ARCP Chunk（20字节） |
| 0x0206 | 报文头部不是合法的ARCP Chunk |
| 0x0207 | 未知协议版本 |

## 保留的状态码
从0x03** 到0x7F** 的状态码为保留状态码，用于未来扩展。
| 状态码 | 描述 |
| --- | --- |
| 0xFFFF | 未知状态码 |

# 保留的类型名
| 类型名 | 描述 |
| --- | --- |
| Exception | 用于被请求者决定抛出异常时传递异常信息 |
| Error | 用于被请求者决定阐述错误详情时传递错误信息 |
| Terminal | 用于ARCP客户端之间的内部协调时的数据传递 |
| Unknown | 用于表达未在本地注册的类型 |
| Any | 用于表达任意类型 |
| None | 用于表达空值 |
| UInt32, Int32, UInt64, Int64, Float, Double, Bool | 用于表达基本数字类型 |
| String | 用于表达字符串，严格为Utf8的字符串 |
| Json | 用于表达Json对象，严格为Utf8的Json字符串 |
| Binary | 用于表达二进制数据，严格为char数组 |

# 和RIFF的比较
1. RIFF的结构总的来说是固定4字节的ID，4字节的长度，然后是数据段，而ARCP是固定4字节的数据段长度，2字节的类型名长度，然后是数据段，然后是类型名。总的来说，都是用固定的头部来标识数据段的长度，但ARCP的头部比RIFF的头部多了类型名长度，这是为了更自由的ID。
2. ARCP未明确规定嵌套Chunk，对于ARCP而言，所有的Chunk都是平级的，但是RIFF允许嵌套Chunk。
3. ARCP的类型名是可选的，RIFF的类型名是必须的。
4. ARCP用第二个Chunk中的N来标记Chunk个数从而确定报文结束，而RIFF用总的RIFF Chunk中的具体数据长度来确定报文结束。
