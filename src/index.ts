import { SearchResult } from './types';
import { join } from 'path';

// 设置 DLL 搜索路径为绝对路径
const dllPath = join(__dirname, '..', 'src', 'native', 'lib');
process.env.PATH = `${dllPath};${process.env.PATH}`;

// 使用绝对路径加载 addon
const addonPath = join(__dirname, '..', 'build', 'Release', 'everything.node');
const addon = require(addonPath);

export class Everything {
  public search(query: string): Promise<SearchResult[]> {
    return new Promise((resolve, reject) => {
      try {
        const results = addon.search(query);
        resolve(results);
      } catch (error) {
        reject(error);
      }
    });
  }
}

export default Everything;