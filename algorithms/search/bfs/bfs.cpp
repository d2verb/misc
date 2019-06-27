#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// return true if path found
bool bfs(vector<string> &field, vector<pair<int, int>> &path)
{
  static const int dx[] = {0, 1, 0, -1};
  static const int dy[] = {1, 0, -1, 0};

  queue<pair<int, int>> Q;
  Q.push(pair<int, int>(0, 0));

  int H = field.size();
  int W = field[0].size();

  map<int, map<int, bool>> visited;
  map<pair<int, int>, pair<int, int>> prev_pos;

  bool found = false;
  int x, y;

  // do bfs
  while (!Q.empty()) {
    tie(x, y) = Q.front();
    Q.pop();

    visited[x][y] = true;

    if (field[y][x] == 'G') {
      found = true;
      break;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx < 0 || nx >= W || ny < 0 || ny >= H)
        continue;

      if (visited[nx][ny])
        continue;

      if (field[ny][nx] == '#')
        continue;

      pair<int, int> next_pos = pair<int, int>(nx, ny);
      prev_pos[next_pos] = pair<int, int>(x, y);
      Q.push(next_pos);
    }
  }

  if (!found)
    return false;

  while (true) {
    path.emplace_back(pair<int, int>(x, y));
    if (x == 0 && y == 0)
      break;
    tie(x, y) = prev_pos[pair<int, int>(x, y)];
  }

  return true;
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

  bool found = bfs(field, path);
  if (found) {
    mark_path(field, path);
    cout << "\nPATH:" << endl;
    dump_field(field);
  } else {
    cout << "path not found" << endl;
  }
}
