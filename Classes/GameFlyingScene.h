//
//  GameFlying.h
//  Number
//
//  Created by Do Minh Hai on 10/8/14.
//
//
#include <cocos2d.h>
USING_NS_CC;
using namespace cocos2d;


#ifndef Number_GameFlying_h
#define Number_GameFlying_h

class GameFlyingLayer: public cocos2d::LayerColor{
    
    public :
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    
//    GameFlyingLayer();      // constructors  => this only call parent method
    virtual ~GameFlyingLayer();     // destructor
    
    virtual bool init();
    
    CREATE_FUNC(GameFlyingLayer);
};

class GameFlyingScene: public cocos2d::Scene{
    public :
    

    
    GameFlyingScene();      // constructor  => this only call parent method
    virtual ~GameFlyingScene();     // destructor
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
};



#endif
