#pragma once

#include "QuadTreeNode.hpp"

namespace BF
{
	template<typename NumberType, class T>
	struct QuadTree
	{
		public:	
		size_t DataSize;
		T* Data;
		QuadTreeNode<NumberType, T> NodeRoot;
		unsigned int ChunkEntityLimit;

        QuadTree()
        {
            DataSize = 0;
            Data = nullptr;
            ChunkEntityLimit = QuadTreeNodeChildSize;
        }

        QuadTreeNode<NumberType, T>* NodeFetch(QuadTreePosition<NumberType> position)
        {
            QuadTreeNode<NumberType, T>* currentNode = &NodeRoot;

            while (currentNode)
            {
                QuadTreeDirection treeDirection = currentNode->DirectChildPosition(position); // If not found, go deeper, look where to go.
                QuadTreeNode<NumberType, T>* nextHopp = nullptr;
                    
                switch (treeDirection)
                {
                    case BF::QuadTreeDirection::NorthEast:                    
                        nextHopp = currentNode->Node[0];
                        break;                                       

                    case BF::QuadTreeDirection::NorthWest:                    
                        nextHopp = currentNode->Node[1];
                        break;                    

                    case BF::QuadTreeDirection::SouthEast:
                        nextHopp = currentNode->Node[2];
                        break;

                    case BF::QuadTreeDirection::SouthWest:
                        nextHopp = currentNode->Node[3];
                        break;
                }

                if (!nextHopp)
                {
                    return currentNode;
                }

                currentNode = nextHopp;
            }

            return nullptr;
        }

		void Add(QuadTreePosition<NumberType> position, T* data)
		{
            QuadTreeNode<NumberType, T>* targetedNode = NodeFetch(position);

            if (!targetedNode) // No Dublicates
            {
                return; 
            }

            /*
            if (this.points.size() < this.capacity)
            {
                this.points.add(p);
                return true;
            }
            else
            {
                if (!this.divide)
                {
                    subDivide();
                }
                if (this.northeast.insert(p))
                {
                    return true;
                }
                else if (this.northwest.insert(p))
                {
                    return true;
                }
                else if (this.southeast.insert(p))
                {
                    return true;
                }
                else if (this.southwest.insert(p))
                {
                    return true;
                }
                else return false; //<>//
            }*/
		}

		void Allocate(size_t amountOfElements)
		{

		}

		void Clear()
		{

		}
	};
}