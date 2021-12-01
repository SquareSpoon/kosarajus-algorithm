#include <iostream>
#include <stack>
#include <vector>
#define MAX 10000
#define COMP 1000
using namespace std;
int n, m, v1, v2, components;
vector<int> g[MAX];
vector<int> gR[MAX];
vector<int> component[COMP];
bool v[MAX], vR[MAX];
stack<int> order;
void dfs(int node){
  v[node] = true;
  for(int i = 0; i < g[node].size(); i++){
    if(v[g[node][i]]) continue;
    dfs(g[node][i]);
  }
  order.push(node);
}
void dfsR(int node, int comp){
  vR[node] = true;
  component[comp].push_back(node);
  for(int i = 0; i < gR[node].size(); i++){
    if(vR[gR[node][i]]) continue;
    dfsR(gR[node][i], comp);
  }
}
int main(){
  cin >> n >> m;
  for(int i = 1; i <= m; i++){
    cin >> v1 >> v2;
    g[v1].push_back(v2);
    gR[v2].push_back(v1);
  }
  //initial graph search to put the nodes in the stack
  for(int i = 1; i <= n; i++){
    if(v[i]) continue;
    dfs(i);
  }
  //loop through the stack elements to find the strongly connected components by searching into the inverted graph
  while(!order.empty()){
    int node = order.top();
    order.pop();
    if(vR[node]) continue;
    components++;
    dfsR(node, components);
  }
  //printing the quantity of components and each of them
  cout << components << '\n';
  for(int i = 1; i <= components; i++){
    for(int j = 0; j < component[i].size(); j++){
      cout << component[i][j] << " ";
    }
    cout << '\n';
  }
}
