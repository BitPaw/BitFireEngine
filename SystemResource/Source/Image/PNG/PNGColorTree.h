#pragma once

namespace BF
{
	/*
One node of a color tree
This is the data structure used to count the number of unique colors and to get a palette
index for a color. It's like an octree, but because the alpha channel is used too, each
node has 16 instead of 8 children.
*/
	struct PNGColorTree
	{
		public:
		PNGColorTree* children[16]; /*up to 16 pointers to ColorTree of next level*/
		int index; /*the payload. Only has a meaningful value if this is in the last level*/

		PNGColorTree();


		static unsigned int color_tree_add(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned index);
	};
}