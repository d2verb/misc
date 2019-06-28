#include <iostream>
#include <vector>
#include <map>
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
bool hill_climbing(vector<string> &field, vector<pair<int, int>> &path) {
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  int H = field.size();
  int W = field[0].size();

  int best_x = 0;
  int best_y = 0;
  int best_eval = eval(best_x, best_y);

  path.emplace_back(pair<int, int>(0, 0));

  // for (;;) { // wikipedia's code using INFINITY loop.
  // but we use finite loop here, because we know the maximum path length.
  for (int c = 0; c <= H * W; c++) {
    int next_x, next_y;
    int next_eval = -(1 << 29);

    // search neighbor nodes
    for (int i = 0; i < 4; i++) {
      int nx = best_x + dx[i];
      int ny = best_y + dy[i];

      if (nx < 0 || nx >= W || ny < 0 || ny >= H)
        continue;

      if (field[ny][nx] == '#')
        continue;

      // calc eval value
      int e = eval(nx, ny);
      if (next_eval < e) {
        next_eval = e;
        next_x = nx;
        next_y = ny;
      }
    }

    // find local optimal
    if (next_eval <= best_eval)
      break;

    best_x = next_x;
    best_y = next_y;
    best_eval = next_eval;
    path.emplace_back(pair<int, int>(next_x, next_y));
  }

  // Check local optimal is global optimal or not
  if (field[best_y][best_x] == 'G')
    return true;

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

  find_goal_pos(field);
  bool found = hill_climbing(field, path);
  if (found) {
    cout << "\nPATH:" << endl;
    mark_path(field, path);
    dump_field(field);
  } else {
    cout << "path not found" << endl;
  }

  return 0;
}
