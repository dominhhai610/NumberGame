#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "string.h"
#include "SimpleAudioEngine.h"
using namespace std;
using namespace cocos2d;
USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
public:
    Sprite* snumber;    //number to move
    Sprite* anumber;    //static number 1
    Sprite* bnumber;    //statuc number 2
    Sprite* cnumber;    //static number 3
    
    
    std::vector<int> _originalNumber;
    std::vector<int>    _number;
    int isdeleted =0;
    int point = -1;
    int state = 0;
    unsigned int isPlayingEffect = -1;
    bool isInitialize = false;
    std::string rightThings = "";
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    // switch game
    void menuSwitchGame(cocos2d::Ref* pSender);
    
    
    /* 
     * SKID.SMART.NUMBER
     */
    
    // xu ly va cham
    bool onContactBegin(const PhysicsContact& contact);
    
    // return touching point
   // Point touchToPoint(cocos2d::Touch* touch);
    
    // Returns true if the touch is within the boundary of our sprite
    bool isTouchingSprite(cocos2d::Touch* touch ,cocos2d::Event* event);
    
    // delete sprite when move finished
     void spriteMoveFinished(cocos2d::Node* sender);     // remove Sprite from game scene
    
    // xu ly touch
    //virtual bool onTouchBegan(cocos2d::Touch* touches,cocos2d::Event* event);
    virtual bool onTouchBegan(cocos2d::Touch* touches,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touches,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touches,cocos2d::Event* event);
    
    
    // ham tao day hoa hong chua thanh diem
    virtual void addhoahong();
    virtual void hithoahong(int point);
    
    
    
    
    
    // xu ly logic
    void gameLogic(float dt);                                     // goi den logic game se dung trong ham schedule
    void numbers();                                               // create new number and add them to sence
    //void moveNumbers(Sprite* A,Sprite* B,Sprite* C);              // move
    void deleteNumbers();                                         // when user touch right number delete all of current sprite
    std::string generate_name();
    std::string generate_background();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
