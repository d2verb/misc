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
    vector<pair<int, int>> &path)
{
  const static int dx[] = {0, 1, -1, 0};
  const static int dy[] = {1, 0, 0, -1};

  path.emplace_back(pair<int, int>(x, y));
  visited[y][x] = true;

  if (field[y][x] == 'G') {
    return true;
  }

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

    bool found = dfs(field, nx, ny, visited, path);
    if (found)
      return found;
  }

  path.pop_back();

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

int main(void) {
  vector<string> field;
  vector<pair<int, int>> path;
  map<int, map<int, bool>> visited;

  int w, h; cin >> w >> h;
  for (int i = 0; i < h; i++) {
    string s; cin >> s;
    field.emplace_back(s);
  }

  cout << "FIELD:" << endl;
  dump_field(field);

  bool found = dfs(field, 0, 0, visited, path);
  if (!found) {
    cout << "path not found" << endl;
  } else {
    int x, y;
    for (auto &p : path) {
      tie(x, y) = p;
      if (field[y][x] != 'S' && field[y][x] != 'G') {
        field[y][x] = 'x';
      }
    }

    cout << "\nPATH:" << endl;
    dump_field(field);
  }
}
