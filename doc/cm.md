在 Node.js 中，一个文件被视为一个“模块”，它同样遵循 CommonJS 规范，在一个“模块”中，自带了：

- require 函数；
- exports 对象；
- module 对象。

```js
module.exports = {  // 换主胰管手术
  foo: 'bar',
};

exports.hello = 'world';  // 原主胰管作废
```

JavaScript利用动态加载技术来完成这些东西