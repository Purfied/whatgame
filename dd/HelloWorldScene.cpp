#if 1
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CollisionTest.h"
#include "TestStartPage.h"

USING_NS_CC;

/*HelloWorld::HelloWorld()
{

	_tilemap = NULL;
	_background = NULL;
}*/

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
		if (!LayerColor::initWithColor(ccc4(0,255,255,255)))
		{
			return false;
		}
		
#if 0
		std::string file = "04.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
		_background = _tileMap->layerNamed("background");

		addChild(_tileMap, -1);
#endif
		/*
		TMXObjectGroup *objects = _tileMap->getObjectGroup("Object-Player");
		CCASSERT(NULL != objects, "'Object-Player' object group not found");

		auto playerShowUpPoint = objects->getObject("PlayerShowUpPoint");
		CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");


		int x = playerShowUpPoint["x"].asInt();
		int y = playerShowUpPoint["y"].asInt();


		_player = Sprite::create("wall.png");
		_player->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
		_player->setScale(0.5);


		addChild(_player);
		setViewPointCenter(_player->getPosition());*/

		CCSize screensize = CCDirector::sharedDirector()->getVisibleSize();

		auto player = CCSprite::create("testball.png");
		player->setPosition(ccp(0 + 40, screensize.height / 2));
		player->setTag(1);

		auto bg = Sprite::create("testBG.png");
		bg->setPosition(Vec2(screensize.width / 2, screensize.height / 2));
		this->addChild(bg);

		this->addChild(player);

		auto item1 = MenuItemAtlasFont::create("100", "wall.png", 16, 24, '.');

		MenuItemFont::setFontName("Arial");
		MenuItemFont::setFontSize(86);
		auto item2 = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::mydefine2,this));
		auto menu = Menu::create(item1, item2, NULL);
		menu->alignItemsVerticallyWithPadding(10);

		//menu->setPosition(ccp(200, screensize.height / 2));
		this->addChild(menu);

		//a set of action
#if 0
		CCCallFuncN* selfdefineaction = CCCallFuncN::create(CC_CALLBACK_1(HelloWorld::mydefine,this));
		CCMoveTo* move = CCMoveTo::create(10, ccp(180, 40));
		CCSequence* action = CCSequence::create(move, selfdefineaction, NULL);
		player->runAction(action);
#endif
		
		//touch
#if 0
		//this->setTouchEnabled(true);
		auto touchListenerOne = EventListenerTouchOneByOne::create();
		//touchListenerOne -> setSwallowTouches(true);
		touchListenerOne -> onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
		touchListenerOne ->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
		touchListenerOne ->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
		
		_eventDispatcher-> addEventListenerWithSceneGraphPriority(touchListenerOne, this);


#endif
#if 1
		auto kblistener = EventListenerKeyboard::create();
		kblistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
		kblistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(kblistener, this);
#endif

#if 1
		auto testMonster = Sprite::create("vampire.png");
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster->setPosition(Vec2(screensize.width / 2, screensize.height / 2));
		testMonster->setScale(0.2);
		testMonster->setName("vampire");
		this->addChild(testMonster);


#endif
}

