#include "HelloWorldScene.h"
#include "string.h"
#include "SimpleAudioEngine.h"
#include "GameFlyingScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setGravity(Vect(0.0f,0.0f));                     // trong luc = 0
    
    auto layer = HelloWorld::create();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundforkid.mp3", true);    // true = lap lai vo han
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
   if ( !LayerColor::initWithColor(ccc4(255,255, 255, 255)) )
    {
        return false;
    }
    
    //init for games
    if(_originalNumber.size() == 0)
    {
        for (int i = 1; i<10; i++) {
            _originalNumber.push_back(i);
        }
    }
    _number = _originalNumber;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tiengvotay2s.mp3");
    
    this->isdeleted = 0;
    this->point = -1;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    this->setTouchEnabled(true);

    std::string bgrimage = generate_background();
    auto bgr = Sprite::create(bgrimage);
    bgr->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bgr);
    
    
    // resize for screen
    float rX = visibleSize.width / bgr->getContentSize().width;
    float rY = visibleSize.height / bgr->getContentSize().height;
    bgr->setScaleX(rX);
    bgr->setScaleY(rY);
    
    
    auto listener1 = EventListenerPhysicsContact::create();
    auto listener3 = EventListenerTouchOneByOne::create();
    
    listener1->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this); // contact began on this scene
    listener3->onTouchBegan   = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener3->onTouchMoved   = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener3->onTouchEnded   = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener3->setSwallowTouches(true);
    
    auto _dispatcher = Director::getInstance()->getEventDispatcher();
    _dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);       // thuc hien lang nghe su kien contact
    _dispatcher->addEventListenerWithSceneGraphPriority(listener3, this);       // thuc hien lang nghe su kien touch
    
    this->gameLogic(1);         // goi ham gameLogic

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    return true;
}

void HelloWorld::gameLogic(float dt){
    _number = _originalNumber;
    this->removeChildByTag(9);
    this->numbers();
}

