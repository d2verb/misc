#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int gx, gy;

// Using manhattan distance as eval function
int eval(int x, int y) {
  return -(abs(gy - y) + abs(gx - x));
}

void find_goal_pos(vector<string> &field) {
  int H = field.size();
  int W = field[0].size();

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (field[y][x] == 'G') {
        gx = x;
        gy = y;
      }
    }
  }
}

// return true if global optimal (goal) found
bool best_first_search(vector<string> &field, vector<pair<int, int>> &path) {
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  int H = field.size();
  int W = field[0].size();

  bool found = false;
  map<int, map<int, bool>> visited;
  priority_queue<pair<int, pair<int, int>>> Q;
  map<pair<int, int>, pair<int, int>> prev_pos;

  // path.emplace_back(pair<int, int>(0, 0));
  visited[0][0] = true;
  Q.push(pair<int, pair<int, int>>(eval(0, 0), pair<int, int>(0, 0)));

  int x, y;
  while (!Q.empty()) {
    pair<int, pair<int, int>> node = Q.top();
    Q.pop();

    x = node.second.first;
    y = node.second.second;

    if (field[y][x] == 'G') {
      found = true;
      break;
    }

    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx < 0 || nx >= W || ny < 0 || ny >= H)
        continue;

      if (field[ny][nx] == '#')
        continue;

      if (visited[nx][ny])
        continue;

      pair<int, int> next_pos = pair<int, int>(nx, ny);
      prev_pos[next_pos] = pair<int, int>(x, y);
      Q.push(pair<int, pair<int, int>>(eval(nx, ny), pair<int, int>(nx, ny)));
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

  find_goal_pos(field);
  bool found = best_first_search(field, path);
  if (found) {
    cout << "\nPATH:" << endl;
    mark_path(field, path);
    dump_field(field);
  } else {
    cout << "path not found" << endl;
  }

  return 0;
}
