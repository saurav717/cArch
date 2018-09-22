#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<assert.h>
#include<sstream>
using namespace std;

int search(string &dataS, vector<string> &My_Cache, int numberOfEntries, int &hit, int &miss, int &compulsory_misses, int &capacity_misses, vector<string> &dataI, string &replacement, vector<string> &data, vector<int> &maxvals, int &index)
{
  string temp;
  int indexD = 0, maxvalue = data.size()+5;

  for(long int i=index; i<data.size(); i++)
  {
    if(dataS == data.at(i))
    {
      cout << dataS << " data = " << data.at(i)<< " i = " <<i <<"\n";
      maxvalue = i;
      break;
    }
  }

//  cout<< "maxvalue = "<< maxvalue << "\n";

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

  for(int i = 0; i <My_Cache.size(); i++ )
  {
    if(dataS == My_Cache[i])  // cache hit
    {
      hit = hit + 1;
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
//---------------------------------------------------------------------------
  if(indexD == 0)
  {
    compulsory_misses = compulsory_misses + 1;
  }

  else if(indexD == 1)
  {
    capacity_misses = capacity_misses + 1;
  }

//---------------------------------------------------------------------------

  if(My_Cache.size() == numberOfEntries) // cache is full and replacement should be done
  {
      if(replacement == "OPTIMAL" || replacement == "optimal")                                           // OPTIMAL REPLACEMENT
      {
        int maxElementIndex = max_element(maxvals.begin(),maxvals.end()) - maxvals.begin();
        My_Cache[maxElementIndex] = dataS;
        //cout << "max index" << maxElementIndex << "\n";
        //cout << "My_Cache[46] = " <<My_Cache[46]<< "\n";
        maxvals[maxElementIndex] = maxvalue;
        return 0;
      }

      else
      {
        My_Cache[0] = dataS;

        for(int j = 0; j<My_Cache.size()-1; j++)
        {
              swap(My_Cache.at(j),My_Cache.at(j+1)); //                                    My_Cache.at(j).push_back(My_Cache.at(j+1))
        }
        miss = miss + 1;
          return 0;
      }
  }

  else
  {
    miss = miss + 1;
    My_Cache.push_back(dataS);
    maxvals.push_back(maxvalue);
    //cout << maxvals.at(maxvals.size()-1) << "\n";
    cout<<"compulsory misses = "<<compulsory_misses << "\n";
    return 0;
  }
}

void LRU(vector<string> &data, vector<string> &My_Cache, int numberOfEntries,string replacement)
{

  My_Cache.reserve(numberOfEntries);
  vector<string> dataI;
  vector<int> maxvals;
  int hit = 0, miss = 0, compulsory_misses = 0, capacity_misses = 0, temp,count = 0;
  for(int i = 0; i<data.size(); i++)
  {
      if(My_Cache.size()==0)
      {
      //  cout << "miss\n";
        miss = miss + 1;
        compulsory_misses = compulsory_misses + 1;
        dataI.push_back(data.at(i));
        My_Cache.push_back(data.at(i));

        for(int j=i+1; j<data.size(); j++)
        {
          if(My_Cache.at(i) == data.at(j))
          {
            maxvals.push_back(j);
            break;
          }
        }
      }

      else
      {
          count++;
    //      cout<<"count = "<< count << "\n";
          int t = i+1;
          search(data.at(i), My_Cache, numberOfEntries, hit, miss, compulsory_misses, capacity_misses, dataI, replacement, data, maxvals, t);
      }

  }
  miss = compulsory_misses + capacity_misses;
  cout << "replacement policy - "<< replacement << "\n";
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
  string word, t,q,filename;
  filename = "AddressAccessSequence.txt";
  //  filename = "AddressTrace_CacheBlocking.txt";
//  My_Cache.reserve(numberOfEntries);
  cout << "enter number of entries in the cache\n";
  cin >> numberOfEntries;
  cout << "enter the replacement method\n";
  cin >> replacement;
  //springstream sstm;
  file.open(filename.c_str());
  int count = 0;

  while (file >> word)
  {
      cout << word << endl;
      data.push_back(word);
  }

    cout << "\n\n" <<"Vector(1) = " << data.size() << "\n";
  file.close();
//  if(replacement == "optimal" || replacement == "OPTIMAL")
//  {
//    optimal(data, My_Cache);
//  }
    LRU(data, My_Cache, numberOfEntries, replacement);


}