void HelloWorld::numbers(){
    Size winsize = Director::getInstance()->getWinSize();
    
    float nHeigh = 2*(winsize.height/3);
    if(this->isPlayingEffect != -1)
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(this->isPlayingEffect);

    std::string s_name1 = this->generate_name();
    auto number1 = Sprite::create("a" + s_name1);
    auto body1 = PhysicsBody::createCircle(number1->getContentSize().width*2);
    body1->setContactTestBitmask(0x1);
    number1->setScale(2.0f, 2.0f);
    number1->setPhysicsBody(body1);
    number1->setTag(1);
   
    // number2
    std::string s_name2 = s_name1;
    while (s_name1.compare(s_name2)==0) {
        s_name2 = this->generate_name();
    }
    auto number2 = Sprite::create("a" + s_name2);
    auto body2 = PhysicsBody::createCircle(number2->getContentSize().width*2);
    number2->setScale(2.0f, 2.0f);
    number2->setTag(-2);
    
    // number3
    std::string s_name3 = s_name1;
    while (s_name3.compare(s_name2)==0 || s_name3.compare(s_name1) == 0) {
        s_name3= this->generate_name();
    }
    this->generate_name();
    auto number3 = Sprite::create("a" + s_name3);
    auto body3 = PhysicsBody::createCircle(number3->getContentSize().width*2);
    number3->setScale(2.0f, 2.0f);
    number3->setTag(-3);
    
    // number to catch
    std::string s_catch = "a" + s_name1;
    auto number = Sprite::create(s_catch);
    number->setPosition(winsize.width/2 , nHeigh/2);
    auto body = PhysicsBody::createCircle(number->getContentSize().width);
    body->setContactTestBitmask(0x1);
    number->setPhysicsBody(body);
    number->setScale(2.0f, 2.0f);
    number->setTag(4);

    Point p1 = Point(winsize.width/6 ,nHeigh +200);
    Point p2 = Point(winsize.width/3 + winsize.width/6 ,nHeigh + 200);
    Point p3 = Point(2*(winsize.width/3) + winsize.width/6 ,nHeigh + 200);
    srand(time(NULL));
    int decession1 = rand();
    int decession2 = rand();
    if(decession1%3==0){
        number1->setPosition(p1);
        if(decession2%2==0){
            number2->setPosition(p2);
            number3->setPosition(p3);
        }
        else{
            number2->setPosition(p3);
            number3->setPosition(p2);
        }
            
    }
    else if (decession1%3==1){
        number1->setPosition(p2);
        if(decession2%2==0){
            number2->setPosition(p1);
            number3->setPosition(p3);
        }
        else{
            number2->setPosition(p3);
            number3->setPosition(p1);
        }

    }
    else{
        number1->setPosition(p3);
        if(decession2%2==0){
            number2->setPosition(p1);
            number3->setPosition(p2);
        }
        else{
            number2->setPosition(p2);
            number3->setPosition(p1);
        }
    }
    
    
    auto actionMove1 = MoveTo::create(1, Point(number1->getPosition().x, number1->getPosition().y -200));
    auto actionMove2 = MoveTo::create(1, Point(number2->getPosition().x, number2->getPosition().y -200));
    auto actionMove3 = MoveTo::create(1, Point(number3->getPosition().x, number3->getPosition().y -200));

    
    // add there numbers to this sence
    this->rightThings = "x" + s_name1;
    this->snumber = (Sprite*) number;
    this->anumber = (Sprite*) number1;
    this->bnumber = (Sprite*) number2;
    this->cnumber = (Sprite*) number3;
    
    // created new ,thereforce is not deleted
    this->isdeleted = 0;
    
    this->addChild(this->anumber);
    this->addChild(this->bnumber);
    this->addChild(this->cnumber);
    this->addChild(this->snumber);
    
    // play sound for true number
    this->isPlayingEffect = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tiengvotay2s.mp3");
    number1->runAction(actionMove1);
    number2->runAction(actionMove2);
    number3->runAction(actionMove3);

}

// generate random name for Sprite
std::string HelloWorld::generate_name(){
    std::string str = "number";
    srand(time(NULL));
    int size = _number.size();
    int index = rand()%size;
    int num = _number.at(index);
    std::stringstream ss;
    ss << num;
    std::string str1 = ss.str();
    str = str.append(str1);
    str = str.append(".png");
    _number.erase(_number.begin() + index);
    return str;
}

std::string HelloWorld::generate_background(){
    std::string str = "childrenhool_brg";
    srand(time(NULL));
    int num = rand()%2;
    std::stringstream ss;
    ss << num;
    std::string str1 = ss.str();
    str = str.append(str1);
    str = str.append(".png");
    return str;
}

bool HelloWorld::isTouchingSprite(Touch* touch ,Event* event)
{
    Point p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    if(this->isdeleted==0 ){
        float dis = p.getDistance(snumber->getPosition());
        return dis < 100.0f;
    }
    return false;
}


bool HelloWorld::onTouchBegan(Touch* touches,Event* event){
    if(isTouchingSprite(touches,event))
    return true;
    else
        return false;
    return true;
}
void HelloWorld::onTouchMoved(Touch* touches,Event* event){
        Point ptouch = touches->getLocationInView();
        ptouch = Director::getInstance()->convertToGL(ptouch);
        if(this->isdeleted != 0)
            return;
        else
            this->snumber->setPosition(ptouch);
    
    return;
    
}
void HelloWorld::onTouchEnded(Touch* touches,Event* event)
{
}


