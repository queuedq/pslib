struct Node { int a, b; };
bool cmp(Node x, Node y) { return x.a < y.a; }

void usage() {
  priority_queue<Node, vector<Node>, decltype(&cmp)> pq(cmp);
  pq.push({1, 3});
  pq.push({4, 2});
  pq.top(); // {4, 2}
}
