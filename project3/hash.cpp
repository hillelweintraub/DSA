//Hillel Weintraub, DSA2 Programming assignment#1

//The implementation of the hashTable class



#include "hash.h"


  hashTable::hashTable(int size){
    capacity=getPrime(size);
    filled=0;
    data.resize(capacity);
    for (int i = 0; i < capacity; ++i)
      data.at(i).isOccupied=false;
  }


  
  int hashTable::insert(const std::string &key, void *pv){
    int pos=hash(key);

    while(data.at(pos).isOccupied==true){
      if(key==data.at(pos).key && data.at(pos).isDeleted==false)
        return 1;
      else{
        pos++;
        if(pos>=capacity)
          pos-=capacity;
      }
    }
    data.at(pos).key=key;
    data.at(pos).isOccupied=true;
    data.at(pos).isDeleted=false;
    data.at(pos).pv=pv;
    
    if(++filled>capacity/2)
      if(rehash())
        return 0;
      else
        return 2;
    return 0;
  }


  
  bool hashTable::contains(const std::string &key){
    if(findPos(key)==-1)
      return false;
    else
      return true;
  }

  
  void *hashTable::getPointer(const std::string &key, bool *b){
    int pos;
    if((pos=findPos(key))==-1){
      if(b)
        *b=false;
      return NULL;
    }
    else{
      if(b)
        *b=true;
      return data[pos].pv;
    }
  }

  
  int hashTable::setPointer(const std::string &key, void *pv){
    int pos;
    if((pos=findPos(key))==-1)
      return 1;
    else
      data[pos].pv=pv;
      return 0;
  }

  
  bool hashTable::remove(const std::string &key){
    int pos;
    if((pos=findPos(key))==-1)
      return false;
    else{
      data[pos].isDeleted=true;
      return true;
    }
  }

 

  int hashTable::hash(const std::string &key){
    int hashVal=0;
    for (int i = 0; i < key.length(); ++i)
      hashVal=37*hashVal+key[i];

    hashVal%=capacity;
    if(hashVal<0)
      hashVal+=capacity;

    return hashVal;
  }

  
  int hashTable::findPos(const std::string &key){
    int pos = hash(key);
    while(data.at(pos).isOccupied==true){
      if(key==data.at(pos).key && data.at(pos).isDeleted==false)
        return pos;
      else
        pos++;
      if(pos>=capacity)
        pos-=capacity;
    }
    return -1;
  }


  bool hashTable::rehash(){
    vector<hashItem> oldTable=data;
    capacity=getPrime(capacity+1);
    try {
      data.resize(capacity);
    }
    catch (bad_alloc const&) {
      return false;
    }

    for (int i = 0; i < capacity; ++i)
      data.at(i).isOccupied=false;

    filled=0;
    for (int i = 0; i < oldTable.size(); ++i)
    {
      if (oldTable.at(i).isOccupied==true && oldTable.at(i).isDeleted==false)
        insert(oldTable.at(i).key,oldTable.at(i).pv);
    }
    return true;
  }

  
   unsigned int hashTable::getPrime(int size){
    int primes[18] ={12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,
                 25165843,50331653,100663319,201326611,402653189,805306457,1610612741}; 
    for (int i = 0; i < 18; ++i){
      if(primes[i]>=size)
        return primes[i];
    }
    cout<<"Could not resize hashTable"<<endl;
    exit(1);
  }


 

