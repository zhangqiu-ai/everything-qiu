import { Everything } from './index';

async function test() {
  const ev = new Everything();
  try {
    // 基本搜索
    console.log('Basic search...');
    const results = await ev.search("*.txt", {
      maxResults: 10,
      matchCase: false
    });
    console.log('Basic search results:', results);

    // 高级搜索
    console.log('Advanced search...');
    const advancedResults = await ev.search("装修", {
      matchPath: true,
      sort: 1, // 按名称升序
      maxResults: 20
    });
    console.log('Advanced search results:', advancedResults);

    // 显示详细信息
    if (advancedResults.length > 0) {
      const firstResult = advancedResults[0];
      console.log('Detailed info for first result:');
      console.log('- File name:', firstResult.filename);
      console.log('- Path:', firstResult.path);
      console.log('- Size:', firstResult.size, 'bytes');
      console.log('- Created:', firstResult.created);
      console.log('- Modified:', firstResult.modified);
      console.log('- Is Folder:', firstResult.isFolder);
    }
  } catch (error) {
    console.error('Search error:', error);
  }
}

test();