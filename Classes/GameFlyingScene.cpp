//
//  GameFlying.cpp
//  Number
//
//  Created by Do Minh Hai on 10/8/14.
//
//

#include <cocos2d.h>
#include "GameFlyingScene.h"
#include "HelloWorldScene.h"
#include "GameFlyingScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace cocos2d;



Scene* GameFlyingLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    //thiet lap trong luc
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);   // debug to view all scope of sprites
    scene->getPhysicsWorld()->setGravity(Vect(0.0f,0.0f));                     // trong luc = 0
    
    
    // 'layer' is an autorelease object
    auto layer = GameFlyingLayer::create();
    scene->addChild(layer);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundforkid.mp3", true);    // true = lap lai vo han
    
    
    // add layer as a child to scene
//    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}



bool GameFlyingLayer::init()
{
    // thuc hien khoi tao Layer
    if ( !LayerColor::initWithColor(ccc4(255,255, 255, 255)) )
    {
        return false;
    }
    
        Size winsize = Director::getInstance()->getWinSize();
        auto gameOverImage = Sprite::create("touching_cow.png");
        gameOverImage->setPosition(winsize.width/2,winsize.height/2);
        
        this->addChild(gameOverImage);

    
    // add a "close" icon to exit the progress. it's an autorelease object
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Point origin = Director::getInstance()->getVisibleOrigin();
  
    
    
    
//    
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(GameFlyingScene::menuCloseCallback, this));
//
//    
//    closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                 origin.y + closeItem->getContentSize().height/2));
//    
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Point::ZERO);
//    this->addChild(menu, 1);
    
    
    
    
    return true;
    
}





GameFlyingLayer::~GameFlyingLayer()
{
    // release Layer if needed
}



bool GameFlyingScene::init()
{
    if(Scene::init()){
        auto sceneImage = Sprite::create("touching_cow.png");
        sceneImage->setScale(0.2, 0.2);
        this->addChild(sceneImage);
        return true;
    }
    return false;
}



GameFlyingScene::~GameFlyingScene()
{
    // release Scene if needed
}



// a selector callback
void GameFlyingScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}