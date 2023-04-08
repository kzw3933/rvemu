# RISC-V emulator

```
学习中科院软件所PLCT Lab实验室的公开课: 手搓 RISC-V 高性能模拟器,参考文档: https://ksco.cc/rvemu/
```

## 补充知识

### Makefile相关

1. 编译选项
```
编译器选项，用于控制编译器的行为和生成的代码的质量。
-O3：表示启用最高级别的优化。编译器将尝试执行更多的优化，以提高生成代码的性能。这可能会增加编译时间，但通常会产生更快的代码。
-Wall：启用所有警告。编译器将向您报告代码中的潜在问题，例如未使用的变量或不兼容的类型。
-Werror：将所有警告视为错误。如果编译器发出任何警告，则编译将失败，并显示相应的错误消息。
-Wimplicit-fallthrough：启用对C/C++ switch语句中隐式的case标签的警告。如果在switch语句中没有明确使用break关键字，编译器会发出警告，因为这可能会导致意外的行为。

这些选项通常用于开发人员希望生成高质量和可维护的代码。
```
2. 常用函数
```markdown
- `wildcard`
    在Makefile中，`wildcard`是一个函数，用于返回指定模式匹配的文件列表。语法如下：`wildcard pattern`,其中，`pattern`是要匹配的模式，可以包含通配符（如`*`和`?`）和目录分隔符（如`/`）。`wildcard`函数将返回与模式匹配的文件列表。在Makefile中，`wildcard`函数通常用于自动化编译源代码文件列表的过程。例如，可以使用`wildcard`函数将所有源文件的列表存储在一个变量中，然后使用这个变量来生成编译目标的依赖关系。
- `patsubst`
    在Makefile中，`patsubst`是一个函数，用于将一组字符串中的模式替换为另一个模式。语法如下：`patsubst pattern,replacement,string`,其中，`pattern`是要替换的模式，`replacement`是替换成的模式，`string`是包含要替换的字符串的列表。`patsubst`函数将返回一个新的字符串列表，其中包含所有输入字符串中所有匹配`pattern`模式的地方，都被替换为`replacement`模式。`patsubst`函数通常用于自动化生成Makefile规则中的目标和依赖项列表。
```

3. 常用自动变量
```markdown
使用自动化变量可以让Makefile更加灵活和可维护，因为它们可以自动适应规则的变化，而不需要手动修改命令行中的文件名。

- `$<`表示当前规则的第一个依赖项。
- `$@`表示当前规则的目标。
- `$^`表示当前规则的所有依赖项
- `$$`表示转义符号`$`
```

4. Makefile编译规则格式
```markdown
规则的语法如下：

targets: target-pattern: prereq-patterns...
        recipe

其中，`targets`是一个或多个目标文件，`target-pattern`是一个模式，用于指定目标文件名的格式。`prereq-patterns`是一个或多个依赖项模式，用于指定依赖项的格式。`recipe`是用于从依赖项构建目标文件的命令序列。

在以下例子`$(OBJS): obj/%.o: src/%.c $(HDRS)`

在这个例子中，该规则定义了一个模式规则，其中：

- `$(OBJS)`是一个或多个目标文件，它们的名称由模式`obj/%.o`指定。
- `obj/%.o`是目标文件名的模式，其中`%`表示匹配任意字符串。
- `src/%.c`是目标文件的依赖项模式，也是由`%`匹配任意字符串。
- `$(HDRS)`表示该规则的所有目标文件都依赖于`$(HDRS)`变量中定义的头文件。

因此，该规则指定了从每个`src/%.c`文件构建一个`obj/%.o`目标文件，其中的依赖关系由`$(HDRS)`变量定义。在构建目标文件时，Make将执行定义在规则下面的命令序列，用于编译源文件并生成目标文件。总之，这个规则的作用是将源文件编译成目标文件，并将目标文件放在`obj/`目录中。
```

### C语言编程方面
1. fprintf格式化字符串

```
#define fatalf(fmt, ...) (fprintf(stderr, "fatal: %s:%d" fmt "\n", __FILE__, __LINE__, __VA_ARGS__), exit(1))

C语言的语法支持使用空格分开格式化字符串。在C语言中，格式化字符串是由一个字符串常量和一系列格式化参数组成的。格式化参数的数量和类型与字符串中包含的格式说明符的数量和类型相匹配。

在格式化字符串中使用空格进行分隔是合法的，并且不会影响程序的编译和执行。编译器会将空格视为普通的字符，并将它们与其他字符一起组成格式化字符串。在运行时，函数将解析格式化字符串并将其与提供的参数进行匹配，以生成最终的输出。

因此，可以使用空格分开格式化字符串来提高代码的可读性和可维护性，这是C语言的语法所支持的。
```

2. C语言常用的预定义宏
```
C语言中有许多预定义的宏，其中一些是常用的。下面列出了一些常用的预定义宏：

1. `__FILE__`：当前源文件的文件名。
2. `__LINE__`：当前代码行号。
3. `__DATE__`：当前源文件的编译日期。
4. `__TIME__`：当前源文件的编译时间。
5. `__STDC__`：如果编译器遵循 ANSI C 标准，则该宏的值为 1。
6. `__cplusplus`：如果编译器是 C++，则该宏的值为非零。
7. `NULL`：表示空指针的宏。
8. `EOF`：表示输入流结束的宏。
9. `CHAR_BIT`：表示 `char` 类型所占用的字节数。
10. `INT_MAX` 和 `INT_MIN`：表示 `int` 类型的最大值和最小值。
11. `FLT_MAX` 和 `FLT_MIN`：表示 `float` 类型的最大值和最小值。
12. `DBL_MAX` 和 `DBL_MIN`：表示 `double` 类型的最大值和最小值。

这些预定义宏可用于在程序中输出调试信息、定义常量等。使用它们可以使代码更加清晰易懂，并提高代码的可读性和可维护性。

需要注意的是，不同的编译器可能会定义不同的预定义宏，而且它们的值也可能会有所不同。因此，在使用预定义宏时，应该查看编译器的文档，以了解它们的确切含义和值。
```

3. `strerror(error)`的使用

```markdown

`strerror(errno)` 是一个C语言中的函数调用，用于将错误码 `errno` 转换为对应的错误信息字符串。

在C语言中，当系统调用或库函数发生错误时，它们通常会将错误码存储在全局变量 `errno` 中。程序员可以使用 `errno` 来判断函数是否执行成功，并根据需要采取相应的处理措施。但是，错误码本身并不容易理解，因此需要将其转换为人类可读的错误信息。

`strerror(errno)` 函数所需的头文件是 `<string.h>`，同时也需要包含 `<errno.h>` 头文件，以便使用全局变量 `errno`。其中，`<errno.h>` 头文件定义了错误码常量以及全局变量 `errno`，而 `<string.h>` 头文件则定义了 `strerror()` 函数。

需要注意的是，`strerror()` 函数在不同的操作系统和编译器中的行为可能会有所不同。在一些平台上，它可能会返回指针类型的字符串，而在另一些平台上，它可能会返回 `char*` 类型的字符串常量。因此，在实际使用中，需要查看操作系统和编译器的文档，以了解其确切的行为和用法。
```

4. ELF文件格式
![](pics/Elf-layout--en.svg.png)


