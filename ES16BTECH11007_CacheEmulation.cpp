#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<assert.h>
#include<sstream>
using namespace std;

int search(string &dataS, vector<string> &My_Cache, int numberOfEntries, int &hit, int &miss, int &compulsory_misses, int &capacity_misses, vector<string> &dataI, string &replacement, vector<string> &data, vector<int> &maxvals, int &index, vector<string> &hitsAndMisses)
{
  string temp;
  int indexD = 0, maxvalue = data.size()+5;
  int there;
  for(long int i=index; i<data.size(); i++)
  {
    if(dataS == data.at(i))
    {
    //  cout << dataS << " data = " << data.at(i)<< " i = " <<i <<"\n";
      maxvalue = i;
      break;
    }
  }

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
      //cout << "hit\n";
      hitsAndMisses.push_back("HIT");
      if(replacement == "OPTIMAL" || replacement == "optimal")
      {
        int j ;
        for( j=index;j<data.size();j++)
        {
          if(dataS == data.at(j))
          {
            maxvals[i] = j;
            break;
          }
        }
        if(j == data.size()-1 || j == data.size())
        {
          maxvals[i] = data.size()+5;
        }
      }

     else if(replacement == "LRU" || replacement == "lru")
      {
        for(int j = i; j<My_Cache.size()-1; j++)
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
    hitsAndMisses.push_back("MISS");
    compulsory_misses = compulsory_misses + 1;
  }

  else if(indexD == 1)
  {
    hitsAndMisses.push_back("MISS");
    capacity_misses = capacity_misses + 1;
  }

//---------------------------------------------------------------------------

  if(My_Cache.size() == numberOfEntries) // cache is full and replacement should be done
  {
      if(replacement == "optimal" || replacement == "OPTIMAL")
      {
        int maxElementIndex = max_element(maxvals.begin(),maxvals.end()) - maxvals.begin();
        My_Cache[maxElementIndex] = dataS;
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
    return 0;
  }
}

void LRU(vector<string> &data, vector<string> &My_Cache, int numberOfEntries,string replacement, string filename, string numberOfEntries2)
{

  My_Cache.reserve(numberOfEntries);
  vector<string> dataI, hitsAndMisses;
  vector<int> maxvals;
  ofstream myfile;
  string myfileName;
  myfileName = "ES16BTECH11007_"+replacement+"_"+filename+"_"+numberOfEntries2+".out";
  myfile.open(myfileName.c_str());

  int hit = 0, miss = 0, compulsory_misses = 0, capacity_misses = 0, temp,count = 0;

  for(int i = 0; i<data.size(); i++)
  {
      if(My_Cache.size()==0)
      {
        miss = miss + 1;
        compulsory_misses = compulsory_misses + 1;
        dataI.push_back(data.at(i));
        My_Cache.push_back(data.at(i));
        hitsAndMisses.push_back("MISS");


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
          int t = i+1;
          search(data.at(i), My_Cache, numberOfEntries, hit, miss, compulsory_misses, capacity_misses, dataI, replacement, data, maxvals, t, hitsAndMisses);
      }

  }
  miss = compulsory_misses + capacity_misses;
//  myfile << "replacement policy - "<< replacement << "\n";
  myfile << "total accesses = " << hit + miss << "\n";
  //myfile << "Total hits = " << hit << ", Total misses = " << miss << "\n";
  myfile << "Total misses = " << miss << "\n";
  myfile << "compulsory misses = " << compulsory_misses << "\n";
  myfile << "capacity misses = " << capacity_misses << "\n";
  for(int i=0; i<hitsAndMisses.size(); i++)
  {
    myfile << hitsAndMisses[i] << "\n";
  }
  myfile.close();
}

int main(int argc, char **argv)
{
  ifstream file;
  char c;
  string word, t,q,filename, NOE;
  string inputString, replacement;
  vector<string> data, My_Cache;
  int numberOfEntries = 0;
  stringstream SS(argv[3]);
  //numberOfEntries << SS;
  replacement = argv[1];
  filename = argv[2];
  //NOE = argv[3];

  SS >> numberOfEntries;

  file.open(filename.c_str());
  int count = 0;

  while (file >> word)
  {
    ////  cout << word << endl;
      data.push_back(word);
  }

    //cout << "\n\n" <<"Vector(1) = " << data.size() << "\n";
  file.close();
  LRU(data, My_Cache, numberOfEntries, replacement,filename ,argv[3]);
}