bool HelloWorld::isHold(EventKeyboard::KeyCode code)
{

	// Check if the key is currently pressed by seeing it it's in the std::map keys

	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?

	if (keys.find(code) != keys.end())
		return true;
	return false;

}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	auto player = this->getChildByTag(1);
	auto cp = player->getPosition();
	auto testMonster = this->getChildByName("vampire");

	auto playerP = player->getPosition();
	auto playerS = player->getContentSize();
	int pwith = player->getScale()*playerS.width;
	int pheig = playerS.height*player->getScale();
	log("pwidth %d", pwith);
	log("pheight %d",pheig);
	auto monsterP = testMonster->getPosition();
	auto monsterS = testMonster->getContentSize();
	int mwith = testMonster->getScale()*monsterS.width;
	int mheig = monsterS.height*testMonster->getScale();
	log("mwidth %d", mwith);
	log("mheight %d", mheig);

		const float d = 10;
		hold = 1;
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			log("up");
			//while (HelloWorld::isHold(EventKeyboard::KeyCode::KEY_UP_ARROW))
			{
				cp = player->getPosition();
				log("cp x %f", cp.x);
				log("cp y %f", cp.y);
				log("cm x %f", monsterP.x);
				log("cm y %f", monsterP.y);
				if (CollisionTest::isCollision(cp.x, cp.y + d, pwith, pheig, monsterP.x, monsterP.y, mwith,mheig))
				{
					log("no");
					if (cp.x > monsterP.x )
						if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
							player->setPosition(Vec2(cp.x + 5, cp.y));
						}
						else { ; }

					else if (cp.x < monsterP.x)
						if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
							player->setPosition(Vec2(cp.x - 5, cp.y));
						}
						else { ; }
					/*else
					{
						int r = random(0, 1);
						if (r == 0)
							player->setPosition(Vec2(cp.x + 5, cp.y));
						else
							player->setPosition(Vec2(cp.x - 5, cp.y));
					}*/
				}
				else
				{
					log("yes");
					player->setPosition(Vec2(cp.x, cp.y + d));
				}
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			log("down");
			cp = player->getPosition();
			if (CollisionTest::isCollision(cp.x, cp.y - d, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.x > monsterP.x)
					if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
						player->setPosition(Vec2(cp.x + 5, cp.y));
					}
					else { ; }

				else if (cp.x < monsterP.x)
					if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
						player->setPosition(Vec2(cp.x - 5, cp.y));
					}
					else { ; }
			}
			else
				player->setPosition(Vec2(cp.x, cp.y - d));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			log("down");
			cp = player->getPosition();
			if (CollisionTest::isCollision(cp.x-d, cp.y, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						player->setPosition(Vec2(cp.x , cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
						if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
							player->setPosition(Vec2(cp.x, cp.y - 5));
						}
						else { ; }
			}
			else
				player->setPosition(Vec2(cp.x - d, cp.y));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			log("down");
			cp = player->getPosition();
			if (CollisionTest::isCollision(cp.x + d, cp.y, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						player->setPosition(Vec2(cp.x, cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
					if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
						player->setPosition(Vec2(cp.x, cp.y - 5));
					}
					else { ; }
			}
			else
				player->setPosition(Vec2(cp.x + d, cp.y));
			break;
	

	//if (HelloWorld::isHold(EventKeyboard::KeyCode::KEY_UP_ARROW))
	/*{
		log('123');
		cp = player->getPosition();
		player->setPosition(Vec2(cp.x, cp.y + d));
	}*/


	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	hold = 0;
	log("THere");
}
	/*
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
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
	CCSprite *sprite1 = CCSprite::create("HelloWorld.png");
	//auto sprite2 = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
	auto winSize = Director::getInstance()->getVisibleSize();

	sprite->setPosition(Vec2(winSize.width * 0.3, winSize.height * 0.5));

	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
    //return true;

bool HelloWorld::onTouchBegan(CCTouch *pTouch, CCEvent *event)
{
	//CCTouch* touch = (CCTouch) pTouches -> anyObject();
	CCSize screensize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint locInView = pTouch->getLocationInView();
	CCPoint loc = CCDirector::sharedDirector()->convertToGL(locInView);

	auto bullet = CCSprite::create("testball.png");
	bullet -> setScale(0.1);
	bullet->setPosition(ccp(0 + 40, screensize.height / 2));
	this->addChild(bullet);

	auto move = CCMoveTo::create(2, ccp(loc.x,loc.y));
	auto actionRemove = RemoveSelf::create();

	bullet -> runAction(Sequence::create(move,actionRemove, NULL));
	return true;
}

void HelloWorld::mydefine2(Ref *sender)
{

	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);

}

void HelloWorld::mydefine(Ref* who)
{
	Sprite* sprite = static_cast<Sprite*>(who);

	sprite ->setPosition(ccp(300, 80));
	sprite ->setScale(2);

	//this->removeChild(sprite);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);



}



void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();


	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);


	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> HelloWorld::keys;
#endif

#if 0
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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}


	auto   screenSize = Director::getInstance()->getWinSize();
	auto player = Sprite::create("testball.png");
	player->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	this->addChild(player);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Start",
		CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));

	/*
	MenuItemAtlasFont * item2 = MenuItemAtlasFont::create("Help",
	"weixin.png", 48, 65, ' ',
	CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	item2->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - 10));
	this->addChild(item2);
	*/

	Menu * mn = Menu::create(item1, NULL);
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

void GameStartPage::menuItemCallback(Ref * pSender) {

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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	/*
	//another menu
	auto item1 = MenuItemFont::create("Back",
	CC_CALLBACK_1(GameStartPage::menuItemCallback, this));
	*/
	//another sprite
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto  qqSprite = Sprite::create("HelloWorld.png");

	qqSprite->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	qqSprite->setScale(0.3);
	this->addChild(qqSprite);
	qqSprite->setTag(12);

	//Menu * mn = Menu::create(item1,  NULL);
	//mn->alignItemsVertically();
	//this->addChild(mn);


	//create a keyboard listener to move the object.
	auto eventListener = EventListenerKeyboard::create();

	/*
	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
	Vec2 loc = event->getCurrentTarget()->getPosition();

	switch (keyCode) {
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
	};
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority
	(eventListener, qqSprite);
	*/
	label = cocos2d::Label::createWithSystemFont("Press the CTRL Key", "Arial", 32);
	label->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	//addChild(label);

	//here is implementation of keyboard scene from game from scratch
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	// Let cocos know we have an update function to be called.
	// No worries, ill cover this in more detail later on
	this->scheduleUpdate();
	return true;
}

bool GameStartPage::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

double GameStartPage::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
		return 0;  // Not pressed, so no duration obviously

				   // Return the amount of time that has elapsed between now and when the user
				   // first started holding down the key in milliseconds
				   // Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void GameStartPage::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	auto sprite = this->getChildByTag(12);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		sprite->setPositionX(sprite->getPositionX() - delta * 1000);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		sprite->setPositionX(sprite->getPositionX() + delta * 1000);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
		sprite->setPositionY(sprite->getPositionY() - delta * 1000);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
		sprite->setPositionY(sprite->getPositionY() + delta * 1000);
	}
	/*
	Node::update(delta);

	if(isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL)) {
	std::stringstream ss;
	ss << "Control key has been pressed for " <<
	keyPressedDuration(EventKeyboard::KeyCode::KEY_CTRL) << " ms";
	label->setString(ss.str().c_str());

	}    else {
	label->setString("Press the CTRL Key");
	}
	*/
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;
#endif
