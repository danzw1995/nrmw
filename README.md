# nrmw

使用c++编写，模拟实现[nrm](https://github.com/Pana/nrm)的 ls use 功能


## 开始

环境要求：gcc


## 构建

```bash
g++ -c ./lib/func/func.cpp -o ./lib/func/func.o
```

```bash
ar -crv ./lib/func/libfunc.a ./lib/func/func.o
```

```bash
g++ main.cpp lib/func/libfunc.a -o nrmw
```

## 使用

在环境变量`$PATH`中加上上一步构建的nrmw.exe的目录
```
$ nrmw ls

* npm ------- https://registry.npmjs.org/
  yarn ------ https://registry.yarnpkg.com
  cnpm ------ http://r.cnpmjs.org/
  taobao ---- https://registry.npm.taobao.org/
  nj -------- https://registry.nodejitsu.com/
  skimdb ---- https://skimdb.npmjs.com/registry

```

```
$ nrmw use yarn
```



