# everything-qiu

[![NPM Version](https://img.shields.io/npm/v/everything-qiu)](https://www.npmjs.com/package/everything-qiu)
[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](https://opensource.org/licenses/ISC)

一个用于调用 Everything 搜索引擎 SDK 的 Node.js 包。Everything 是一个优秀的 Windows 文件搜索工具，本包提供了与 Everything 进行交互的 TypeScript/JavaScript API。

## 功能特点

- 🚀 完整的 TypeScript 支持
- 🔍 快速文件搜索能力
- 💡 简单易用的 API
- 🛡️ 类型安全
- 🔄 异步操作支持

## 安装

使用 npm:
```bash
npm install everything-qiu
```

使用 yarn:
```bash
yarn add everything-qiu
```

使用 pnpm:
```bash
pnpm add everything-qiu
```

## 前置要求

- Windows 操作系统
- 已安装 [Everything](https://www.voidtools.com/) 搜索工具
- Node.js 版本 >= 14.0.0

## 使用示例

```typescript
import { Everything } from 'everything-qiu';

// 初始化 Everything 实例
const everything = new Everything();

// 搜索文件
const results = await everything.search('*.txt');
console.log(results);

// 获取搜索结果数量
const count = await everything.getResultCount();
console.log(`找到 ${count} 个结果`);
```

## API 文档

### Everything 类

#### 构造函数
```typescript
new Everything(options?: EverythingOptions)
```

#### 方法

- `search(query: string): Promise<SearchResult[]>`
  搜索文件和文件夹

- `getResultCount(): Promise<number>`
  获取搜索结果数量

- `setSearchPath(path: string): void`
  设置搜索路径

更多 API 详情请查看源代码文档。

## 贡献指南

欢迎提交 Pull Requests 和 Issues！在提交 PR 之前，请确保：

1. 更新测试用例
2. 更新文档
3. 遵循现有的代码风格

## 许可证

ISC License - 查看 [LICENSE](LICENSE) 文件了解更多详情。

## 作者

qiu ge

## 更新日志

### 1.0.0
- 初始发布
- 基本搜索功能实现
- TypeScript 类型支持
