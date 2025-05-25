export interface SearchResult {
  filename: string;
  path: string;
}

export interface Everything {
  search(query: string): Promise<SearchResult[]>;
}