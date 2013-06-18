//  Author: Sean Davis
//  Author: Huajun Chai
#include "encoder.h"
#include "TreeNode.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;

const unsigned int mask = 0x80000000;

Encoder::Encoder()
{
  leafSize = 0;
  //cout << (int) encodedMessage[40] << endl;
  treeSize = 0;
  for(int i = 0; i < 256; i++)
  {
    lengths[i] = 0;
    for(int j = 0; j < 8; j++)
      huffman_binary[i][j] = 0;
  }
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()

void Encoder::encode(const unsigned char *message, const int size,
  unsigned char *encodedMessage,
    int *encodedSize)
{
  //if(size < 1024)
   // encodedMessage = new unsigned char[1024+size];

  analysisFile(message, size, encodedMessage);
  //cout << (int) encodedMessage[40] << endl;
  //compress(message, size, encodedMessage, encodedSize);
  createTree();
  createdBitCode();
  compress(message, size, encodedMessage, encodedSize);
}  // encode()

void Encoder::analysisFile(const unsigned char *message, const int size, unsigned char *encodedMessage)
{
  //cout << (int) encodedMessage[40] << endl;
  int leaf[256] = {0}, i = 0;
  for(i = 0; i < size; i++)
    leaf[message[i]]++;
  //
  //cout << (int) encodedMessage[40] << endl;
  //leafFreq = new int(256);
  leafFreq.resize(256);
  //cout << (int) encodedMessage[40] << endl;
  for(i = 0; i < 256; i++)
  {
    if(leaf[i] != 0)
    {
      leafFreq[i] = leaf[i];
      leafSize++;
    }
  }
  //cout << (int) encodedMessage[40] << endl;
}

bool Encoder::createTree()
{
  int i, nodeIndex;
  ExTreeNode ln,rn;
  priority_queue < ExTreeNode, vector<ExTreeNode>, greater<ExTreeNode> > pQueue;

  if(leafSize == 1)
  {
    if(leafFreq[0] == 0)
      leafFreq[0] = 1;
    else
      leafFreq[1] = 1;
    leafSize = 2;
  }

  nodeIndex = 0;
  treeSize = 2 * leafSize - 1;
  huffmanTree.resize(treeSize);
  //cout << (int) encodedMessage[40] << endl;
  for(i = 0; i < 256; i++)
  {
    /*if(nodeIndex==34)
    {
      cout<<i<<endl;
      cout<<leafFreq[i]<<endl;
      cout<<char(i)<<endl;
    }*/

    if(leafFreq[i] != 0)
    {
      huffmanTree[nodeIndex] = ExTreeNode((unsigned) char(i), NTL, NTL, leafFreq[i], nodeIndex);
      //if(nodeIndex==18)
      //cout << (int)huffmanTree[nodeIndex].ch << endl;
     //cout << nodeIndex << endl;
      pQueue.push(huffmanTree[nodeIndex]);
      nodeIndex++;
    }
  }
  //cout << huffmanTree[34].ch << endl;

  for(i = 1; i <= leafSize - 1; i++)
  {
    ln = pQueue.top();
    pQueue.pop();
    rn = pQueue.top();
    pQueue.pop();

    huffmanTree[nodeIndex] = ExTreeNode((unsigned) char(0), ln.index, rn.index, ln.freq + rn.freq, nodeIndex);
    huffmanTree[ln.index].parent = nodeIndex;
    huffmanTree[rn.index].parent = nodeIndex;
    pQueue.push(huffmanTree[nodeIndex]);
    nodeIndex++;
  }
  return true;
}

void Encoder::createdBitCode()
{
  int i = 0, bit = 0;
  ExTreeNode tempNode;
  stack<bool> code;
  for(i = 0; i < leafSize; i++)
  {
    tempNode = huffmanTree[i];
    while(tempNode.index + 1 != huffmanTree.size())
    {
      code.push(tempNode.index == huffmanTree[tempNode.parent].left ? 0 : 1);
      tempNode = huffmanTree[tempNode.parent];
    }
    int count = 0;
    while(!code.empty())
    {
      huffmanTree[i].bits.set(bit++, code.top());

	  if(code.top()==1)
	  {
	    huffman_binary[huffmanTree[i].ch][0] |= (mask>>count);
	  }
	  count++;
      code.pop();
    }
    huffmanTree[i].numbits = bit;

    lengths[huffmanTree[i].ch] = bit;

    for(int j = 1; j < 8; j++)
    {
      huffman_binary[huffmanTree[i].ch][j] |= (huffman_binary[huffmanTree[i].ch][j-1] >> 1);
    }
    bit = 0;
  }
  //return true;
}

bool Encoder::compress(const unsigned char *message, const int size, unsigned char *encodedMessage, int *encodedSize)
{
  int i = 0;
  int index = 1024;
  //int counter = 0;
  //int count = 1024;
  int pos = 0;

  for(; i < 256; i++)
  {
    encodedMessage[ 4 * i + 0 ] |= ( (char*)&huffman_binary[ i ][ 0 ] )[3];
    encodedMessage[ 4 * i + 1 ] |= ( (char*)&huffman_binary[ i ][ 0 ] )[2];
    encodedMessage[ 4 * i + 2 ] |= ( (char*)&huffman_binary[ i ][ 0 ] )[1];
    encodedMessage[ 4 * i + 3 ] |= ( (char*)&lengths[ i ])[0];
  }

  i = 0;

  //cout << message << endl;
  for(; i < size; i++)
  {
    encodedMessage[ index + 0 ] |= ( (char*)&huffman_binary[ message[i] ][ pos ] )[3];
    encodedMessage[ index + 1 ] |= ( (char*)&huffman_binary[ message[i] ][ pos ] )[2];
    encodedMessage[ index + 2 ] |= ( (char*)&huffman_binary[ message[i] ][ pos ] )[1];
    encodedMessage[ index + 3 ] |= ( (char*)&huffman_binary[ message[i] ][ pos ] )[0];

    /*index = ((lengths[ message[i]  ] + counter) / 8) + count;
    counter = counter + (lengths[ message[i]  ]) % 8;
    pos = counter % 8;*/
    index = index + (pos + lengths[message[i]]) / 8;
    pos = (pos + lengths[message[i]]) % 8;
  }
  if(pos==0)
    *encodedSize = index ;
  else
    *encodedSize = index + 1;///here////////////////////////////
  return true;
}





