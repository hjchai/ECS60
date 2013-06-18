// Author: Sean Davis
// Author: Huajun Chai
#ifndef ENCODER_H
#define	ENCODER_H
#include <stdio.h>
#include <vector>
#include "TreeNode.h"
using namespace std;

class Encoder
{
public:
  Encoder();
  void encode(const unsigned char *message, const int size,
    unsigned char *encodedMessage, int *encodedSize);
  ~Encoder();
  void analysisFile(const unsigned char *message, const int size, unsigned char *encodedMessage);
  bool createTree();
private:
  vector<int> leafFreq;
  vector<ExTreeNode> huffmanTree;
  unsigned int  huffman_binary[256][8];
  unsigned int lengths[256];
  unsigned long leafSize;
  unsigned long treeSize;
  unsigned long fileSize;
  void createdBitCode();
  bool compress(const unsigned char *message, const int size, unsigned char *encodedMessage, int *encodedSize);
};

#endif	/* ENCODER_H */

