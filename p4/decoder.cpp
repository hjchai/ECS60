//  Author: Sean Davis
//  Author: Huajun Chai
#include <iostream>
#include "decoder.h"
using namespace std;
const unsigned char mask = 0x80;

Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize,
  unsigned char* decodedMessage, int *decodedSize)
{
  //cout << (int) encodedMessage[40] << endl;
  createTree(encodedMessage, encodedSize);
  decompress(encodedMessage, encodedSize, decodedMessage, decodedSize);
} // decode()

bool Decoder::createTree(const unsigned char* encodedMessage, const int encodedSize)
{
  //cout << (int) encodedMessage[40] << endl;
  int treeSize = 2 * 256 - 1;
  deHuffmanTree.resize(treeSize);
  int index_byte = 0;//based on int
  deHuffmanTree[0] = ExTreeNode(char(0), NTL, NTL, 0);

  int pos = 1;
  for(; index_byte < 256; index_byte++)
  {
    int current_pos = 0;//current position in deHuffmanTree
    int length = (int)encodedMessage[index_byte*4+3];
    int j = 0;
    for(; j < length; j++)
    {
      if((mask >> j%8) == ((mask >> j%8) & encodedMessage[index_byte*4+(j/8)]))//read a 1
      {

        if(deHuffmanTree[current_pos].right == NTL)
        {
          if(j != length - 1)//not the last digit
          {
            deHuffmanTree[pos] = ExTreeNode(char(0), NTL, NTL, 0, pos, current_pos);
            deHuffmanTree[current_pos].right = pos;
            current_pos = pos;
            pos++;
          }
          else//the last digit
          {
            deHuffmanTree[pos] = ExTreeNode(char(index_byte), NTL, NTL, 1, pos, current_pos);
            deHuffmanTree[current_pos].right = pos;
            current_pos = pos;
            pos++;
          }
        }
        else
        {
          current_pos = deHuffmanTree[current_pos].right;
        }
      }

      else//read a 0
      {
        if(deHuffmanTree[current_pos].left == NTL)
        {
          if(j != length - 1)//not the last digit
          {
            deHuffmanTree[pos] = ExTreeNode(char(0), NTL, NTL, 0, pos, current_pos);
            deHuffmanTree[current_pos].left = pos;
            current_pos = pos;
            pos++;
          }
          else//the last digit
          {
            deHuffmanTree[pos] = ExTreeNode(char(index_byte), NTL, NTL, 1, pos, current_pos);
            deHuffmanTree[current_pos].left = pos;
            current_pos = pos;
            pos++;
          }
        }
        else
        {
          current_pos = deHuffmanTree[current_pos].left;
        }
      }

    }
  }
  return true;
}

bool Decoder::decompress(const unsigned char* encodedMessage, const int encodedSize, unsigned char* decodedMessage, int *decodedSize)
{
  //cout << (int) encodedMessage[0] << endl;
  //cout << (int) encodedMessage[3] << endl;
  int index_byte = 1024;
  int pos = 0;
  *decodedSize = 0;
  while(index_byte < encodedSize)
  {
    int index = 0;//to indicate the position when traversing the tree
    while(deHuffmanTree[index].freq == 0)//not reach leafnode
    {
      if((mask >> pos%8) == ((mask >> pos%8) & encodedMessage[index_byte]))//read a 1
      {
        index = deHuffmanTree[index].right;
        pos++;
        if(pos == 8)
        {
          index_byte++;
          pos = 0;
        }
        if(index_byte >= encodedSize && deHuffmanTree[index].freq == 0)
          break;
      }
      //index = deHuffmanTree[index].;
      else
      {
        index = deHuffmanTree[index].left;
        pos++;
        if(pos == 8)
        {
          index_byte++;
          pos = 0;
        }
        if(index_byte >= encodedSize && deHuffmanTree[index].freq == 0)
          break;
      }
    }
    if(index_byte >= encodedSize && deHuffmanTree[index].freq == 0)
      break;
    ///cout << *decodedSize << endl;
    decodedMessage[*decodedSize] = deHuffmanTree[index].ch;
    (*decodedSize)++;
    /*
    if(*decodedSize==529973)
    {
      cout << "index_byte: " << index_byte << endl;
      cout << "encodedSize: " << encodedSize << endl;
      cout << "pos: " << pos << endl;
    }*/
  }
  ///(*decodedSize)++;//hehe

  return true;
}

