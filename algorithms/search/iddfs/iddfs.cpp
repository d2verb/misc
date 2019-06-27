#include <iostream>
#include <vector>
#include <map>
using namespace std;

// return true if path found
bool dfs(
    vector<string> &field,
    int x,
    int y,
    map<int, map<int, bool>> &visited,
    vector<pair<int, int>> &path,
    int depth)
{
  const static int dx[] = {0, 1, -1, 0};
  const static int dy[] = {1, 0, 0, -1};

  path.emplace_back(pair<int, int>(x, y));
  visited[y][x] = true;

  if (field[y][x] == 'G') {
    return true;
  }

  if (depth == 0)
    return false;

  int height = field.size();
  int width = field[0].size();

  for (int i = 0; i < 4; i++) {
    int nx = dx[i] + x;
    int ny = dy[i] + y;

    if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
      continue;
    }

    if (field[ny][nx] == '#') {
      continue;
    }

    if (visited[ny][nx]) {
      continue;
    }

    bool found = dfs(field, nx, ny, visited, path, depth-1);
    if (found)
      return found;
  }

  path.pop_back();
  return false;
}

// See: https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search
bool iddfs(vector<string> &field, vector<pair<int, int>> &path) {
  int H = field.size();
  int W = field[0].size();

  // Node number is H * W, so the maximum depth is H * W
  // Brancing factor b is b = 4, so space complexity is O(4*depth)
  // Time complexity is O(4^depth)
  for (int depth = 0; depth <= H * W; depth++) {
    map<int, map<int, bool>> visited;
    bool found = dfs(field, 0, 0, visited, path, depth);
    if (found)
      return true;
    vector<pair<int, int>>().swap(path);
  }

  return false;
}

void dump_field(vector<string> &field) {
  for (int y = 0; y < field.size(); y++) {
    for (int x = 0; x < field[0].size(); x++) {
      cout << field[y][x] << " ";
    }
    cout << endl;
  }
}

void mark_path(vector<string> &field, vector<pair<int, int>> &path) {
  int x, y;
  for (auto p : path) {
    tie(x, y) = p;
    if (field[y][x] != 'S' && field[y][x] != 'G')
      field[y][x] = 'x';
  }
}

int main(void) {
  vector<string> field;
  vector<pair<int, int>> path;

  int w, h; cin >> w >> h;
  for (int i = 0; i < h; i++) {
    string s; cin >> s;
    field.emplace_back(s);
  }

  cout << "FIELD:" << endl;
  dump_field(field);

  bool found = iddfs(field, path);
  if (found) {
    cout << "\nPATH:" << endl;
    mark_path(field, path);
    dump_field(field);
  } else {
    cout << "path not found" << endl;
  }
}
