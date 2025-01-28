#include<iostream>
#include<vector>

class Pair
{
public:
	int key=0;
	std::string val="";
	Pair(int k,std::string v)
	{
		key=k;
		val=v;
	}
};

class hashTable
{
private:
	int capacity=10;//容量
	int size=0;//哈希表当前数量
	double loadThres=3.0/4.0;//扩容阈值
	int extendRatio=2;//扩容倍率
	std::vector<Pair*> bucket;//存储桶，头尾连通的
	Pair* TOMBSTONE=new Pair(-1,"-1");//懒删除，墓碑机制
	int hash(int key)
	{
		return key%capacity;
	}
public:
	hashTable()
	{
		bucket=std::vector<Pair*>(capacity,nullptr);
	}
	~hashTable()
	{
		for(auto&i:bucket)
		{
			if(i!=nullptr&&i!=TOMBSTONE)
				delete i;
		}
		//TOMBSTONE单独销毁
		delete TOMBSTONE;
	}
	int findBucket(int key)
	{
		int index=hash(key);
		int firstTombstoneIndex=-1;
		while(bucket[index]!=nullptr)
		{
			if(bucket[index]==TOMBSTONE&&firstTombstoneIndex==-1)
				firstTombstoneIndex=index;
			else if(bucket[index]->key==key)
			{
				if(firstTombstoneIndex!=-1)
				{
					bucket[firstTombstoneIndex]=bucket[index];
					bucket[index]=TOMBSTONE;
					return firstTombstoneIndex;
				}
				return index;
			}
			index=(index+1)%capacity;//因为存储桶头尾相连，相当于是循环的数组
		}
		return firstTombstoneIndex==-1?index:firstTombstoneIndex;
	}
	void put(int key,std::string val)
	{
		double load=(double)size/capacity;//当前负载
		if(load>loadThres)
			extend();
		int index=findBucket(key);
		if(bucket[index]!=nullptr&&bucket[index]!=TOMBSTONE)
			bucket[index]->val=val;
		else
		{
			Pair* pair=new Pair(key,val);
			bucket[index]=pair;
			size++;
		}
	}
	void remove(int key)
	{
		int index=findBucket(key);
		if(bucket[index]!=nullptr&&bucket[index]!=TOMBSTONE)
		{
			delete bucket[index];
			bucket[index]=TOMBSTONE;
			size--;
		}
	}
	void extend()
	{
		std::vector<Pair*>tempBucket=bucket;//备份存储桶
		size=0;//重置计数器
		capacity*=extendRatio;
		bucket=std::vector<Pair*>(capacity,nullptr);
		for(auto&i:tempBucket)
		{
			if(i!=nullptr&&i!=TOMBSTONE)
			{
				put(i->key,i->val);
				delete i;
			}
		}
	}
		
};
