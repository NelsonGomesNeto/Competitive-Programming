int bellmanFord()
{
  for (int i = 0; i < vertices; i ++) cost[i] = inf;
  cost[source] = 0; int done;
  for (int i = 0; i < vertices - 1; i ++)
  {
    done = 0;
    for (int u = 0; u < vertices; u ++)
      for (auto v: graph[u])
        if (matrixGraph[u][v][0] && cost[u] + matrixGraph[u][v][1] < cost[v])
        {
          cost[v] = cost[u] + matrixGraph[u][v][1];
          previ[v] = u;
          done = 1;
        }
    if (!done) break;
  }
  return(cost[target] != inf);
}

int spfa()
{
  for (int i = 0; i < vertices; i ++) cost[i] = inf;
  memset(inq, false, sizeof(inq)); memset(visited, 0, sizeof(visited));
  cost[source] = 0;
  queue<int> queue; queue.push(source); inq[source] = true;
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop();
    // if (u == target) break;
    if (visited[u] >= vertices) break;
    inq[u] = false;
    for (auto v: graph[u])
      if (matrixGraph[u][v][0] && cost[u] + matrixGraph[u][v][1] < cost[v])
      {
        cost[v] = cost[u] + matrixGraph[u][v][1];
        previ[v] = u;
        if (!inq[v])
        {
          visited[v] ++; queue.push(v);
          inq[v] = true;
        }
      }
  }
  return(cost[target] != inf);
}

int dijkstraWithPotentials()
{
  for (int i = 0; i < vertices; i ++) cost[i] = inf;
  memset(visited, 0, sizeof(visited));
  cost[source] = 0;
  priority_queue<pair<lli, int> > q;
  q.push({-0, source});
  while (!q.empty())
  {
    int u = q.top().second; q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (auto v: graph[u])
    {
      if (!matrixGraph[u][v][0]) continue;
      int newCost = cost[u] + matrixGraph[u][v][1] + potential[u] - potential[v];
      if (newCost < cost[v])
      {
        cost[v] = newCost; previ[v] = u;
        q.push({-newCost, v});
      }
    }
  }
  for (int i = 0; i  < vertices; i ++) potential[i] += cost[i];
  return(cost[target] != inf);
}
