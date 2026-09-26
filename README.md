# 便利店POS系统

Dian 团队 2026 秋招大一题——命令行交互式 POS 系统。

本项目使用 C 语言开发，运行于终端，支持商品查询、购物车管理、结账、销售记录持久化、管理员价格与库存管理等功能。数据使用 `CSV` 文件存储，程序重启后仍可查看历史销售记录。

- 作者：陈承权
- 仓库：https://github.com/CCQ-nb/POS
- 学习文档：docs/learning.md
- 指令参考：docs/commands.md

***



# 完成进度
- [x] level 1.1 - 计价与输出
- [x] level 1.2 - 订单结账
- [x] level 1.3 - 当日销售统计
- [x] level 2.1 - 管理员商品价格管理
- [x] level 2.2 - 管理员商品库存管理
- [ ] level 3.0 - 自由发挥

***



# 功能概览


### 收银员模式

- 输入`<条码> <条码> ......`: 将商品加入购物车并显示名称、单价、数量、小计
- `-<条码>`: 减少购物车中对应商品数量，同时恢复库存，数量为 0 时自动删除
- `prices`: 查看所有商品名称、条码、价格(不包括库存)
- `print`: 打印当前购物车小票
- `drop`: 清空购物车
- `checkout`: 结账，打印小票，将销售记录写入`data/sales.csv`，扣减库存，清空购物车
- `sales <day>`: 查看指定日期的销售记录与总营业额，省略参数默认今天
- `newday`: 开始新的一天，清空当日内存统计，历史记录保留于`data/sales.csv`
- `admin`: 进入管理员模式（密码: admin123）
- `quit/exit`: 退出程序(在输入密码时`>Password`，quit/exit可退出输入密码状态)


### 管理员模式

*收银员模式下的指令同样可用*

- `setprice <条码> <新价格>`: 修改指定商品价格
- `itemadd <条码> <名称> <价格>`: 添加新商品
- `itemdel <条码>`: 删除商品
- `restock <条码> <数量>`: 增加库存
- `setstock <条码> <数量>`: 直接设置库存
- `prices`: 查看商品信息(包含库存)
- `back`: 返回收银员模式

***



# 编译与运行


### 环境要求
- Cygwin
- gcc


### 编译
在项目根目录执行

**程序使用相对路径读取`data/items.csv`和`data/sales.cs`因此必须在项目根目录运行**

`gcc -Wall -Wextra -g -o pos src/*.c`


### 运行
`./pos`

***



# 数据文件

`data/items.csv`

商品信息，格式

```csv
    code,name,price,stock
    001,Cola,3.50,10
    002,Lollipop,0.50,10
    003,Noodles,6.00,10
```

| 列 | 含义 |
|:---|:---|
| code | 商品条码 |
| name | 商品名称 |
| price | 单价(元，保留两位小数) |
| stock | 库存数量 |

**第一行为表头，程序读取时跳过。价格在内存中以整数分存储，避免浮点误差。**


`data/sales.csv`

销售记录，每次`checkout`追加写入。格式:

```csv
date,receipt_id,time,code,name,price,quantity,amount
1,1,10:15:32,001,Cola,3.50,1,3.50
1,1,10:15:32,002,Lollipop,0.50,1,0.50
2,1,11:02:10,003,Noodles,6.00,2,12.00
```

| 列 | 含义 |
|:---|:---|
| date | 日期编号（程序运行的第几天） |
| receipt_id | 流水号，每单递增 |
| time | 结账时间 |
| code | 商品条码 |
| name | 商品名称 |
| price | 单价（元）|
| quantity | 数量 |
| amount | 金额（元）|

***



# 项目结构

```text
POS/
├── README.md
├── .gitignore
├── src/
│   ├── main.c              # 主循环
│   ├── catalog.c           # 商品目录：加载、保存、查找
│   ├── catalog.h
│   ├── cart.c              # 购物车：增删改查、库存检查
│   ├── cart.h
│   ├── sales.c             # 销售记录：写入、读取、日期管理
│   ├── sales.h
│   ├── admin.c             # 管理员：价格、库存管理
│   ├── admin.h
│   ├── input.c             # 输入解析、命令分发
│   └── input.h
├── data/
│   ├── items.csv           # 商品数据
│   └── sales.csv           # 销售记录
├── docs/
│   ├── learning.md         # 学习文档
│   └── commands.md         # 命令参考
```