#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
using namespace std;

int W, H;
int dx[] = {0, 1};
int dy[] = {1, 0};
random_device rnd;

void gen_path(vector<string> &field) {
  int path_len = (W + H) * 2 / 3;

  int x = 0, y = 0;
  int nx, ny;

  field[y][x] = 'S';
  path_len--;

  // build path
  while (path_len > 0) {
    int i = rnd() % 2;

    while (true) {
      nx = x + dx[i];
      ny = y + dy[i];

      if (nx < 0 || nx >= W || ny < 0 || ny >= H || field[ny][nx] == '.') {
        i++;
        continue;
      }

      break;
    }

    if (path_len == 1) {
      field[ny][nx] = 'G';
    } else {
      field[ny][nx] = '.';
    }

    x = nx;
    y = ny;

    path_len--;
  }
}

void set_block(vector<string> &field, double ratio) {
  int path_len = (W + H) * 2 / 3;
  int block_cnt = int((W * H - path_len) * ratio);

  // set block
  while (block_cnt > 0) {
    int x = rnd() % W;
    int y = rnd() % H;
    if (field[y][x] == ',') {
      field[y][x] = '#';
      block_cnt--;
    }
  }
  
  // finally, replace all ',' to '.'
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (field[y][x] == ',') {
        field[y][x] = '.';
      }
    }
  }
}

void dump_field(vector<string> &field) {
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      cout << field[y][x];
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./maze_gen W H" << endl;
    return 1;
  }

  W = atoi(argv[1]);
  H = atoi(argv[2]);

  vector<string> field(H, string(W, ','));
  gen_path(field);
  set_block(field, 0.4);

  cout << W << " " << H << endl;
  dump_field(field);
}
