#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

struct DataPoint
{
  vector<double> features1;
  vector<double> features2;
  string label;
};

double distformula(const vector<double> &v, const vector<double> &b)
{
  double dist = 0;
  for (size_t i = 0; i < v.size(); i++)
  {
    dist += pow(v[i] - b[i], 2);
  }
  return dist;
}

vector<double> normalization(const vector<double> &feature1, double mini, double maxi)
{
  vector<double> newvec;
  for (auto value : feature1)
  {
    double newval = (value - mini) / (maxi - mini);
    newvec.push_back(newval);
  }
  
  return newvec;
}

class KNN
{
private:
  vector<DataPoint> data;
  vector<double> mini ;
  vector<double> maxi;

public:
  
  void reCSV(const string &filename)
  {
    ifstream file(filename);
    string line;
    getline(file, line);
    mini.resize(2, numeric_limits<double>::max());
    maxi.resize(2, numeric_limits<double>::min());

    while (getline(file, line))
    {
      stringstream ss(line);
      DataPoint dp;
      string value;
      int col = 0;

      while (getline(ss, value, ','))
      {
        if (value.back() == '\r')
          value.pop_back();
        if (col != 0)
        {
          
          if (col ==1 ){
            maxi[col - 1] = max(maxi[col - 1], stod(value));
            mini[col - 1] = min(mini[col - 1], stod(value));
            dp.features1.push_back(stod(value));
            }
          else if (col ==2 ){
            maxi[col - 1] = max(maxi[col - 1], stod(value));
            mini[col - 1] = min(mini[col - 1], stod(value));
            dp.features2.push_back(stod(value));
            }
          else if (col == 5)
            dp.label = value;
        }
        col++;
      }
      data.push_back(dp);
    }
    for (auto &dp : data)
    {
      dp.features1 = normalization(dp.features1, mini[0], maxi[0]);
      dp.features2 = normalization(dp.features2, mini[1], maxi[1]);
      // dp.features = normalization(dp.features, mini[2],maxi[2]);
      // dp.features = normalization(dp.features, mini[3],maxi[3]);
    }
    file.close();
  }

  double getmini(int index) { return mini[index]; }
  double getmaxi(int index) { return maxi[index]; }

  string algot(const DataPoint &stuf, int k)
  {
    vector<pair<double, string>> dist;
    for (const auto &dp : data)
    {
      double sqdist1 = distformula(stuf.features1, dp.features1);
      double sqdist2 = distformula(stuf.features2, dp.features2);
      double sqdist = sqdist1 + sqdist2;
      dist.push_back({sqdist, dp.label});
    }
    sort(dist.begin(), dist.end());

    map<string, int> count;
    for (int i = 0; i < k; i++)
    {
      count[dist[i].second]++;
    }

    string pred;
    int maxi = 0;
    for (const auto &name : count)
    {
      if (name.second > maxi)
      {
        maxi = name.second;
        pred = name.first;
      }
    }

    return pred;
  }
};

int main()
{

  KNN knn;
  knn.reCSV("Iris.csv");
  DataPoint stuf;
  stuf.features1 = {5.1};
  stuf.features2 = {3.5};

  stuf.features1 = normalization(stuf.features1, knn.getmini(0), knn.getmaxi(0));
  stuf.features2 = normalization(stuf.features2, knn.getmini(1), knn.getmaxi(1));

  string prediction = knn.algot(stuf, 3);
  cout << "Predicted Species: " << prediction << endl;

  return 0;
}
