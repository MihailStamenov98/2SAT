#include <bits/stdc++.h>
using namespace std;
#define null NULL
#define mp make_pair
#define pb(a) push_back(a)
#define sz(a) ((int)(a).size())
#define all(a) a.begin() , a.end()
#define fi first
#define se second
#define relaxMin(a , b) (a) = min((a),(b))
#define relaxMax(a , b) (a) = max((a),(b))
#define SQR(a) ((a)*(a))
#define PI 3.14159265358979323846
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef long long ll;

  int vars;
  vector<vi> fo, rfo;
  vector<char> used;
  vi comp_id;
  vi top_sort;

  void AddEdge(int f, int t) {
    fo[f].pb(t);
    rfo[t].pb(f);
  }

  int Var(int w) {
    return 2 * w;
  }

  int Not(int w) {
    return w ^ 1;
  }

  void AddConstraint(int a, int b) {
    AddEdge(Not(a), b);
    AddEdge(Not(b), a);
  }

  void Reset(int vars) {
    this->vars = vars;

    fo.clear(), fo.resize(2 * vars);
    rfo.clear(), rfo.resize(2 * vars);

    used.resize(2 * vars);
    fill(all(used), false);

    comp_id.resize(2 * vars);
    fill(all(comp_id), -1);

    top_sort.clear();
  }

  void Dfs1(int vr){
    used[vr] = true;
    for (int nxt : fo[vr])
      if (!used[nxt]) Dfs1(nxt);
    top_sort.pb(vr);
  }

  void Dfs2(int vr, int id){
    comp_id[vr] = id;
    for (int nxt : rfo[vr])
      if (comp_id[nxt] == -1)
        Dfs2(nxt, id);
  }

  bool Solve(vector<char>& res){
    for (int i = 0; i < 2 * vars; ++i)
      if (!used[i]) Dfs1(i);

    reverse(all(top_sort));
    int idx = 0;
    for (int vr : top_sort)
      if (comp_id[vr] == -1)
        Dfs2(vr, idx++);

    res.resize(vars);
    for (int i = 0; i < vars; ++i){
      if (comp_id[Var(i)] == comp_id[Not(Var(i))])
        return false;
      res[i] = (comp_id[Var(i)] > comp_id[Not(Var(i))]);
    }

    return true;
  }


int main()
{
  Reset(2);

  // (X0 | X1) & (!X0 | X1)
  AddConstraint(sat.Var(0), sat.Var(1));
  AddConstraint(sat.Not(sat.Var(0)), sat.Var(1));

  vector<char> res;
  if (sat.Solve(res)) {
    for (int i = 0; i < sz(res); ++i)
      cout << "X" << i << " = " << ((int)res[i]) << '\n';
  } else {
    cout << "No solution\n";
  }



    int t;
    cin>>t;

    for (int test = 0; test < t; test++)
    {
        for (int i = 0; i < MAX; i++)
            v[i].clear(), r[i].clear();

        cin>>n>>m>>k;
        for (int i = 0; i < k; i++)
        {
            int row1, col1, row2, col2;
            cin>>row1>>col1>>row2>>col2;
            row1--, col1--, row2--, col2--;
            int wantedRow = col1 < col2, wantedCol = row1 < row2;
            if (row1 == row2)
            {
                addEdge(getRow(row1, !wantedRow), getRow(row1, wantedRow));
            }
            else if (col1 == col2)
            {
                addEdge(getCol(col1, !wantedCol), getCol(col1, wantedCol));
            }
            else
            {
                addEdge(getRow(row1, !wantedRow), getRow(row2, wantedRow));
                addEdge(getRow(row2, !wantedRow), getRow(row1, wantedRow));
                addEdge(getCol(col1, !wantedCol), getCol(col2, wantedCol));
                addEdge(getCol(col2, !wantedCol), getCol(col1, wantedCol));
                addEdge(getRow(row1, !wantedRow), getCol(col1, wantedCol));
                addEdge(getCol(col1, !wantedCol), getRow(row1, wantedRow));
                addEdge(getRow(row2, !wantedRow), getCol(col2, wantedCol));
                addEdge(getCol(col2, !wantedCol), getRow(row2, wantedRow));
            }
        }
        // Run 2-SAT
        kosaraju();

        // Check impossibility
        bool impossible = false;
        for (int i = 0; i < n + m; i++)
        {
            if (comp[i * 2 + 0] == comp[i * 2 + 1])
            {
                impossible = true;
                break;
            }
        }
        fprintf(out, "%s\n", impossible ? "No" : "Yes");
    }

    return 0;
}
  return 0;
}
