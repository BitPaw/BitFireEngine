#include "PNGColorTree.h"

#include <stdlib.h>
#include <string.h>

BF::PNGColorTree::PNGColorTree()
{
	memset(children, 0, 16 * sizeof(PNGColorTree*));
	index = -1;
}

unsigned int BF::PNGColorTree::color_tree_add(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned index)
{
    int bit;
    for (bit = 0; bit < 8; ++bit)
    {
        int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
        if (!tree->children[i])
        {
            tree->children[i] = new PNGColorTree();
           
            if (!tree->children[i]) return 83; /*alloc fail*/
        }
        tree = tree->children[i];
    }
    tree->index = (int)index;
    return 0;
}
