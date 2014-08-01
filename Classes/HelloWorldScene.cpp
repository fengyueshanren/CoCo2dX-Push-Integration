#include "HelloWorldScene.h"
#include "AppMacros.h"


#include "platform/android/jni/JniHelper.h"
#include "platform/CCCommon.h"
USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jint Java_app42_push_coco_PushHelper_sendRegId(JNIEnv *env, jobject obj,jstring regId){
	printf("send RegiD");
       return 1;
    }
#endif
}

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jint Java_app42_push_coco_PushHelper_sendMessage(JNIEnv *env, jobject obj,jstring message){
	printf("Send message");
        return 11;
    }
#endif
}
void registerForPush()
{    JniMethodInfo t;
    if(JniHelper::getStaticMethodInfo(t,"app42/push/coco/PushHelper","registerForPush","(Ljava/lang/String;)V"))
    {    const char* myName = "676734267";
	jstring stringArg1 = t.env->NewStringUTF(myName);
    t.env->CallStaticBooleanMethod(t.classID,
       t.methodID,
        stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
    }
}

void getLastMessage()
{    JniMethodInfo t;
    if(JniHelper::getStaticMethodInfo(t,"app42/push/coco/PushHelper","getLastMeassage","(Ljava/lang/String;)Ljava/lang/String;"))
    {    const char* myName = "676734267";
	jstring stringArg1 = t.env->NewStringUTF(myName);
    t.env->CallStaticBooleanMethod(t.classID,
       t.methodID,
        stringArg1);
		//string ret = JniHelper::jstring2string(myVal);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
    }
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
   
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

   registerForPush();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
