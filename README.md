# everything-qiu

[![NPM Version](https://img.shields.io/npm/v/everything-qiu)](https://www.npmjs.com/package/everything-qiu)
[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](https://opensource.org/licenses/ISC)

一个用于调用 Everything 搜索引擎 SDK 的 Node.js 包。Everything 是一个优秀的 Windows 文件搜索工具，本包提供了与 Everything 进行交互的 TypeScript/JavaScript API。

## 功能特点

- 🚀 完整的 TypeScript 支持
- 🔍 快速文件搜索能力
- 💡 简单易用的 API
- ��️ 类型安全
- 🔄 异步操作支持
- 📂 支持文件夹和文件搜索
- 📊 支持高级搜索选项
- 📅 支持文件元数据（大小、创建时间等）

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

### 基本搜索
```typescript
import { Everything } from 'everything-qiu';

// 初始化 Everything 实例
const everything = new Everything();

// 基本搜索
const results = await everything.search('*.txt');
console.log(results);
```

### 高级搜索选项
```typescript
// 使用高级搜索选项
const advancedResults = await everything.search('项目文档', {
  matchPath: true,        // 在路径中也搜索
  matchCase: false,       // 不区分大小写
  matchWholeWord: false,  // 不全字匹配
  regex: false,          // 不使用正则表达式
  maxResults: 100,       // 最多返回100个结果
  sort: 1                // 按名称升序排序
});

// 结果包含详细信息
for (const result of advancedResults) {
  console.log(`文件名: ${result.filename}`);
  console.log(`路径: ${result.path}`);
  console.log(`大小: ${result.size} 字节`);
  console.log(`创建时间: ${result.created}`);
  console.log(`修改时间: ${result.modified}`);
  console.log(`是否文件夹: ${result.isFolder}`);
}
```

## API 文档

### Everything 类

#### 构造函数
```typescript
new Everything()
```

#### 方法

- `search(query: string, options?: SearchOptions): Promise<SearchResult[]>`
  搜索文件和文件夹，支持高级搜索选项

#### SearchOptions 接口
```typescript
interface SearchOptions {
  matchPath?: boolean;        // 是否匹配路径
  matchCase?: boolean;        // 是否区分大小写
  matchWholeWord?: boolean;   // 是否全字匹配
  regex?: boolean;            // 是否使用正则表达式
  maxResults?: number;        // 最大结果数
  sort?: number;             // 排序方式
}
```

#### SearchResult 接口
```typescript
interface SearchResult {
  filename: string;          // 文件名
  path: string;             // 文件路径
  size?: number;            // 文件大小（字节）
  created?: Date;           // 创建时间
  modified?: Date;          // 修改时间
  isFolder?: boolean;       // 是否是文件夹
}
```

#### 排序选项
- `1`: 按名称升序
- `2`: 按名称降序
- `3`: 按路径升序
- `4`: 按路径降序
- `5`: 按大小升序
- `6`: 按大小降序
- `11`: 按创建时间升序
- `12`: 按创建时间降序
- `13`: 按修改时间升序
- `14`: 按修改时间降序

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
- 支持高级搜索选项
- 支持文件元数据
- 支持自定义排序
