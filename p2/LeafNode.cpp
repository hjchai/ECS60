//Huajun Chai, 998584845
#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"
#include <math.h>

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;
} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
       // cout << value << "here"  << endl;
	if(count<leafSize)//not full, add element, and keep it sorted
	{
		sortedInsert(value);
		return NULL;
	}
	else//full, need split or give one for adoption
	{
		if(getLeftSibling() != NULL && getLeftSibling()->getCount() < leafSize)
		{
			getLeftSibling()->insert(values[0]);
			int i = 0;
			for(;i < leafSize-1; i++)
				values[i] = values[i + 1];
			values[i] = 0;
			count--;
			insert(value);
			//count ++;
			return NULL;
		}//insert on left,remeber to return
		else
		{
			if(getRightSibling() != NULL && getRightSibling()->getCount() < leafSize)
			{
				int max = values[leafSize - 1];
				if(max > value)
				{
					getRightSibling()->insert(max);
					values[leafSize - 1]=0;
					count--;
					insert(value);
				}
				else
					getRightSibling()->insert(value);
				return NULL;
			}//insert on right,remeber to return
			else//both left and right can't adopt, then split
			{
					return split(value);
			}
		}
	}
	return NULL; // to avoid warnings for now.
}  // LeafNode::insert()// students must write this

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

//added
void LeafNode::sortedInsert(int value)
{
	values[count]=value;
	count ++;
	//int temp = values[count - 1];
	int temp;
	for(int i = count - 1; i > 0; i--)
	{
		if(values[i - 1] > values[i])
		{
			temp = values[i];
			values[i] = values[i-1];
			values[i-1] = temp;
		}
		else
			break;
	}
}

LeafNode* LeafNode::split(int value)
{
	LeafNode* newNode = new LeafNode(leafSize, NULL, NULL, NULL);
	//set all pointers
	BTreeNode* originalRight = getRightSibling();

	newNode->setParent(parent);//if parent is full?
	setRightSibling(newNode);
	if(originalRight == NULL)//there is no node on the right
	{
		newNode->setRightSibling(NULL);
		newNode->setLeftSibling(this);
	}
	else//there is node on the right
	{
		newNode->setRightSibling(originalRight);
		newNode->setLeftSibling(this);
		originalRight->setLeftSibling(newNode);
	}
	//move numbers
	int max = values[leafSize-1];
	if(max>value)
	{
		newNode->insert(max);
		values[leafSize-1]=0;
		count--;
		insert(value);
	}
	else
	{
		newNode->insert(value);
		//count--;
	}
	int center = (int) ceil(double(leafSize)/2);
	for(int i = center; i < leafSize; i++)
	{
		newNode->insert(values[i]);
		values[i] = 0;//set the removed number to 0
		count--;
	}
	//
	return newNode;
}
