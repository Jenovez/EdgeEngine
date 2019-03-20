/********************************************
名称:
说明:
1.
********************************************/

#ifndef __SKELETON_ANIMATION_H_H__
#define __SKELETON_ANIMATION_H_H__

#include "SkeletonNode.h"

NS_EDGE_BEGIN

struct SkeletonData
{
};

class EDGE_DLL SkeletonAnimation final
{
public:

private:
	std::map<std::string, SkeletonNode*> _skeletonRootList;
};

NS_EDGE_END

#endif // __SKELETON_ANIMATION_H_H__