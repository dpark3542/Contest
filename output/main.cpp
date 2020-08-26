/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author dpark3542
 */

#include <bits/stdc++.h>

using namespace std;

class TaskE {
public:
  void solve(istream& in, ostream& out) {
    int n;
    in >> n;
    int a[n];
    unordered_set<int> s;
    vector<int> b;
    for (int i = 0; i < n; i++) {
      in >> a[i];
      s.insert(a[i]);
    }
    b.assign(s.begin(), s.end());
    sort(b.begin(), b.end());
    int m = b.size(), bindex[n];
    for (int i = 0; i < n; i++) {
      bindex[i] = find(b.begin(), b.end(), a[i]) - b.begin();
    }
    vector<vector<int>> cnt(n, vector<int>(m));
    cnt[0][bindex[0]]++;
    for (int i = 1; i < m; i++) {
      for (int j = 0; j < m; j++) {
        cnt[i][j] = cnt[i - 1][j];
      }
      cnt[i][bindex[i]]++;
    }
    vector<tuple<double, int, int>> q; // p, cnt, cost
    for (int i = 0; i < m; i++) {
      int j = 0;
      while (j < n && a[j] < b[i]) {
        j++;
      }
      if (j == n) {
        continue;
      }
      int d = 0, cnt = 0;
      while (j + d < n && a[j + d] >= b[i]) {
        if (a[j + d] == b[i]) {
          cnt++;
        }
        d++;
      }
      int cost = b[i];
      if (j - 1 >= 0) {
        cost = min(cost, a[j - 1]);
      }
      if (j + d - 1 < n) {
        cost = min(cost, a[j + d - 1]);
      }
      q.emplace_back((double) cnt / cost, cnt, cost);
    }
    int ans = n, x = n, y = 0;
    for (auto [p, cnt, cost] : q) {
      x -= cnt;
      y += cost;
      ans = min(ans, x + y);
    }
    out << ans << '\n';
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  TaskE solver;
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  solver.solve(in, out);
  return 0;
}