// xu ly va cham
bool HelloWorld::onContactBegin(const PhysicsContact &contact){
    // lay doi tuong va cham
    auto _obj1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto _obj2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
    if(_obj1 == NULL || _obj2 == NULL)
        return false;
    
    bool isTrueContact = false;
    if(_obj1->getTag() == 1 && _obj2->getTag() == 4){
        Point x = _obj1->getPosition();
        this->isdeleted = 1;
        auto apple = Sprite::create(this->rightThings);
        apple->setPosition(x);
        apple->setTag(9);
        apple->setScale(2.0f, 2.0f);
        
        this->removeChild(snumber);
        this->removeChild(anumber);
        this->removeChild(bnumber);
        this->removeChild(cnumber);
        this->addChild(apple);
        isTrueContact = true;
        CCLOG("%f : %f /n",x.x,x.y);
        CCLOG("ON CONTACT BEGIN");
    }
    else if (_obj1->getTag() == 4 && _obj2->getTag() == 1){
        
        Point x = _obj2->getPosition();
        this->isdeleted = 1;
        
        auto apple = Sprite::create(this->rightThings);
        apple->setPosition(x);
        apple->setTag(9);
        apple->setScale(2.0f, 2.0f);
        this->removeChild(snumber);
        this->removeChild(anumber);
        this->removeChild(bnumber);
        this->removeChild(cnumber);
         isTrueContact = true;
        this->addChild(apple);
        CCLOG("%f : %f /n",x.x,x.y);
        CCLOG("ON CONTACT BEGIN");
    }
    
    if(isTrueContact)
    {
        // move
        if(this->point<9){
            this->point++;
            this->hithoahong(this->point);
            auto delayAction = DelayTime::create(0.5);
            auto actionMoveFinished = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
            this->isdeleted = 1;            // number is deleted
            this->deleteNumbers();
            this->runAction(Sequence::create(delayAction,actionMoveFinished,NULL));
        }
        else
        {
            auto delayAction = DelayTime::create(0.5);
            auto actionMoveFinished = CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
            this->runAction(Sequence::create(delayAction,actionMoveFinished,NULL));
        }
    }

    return true;
}

void HelloWorld::deleteNumbers(){
    this->isInitialize = false;
    this->isdeleted = 1;

}


void HelloWorld::spriteMoveFinished(Node *sender){
    //this->init();
    if(this->point<9)
        this->gameLogic(1);
    else
        this->init();
}


// add hoa hong chua tinh diem
void HelloWorld::addhoahong()
{

    Size winsize = Director::getInstance()->getWinSize();
    for (int dem =0; dem<10; dem++) {
        auto hoahong = Sprite::create("bhoahong_point.png");
        hoahong->setScale(0.1f, 0.1f);
         hoahong->setPosition(0.05* hoahong->getContentSize().width + dem * 0.05 * hoahong->getContentSize().width,winsize.height - 0.05 * hoahong->getContentSize().height);
        //    hoahong->setPosition(winsize.width/5. ,winsize.height/5);
        this->addChild(hoahong);
    }
   
}

// add hoa hong da tinh diem
void HelloWorld::hithoahong(int _point)
{
    Size winsize = Director::getInstance()->getWinSize();
    Sprite* hoahong;
   // switch (this->state) {
    srand(time(NULL));
    switch (rand()%4) {
        case 0:
               hoahong = Sprite::create("hoahong_point_x1.png");
            break;
        case 1:
               hoahong = Sprite::create("hoahong_point_x2.png");
            break;
        case 2 :
               hoahong = Sprite::create("hoahong_point_x3.png");
            break;
        case 3:
               hoahong = Sprite::create("hoahong_point_x4.png");
            break;
            
        default:
             auto hoahong = Sprite::create("hoahong_point_x0.png");
            break;
    }
    
        hoahong->setScale(0.1f, 0.1f);
        hoahong->setPosition(0.05* hoahong->getContentSize().width + _point * 0.05 * hoahong->getContentSize().width,winsize.height - 0.05 * hoahong->getContentSize().height);
        //    hoahong->setPosition(winsize.width/5. ,winsize.height/5);
        this->addChild(hoahong);
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



