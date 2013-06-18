//  Author: Huajun Chai

#include <bitset>
using namespace std;

#ifndef  MAXBITNTL

const short NTL=-1;
const short MAXBIT=256;
const unsigned long DATA=200*1024*8;
const unsigned long NUM=200*1024;
const short BIT=8;

//const unsigned long MAXCHAR=256;
#define MAXBITNTL



class TreeNode
{

public:
	TreeNode(char c=0,int Lleafage=NTL,int Rleafage=NTL):
            ch(c),left(Lleafage),right(Rleafage)
	   {

	   }
       unsigned char ch;
	   int left;
	   int right;

};

typedef  bitset<MAXBIT>  LeafBit;
typedef  bitset<BIT>     EightBit;

class ExTreeNode:public TreeNode
{
     public:
		 int freq;
		 int index;
		 int parent;
		 int numbits;
		 LeafBit  bits;


		 ExTreeNode(char c=0,int Lleafage=NTL,int Rleafage=NTL,
			 int f=0,int indx=NTL,int p=0,int nb=0)
			 :TreeNode(c,Lleafage,Rleafage),freq(f),
			 index(indx),parent(p),numbits(nb),bits(0)
		 {

		 }

		 friend bool operator< (const ExTreeNode& lhs,const ExTreeNode& rhs)
		 {
			 return lhs.freq < rhs.freq;
		 }


		 friend bool operator> (const ExTreeNode& lhs,const ExTreeNode& rhs)
		 {
			 return lhs.freq > rhs.freq;
		 }

};
#endif
