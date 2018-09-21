#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<assert.h>
#include<sstream>
using namespace std;

int search(string &dataS, vector<string> &My_Cache, int numberOfEntries, int &hit, int &miss, int &compulsory_misses, int &capacity_misses, vector<string> &dataI, string replacement)
{
  string temp;
  int indexD = 0;

  for(int i=0; i<dataI.size(); i++)
  {
    if(dataI[i] == dataS)  // data already came
    {
      indexD = 1;
    }
  }
  if(indexD == 0)
  {
    dataI.push_back(dataS);
  }

//  cout << "string = " << dataS << "\n";
  //cout << "this function working\n";
  for(int i = 0; i <My_Cache.size(); i++ )
  {
  //  cout << "dataS = "<< dataS << " my cache [i] = "<< My_Cache[i] << "\n";
    if(dataS == My_Cache[i])  // cache hit
    {
      hit = hit + 1;
  //    cout << dataS;
      //cout << "this should work\n";
      cout << "hit\n";
      if(replacement == "LRU" || replacement == "lru")
      {  for(int j = i; j<My_Cache.size()-1; j++)
        {
              swap(My_Cache.at(j),My_Cache.at(j+1)); //                                    My_Cache.at(j).push_back(My_Cache.at(j+1))
        }
      }
        return 1;
    }
  }

  if(indexD == 0)
  {
    compulsory_misses = compulsory_misses + 1;
  }

  else if(indexD == 1)
  {
    capacity_misses = capacity_misses + 1;
  }

  if(My_Cache.size() == numberOfEntries) // cache is full and replacement should be done
  {
    My_Cache[0] = dataS;

    for(int j = 0; j<My_Cache.size()-1; j++)
    {
          swap(My_Cache.at(j),My_Cache.at(j+1)); //                                    My_Cache.at(j).push_back(My_Cache.at(j+1))
    }
    miss = miss + 1;
    return 0;
  }

  else
  {
    miss = miss + 1;
    My_Cache.push_back(dataS);
    return 0;
  }
}

void LRU(vector<string> &data, vector<string> &My_Cache, int numberOfEntries,string replacement)
{

  My_Cache.reserve(numberOfEntries);
  vector<string> dataI;
  int hit = 0, miss = 0, compulsory_misses = 0, capacity_misses = 0, temp;
  for(int i = 0; i<data.size(); i++)
  {
      if(My_Cache.size()==0)
      {
        cout << "miss\n";
        miss = miss + 1;
        compulsory_misses = compulsory_misses + 1;
        dataI.push_back(data.at(i));
        My_Cache.push_back(data.at(i));
      }

      else
      {
          search(data.at(i), My_Cache, numberOfEntries, hit, miss, compulsory_misses, capacity_misses, dataI, replacement);
      }

  }
  cout << "replacement polict - "<< replacement << "\n";
  cout << "total accesses = " << hit + miss << "\n";
  cout << "hits = " << hit << ", misses = " << miss << "\n";
  cout << "capacity misses = " << capacity_misses << "\n";
  cout << "compulsory misses = " << compulsory_misses << "\n";

}

int main()
{
  ifstream file;
  char c;
  string inputString, replacement;
  vector<string> data, My_Cache;
  int numberOfEntries;
//  My_Cache.reserve(numberOfEntries);
  cout << "enter number of entries in the cache\n";
  cin >> numberOfEntries;
  cout << "enter the replacement method\n";
  cin >> replacement;
  //springstream sstm;
  file.open("AddressTrace_CacheBlocking.txt");
  int count = 0;

  /*while(replacement != "LRU" || replacement != "lru" || replacement != "FIFO" || replacement != "fifo")
  {
    cout << "enter valid replacement policy\n";
    cin >> replacement;
  }*/

  while(!file.eof()) //reads one string at a time
  {
    file>>c;
    //cout <<  c ;
    count++;
    inputString += c;
    if(count == 7)
    {
      cout << inputString <<"\n";
      data.push_back(inputString);
      count = 0;
      inputString.clear();
    }
  }

    cout << "\n\n" <<"Vector(1) = " << data.size() << "\n";
  file.close();

    LRU(data, My_Cache, numberOfEntries, replacement);

}
