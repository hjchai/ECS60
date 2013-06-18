// Author: Sean Davis
// Author: Huajun Chai
#ifndef DECODER_H
#define	DECODER_H
#include "TreeNode.h"
#include <vector>
using namespace std;


class Decoder
{
public:
  Decoder();
  ~Decoder();
  void decode(const unsigned char* encodedMessage, const int encodedSize, unsigned char* decodedMessage, int *decodedSize);
  bool createTree(const unsigned char* encodedMessage, const int encodedSize);
  bool decompress(const unsigned char* encodedMessage, const int encodedSize, unsigned char* decodedMessage, int *decodedSize);
private:
  vector<ExTreeNode> deHuffmanTree;
};

#endif	/* DECODER_H */

