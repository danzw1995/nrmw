# nrmw

使用c++编写，模拟实现[nrm](https://github.com/Pana/nrm)的 ls use 功能


## 构建

### 静态链接库
#### gcc
```bash
g++ -c ./lib/func/func.cpp -o ./lib/func/func.o
```

```bash
ar -crv ./lib/func/libfunc.a ./lib/func/func.o
```

```bash
g++ main.cpp lib/func/libfunc.a -o nrmw
```

#### MSVC
```bash
cl /c ./lib/func/func.cpp
```

```bash
cl /EHsc main.cpp func.lib /link /out:nrmw.exe
```

#### clang
```bash
clang++ -c -std=c++11  ./lib/func/func.cpp
```

```bash
ar -r libfunc.a func.o
```

```bash
clang++ main.cpp -L. -lfunc -o nrmw 
```

### 动态链接库

#### gcc

```bash
g++ ./lib/func/func.cpp -I ./lib/func  -fPIC -shared -o libdynfunc.dll
```

```bash
g++ main.cpp libdynfunc.dll -o nrmw
```

or 显示调用

##### windows

```bash
g++ ./lib/func/func.cpp ./lib/func/func.def -I ./lib/func  -fPIC -shared -o libdynfunc.dll
```

```bash
g++ main.cpp  -D LOAD_L -o nrmw
```

##### linux

```bash
g++ ./lib/func/func.cpp -std=c++11 -I ./lib/func  -fPIC -shared -o libdynfunc.so
```

```bash
g++ main.cpp  -D DL_OPEN -o nrmw -ldl
```

将当前库文件加入到库文件搜索目录环境变量
```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```


#### MSVC

```bash
cl /LD /DEF: ./lib/func/func.def  ./lib/func/func.cpp
```

```bash
cl /EHsc main.cpp func.lib /link /out:nrmw.exe
```

#### clang
```bash
clang++ ./lib/func/func.cpp -std=c++11 -I ./lib/func -shared -fPIC -o libfunc.so
```

将当前库文件加入到库文件搜索目录环境变量
```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```

```bash
clang++ main.cpp -L. -lfunc -o nrmw
```


## 使用

### windows
在环境变量`$PATH`中加上上一步构建的nrmw.exe的目录
```
 nrmw ls

* npm ------- https://registry.npmjs.org/
  yarn ------ https://registry.yarnpkg.com
  cnpm ------ http://r.cnpmjs.org/
  taobao ---- https://registry.npm.taobao.org/
  nj -------- https://registry.nodejitsu.com/
  skimdb ---- https://skimdb.npmjs.com/registry

```

```
 nrmw use yarn
```

### linux

```
./nrmw ls
```

```
./nrmw use
```



