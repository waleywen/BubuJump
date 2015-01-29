#ifndef __UIHelper_H__
#define __UIHelper_H__

#include "cocos2d.h"

class UIHelper
{
public:
    static cocos2d::Node* seekNodeByTag(cocos2d::Node* root, int tag)
    {
        if (!root)
        {
            return nullptr;
        }
        if (root->getTag() == tag)
        {
            return root;
        }
        const auto& arrayRootChildren = root->getChildren();
        ssize_t length = arrayRootChildren.size();
        for (ssize_t i=0;i<length;i++)
        {
            cocos2d::Node* child = dynamic_cast<cocos2d::Node*>(arrayRootChildren.at(i));
            if (child)
            {
                cocos2d::Node* res = seekNodeByTag(child,tag);
                if (res != nullptr)
                {
                    return res;
                }
            }
        }
        return nullptr;
    }
    
    static cocos2d::Node* seekNodeByName(cocos2d::Node* root, const std::string& name)
    {
        if (!root)
        {
            return nullptr;
        }
        if (root->getName() == name)
        {
            return root;
        }
        const auto& arrayRootChildren = root->getChildren();
        for (auto& subWidget : arrayRootChildren)
        {
            cocos2d::Node* child = dynamic_cast<cocos2d::Node*>(subWidget);
            if (child)
            {
                cocos2d::Node* res = seekNodeByName(child,name);
                if (res != nullptr)
                {
                    return res;
                }
            }
        }
        return nullptr;
    }
};

#endif // __UIHelper_H__
