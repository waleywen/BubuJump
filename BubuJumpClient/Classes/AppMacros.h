#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_720X1280    1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_720X1280

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static cocos2d::Size size720 = cocos2d::Size(720, 1280);

static Resource smallResource  =  { size720, "720P" };
static Resource mediumResource =  { size720, "720P" };
static Resource largeResource  =  { size720, "720P" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = size720;
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_720X1280)
static cocos2d::Size designResolutionSize = size720;
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = size720;
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#define CREATE_SCENE_FUNC(__TYPE__) \
static cocos2d::Scene* createScene() \
{ \
    cocos2d::Scene* scene = cocos2d::Scene::create(); \
    scene->addChild(__TYPE__::create()); \
    return scene; \
}


#endif /* __APPMACROS_H__ */
