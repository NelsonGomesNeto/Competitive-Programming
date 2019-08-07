#include <bits/stdc++.h>
using namespace std;

int cmp( string & w1, string & w2 )
{
  int ans = 0;
  for (int i = 0; i < min(w1.size(),w2.size()) ; ++i)
  {
    ++ans;
    if( w1[i] - w2[i] == 0 ) continue;
    else break;
  }
  return ans;
}

bool search( vector<string> & words, string & word , int * ans )
{
  int begin = 0, end = words.size() - 1, mid;
  (*ans) = 0;
  while( begin <= end )
  {
    mid = (begin+end)>>1;
    if( word == words[mid] )
    {
      (*ans) += word.size();
      return true;
    }
    else
    {
      (*ans) += cmp( word, words[mid] );
      if( word < words[mid] ) end = mid -1;
      else begin = mid + 1;
    }
  }
  return false;
}

int main() {
  int size, query;
  vector<string> words;
  string word;
  cin >> size >> query;
  for (int i = 0; i < size; ++i) {
    cin >> word;
    words.push_back(word);
  }
  while (cin >> word) 
  {
    //cout << word << " ";
    int ans;
    if( search( words , word, &ans ) ) cout << "SIM " << ans << endl;
    else cout << "NAO " << ans << endl;
  }

  return 0;
}
