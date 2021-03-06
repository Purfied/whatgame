#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(ccc4(0, 0, 0, 255)) )
    {
        return false;
    }
    
	/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0
	*/

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* player = CCSprite::create("player.png");
	player->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(player);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Start",
		CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item2 = MenuItemFont::create("Option",
		CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));

	/*
	MenuItemAtlasFont * item2 = MenuItemAtlasFont::create("Help",
		"weixin.png", 48, 65, ' ',
		CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	item2->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - 10));
	this->addChild(item2);
	*/

	Menu * mn = Menu::create(item1, item2, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuItem1Callback(Ref * pSender) {
	
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);

}

void HelloWorld::menuItem2Callback(Ref * pSender) {

	auto sc = OptionPage::createNewScene();
	Director::getInstance()->pushScene(sc);

}

void GameStartPage::menuItemCallback(Ref * pSender) {

	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);

}

void OptionPage::menuItemCallback(Ref * pSender) {

	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);
}


Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();

	auto layer = GameStartPage::create();
	
	scene->addChild(layer);

	return scene;
}

bool GameStartPage::init() {
	//将背景设置为绿色
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;


	//创建返回开始菜单的按钮，以及背景图片的设置
	/*
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Back",
		CC_CALLBACK_1(GameStartPage::menuItemCallback, this));
	*/
	Size screenSize = Director::getInstance()->getVisibleSize();
	Sprite* qqSprite = Sprite::create("qq.png");

	qqSprite->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	qqSprite->setScale(0.3);
	this->addChild(qqSprite);

	auto action = MoveBy::create(3, Point(100, 0));

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch(keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			event->getCurrentTarget()->setPosition(loc.x -=10, loc.y);
			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(loc.x += 10, loc.y);
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			event->getCurrentTarget()->setPosition(loc.x, loc.y += 10);
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, loc.y -= 10);
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority
	(eventListener, qqSprite);

	/*
	Menu * mn = Menu::create(item1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
	*/
	//创建返回开始菜单的按钮，以及背景图片的设置


	return true;
}

Scene* OptionPage::createNewScene() {
	auto scene = Scene::create();

	auto layer = OptionPage::create();

	scene->addChild(layer);

	return scene;
}

bool OptionPage::init() {

	if (!LayerColor::initWithColor(Color4B(255, 0, 0, 255)))
		return false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Back",
		CC_CALLBACK_1(OptionPage::menuItemCallback, this));

	Size screenSize = Director::getInstance()->getVisibleSize();
	Sprite* button = Sprite::create("qqcom.png");
	button->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	button->setScale(0.3);
	this->addChild(button);

	Menu * mn = Menu::create(item1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}


