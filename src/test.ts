import { Everything } from './index';

async function test() {
  const ev = new Everything();
  try {
    // 尝试一个简单的搜索词
    console.log('Searching for files...');
    const results = await ev.search("*.txt");
    console.log('Search results:', results);
    
    // 尝试中文搜索
    console.log('Searching with Chinese query...');
    const chineseResults = await ev.search("装修");
    console.log('Chinese search results:', chineseResults);
  } catch (error) {
    console.error('Search error:', error);
  }
}

test();