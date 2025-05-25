export interface SearchOptions {
  matchPath?: boolean;        // 是否匹配路径
  matchCase?: boolean;        // 是否区分大小写
  matchWholeWord?: boolean;   // 是否全字匹配
  regex?: boolean;            // 是否使用正则表达式
  maxResults?: number;        // 最大结果数
  sort?: number;             // 排序方式
}

export interface SearchResult {
  filename: string;
  path: string;
  size?: number;            // 文件大小
  created?: Date;          // 创建时间
  modified?: Date;         // 修改时间
  isFolder?: boolean;      // 是否是文件夹
}

export interface Everything {
  search(query: string, options?: SearchOptions): Promise<SearchResult[]>;
}