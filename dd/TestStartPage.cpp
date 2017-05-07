#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "PlayerLayer.h"

USING_NS_CC;

//void GameStartPage::menuItemCallback(Ref * pSender) {
//    
//    auto sc = HelloWorld::createScene();
//    Director::getInstance()->pushScene(sc);
//}


Scene* GameStartPage::createNewScene() {
    auto scene = Scene::create();
    
	//auto bg = GameStartPage::create();

	auto layer = GameStartPage::create();

	//scene->addChild(bg,0);
	scene->addChild(layer,1);
    
    return scene;
}

bool GameStartPage::init() {
    if (!Layer::init())
        return false;

	//character maincharacter;
	screenO = Director::getInstance()->getVisibleOrigin();

    MenuItemFont::setFontName("Times New Roman");
    MenuItemFont::setFontSize(86);

	auto screenSize = Director::getInstance()->getVisibleSize();


	auto bg = Sprite::create("Map.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	bg->setTag(1);
	this->addChild(bg, -1);

#if 1
	auto playerl = PlayerLayer::create();
	this->addChild(playerl);
	playerl->setName("playerl");
	auto sprite = playerl->getChildByTag(10);
	//sprite->setTag(1);
#endif
#if 0
    //first sprite in game start page

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(40, screenSize.height / 2));
    sprite->setScale(0.3);
    this->addChild(sprite);
    sprite->setTag(1);

#endif
   
    auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioengine->preloadBackgroundMusic("bgmusic.mp3");
    audioengine->playBackgroundMusic("bgmusic.mp3");
    
#if 1
	auto testMonster = Sprite::create("vampire.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	testMonster->setScale(0.1);
	testMonster->setTag(2);
	__String* nameCC = __String::createWithFormat("Monster_%d", 1);
	std::string a = nameCC->getCString();

	testMonster->setName("Monster_1");
	this->addChild(testMonster);

	auto testMonster2 = Sprite::create("demon.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster2->setPosition(Vec2(screenSize.width / 2+40, screenSize.height / 2));
	testMonster2->setScale(0.1);
	testMonster2->setTag(2);
	testMonster2->setName("Monster_2");
	this->addChild(testMonster2);
#endif
	//initialize collision list
	
	//create a keyboard listener to move the object.
	auto eventListener = EventListenerKeyboard::create();
	
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);

    //create a keyboard listener to move the object.
    
    
    
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
    

	initCL();
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
    return std::chrono::duration_cast<std::chrono::seconds>
    (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void GameStartPage::update(float delta) {



    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
	keyEvent(delta);

}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;

void GameStartPage::keyEvent(float delta) {
	auto screenSize2 = Director::getInstance()->getVisibleSize();
	auto sprite = this->getChildByName("playerl")->getChildByTag(10);
	int speed = maincharacter.get_speed();
	//auto testMonster = this->getChildByTag(2);
	//    auto sprite2 = this ->getChildByTag(2);
	//auto weaponSprite = this->getChildByTag(2);
	auto cp = sprite->getPosition();
	auto playerP = sprite->getPosition();
	auto playerS = sprite->getContentSize();
	int pwith = sprite->getScale()*playerS.width;
	int pheig = playerS.height*sprite->getScale();
	//log("pwidth %d", pwith);
	//log("pheight %d", pheig);
	/*auto monsterP = testMonster->getPosition();
	auto monsterS = testMonster->getContentSize();
	int mwith = testMonster->getScale()*monsterS.width;
	int mheig = monsterS.height*testMonster->getScale();*/
	//log("mwidth %d", mwith);
	//log("mheight %d", mheig);
	auto remove = RemoveSelf::create();

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)
		&& sprite->getPositionX() >= sprite->getContentSize().height*sprite->getScale()*0.5) {
		cp = sprite->getPosition();
		updateCL();
		PandS hitted = cheakCL(cp.x - delta* speed, cp.y, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			log("no");
			
			hittedSprite->runAction(remove);
			auto monsterP = hittedSprite->getPosition();
			auto monsterS = hittedSprite->getContentSize();
			int mwith = hittedSprite->getScale()*monsterS.width;
			int mheig = monsterS.height*hittedSprite->getScale();

			if (cp.y > monsterP.y)
				if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
					sprite->setPosition(Vec2(cp.x, cp.y + 5));
				}
				else { ; }

			else if (cp.y < monsterP.y)
				if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
					sprite->setPosition(Vec2(cp.x, cp.y - 5));
				}
				else { ; }
		}

		else
		{
			if (cp.x - screenO.x > screenSize2.width / 4 )
			{
				//sprite->setPosition(Vec2(cp.x - delta * speed, cp.y));
				sprite->setPositionX(cp.x - delta* speed);
				log("yes");
			}
			else
			{
				sprite->setPosition(Vec2(cp.x - delta * speed, cp.y));
				this->setPosition(Vec2(this->getPosition().x + delta * speed, this->getPosition().y));
				screenO.x -= delta * speed;
			}
		}
			//sprite->setPositionX(cp.x - delta* speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)
		){//&& sprite->getPositionX() <= screenSize2.width) {
		cp = sprite->getPosition();
		updateCL();
		PandS hitted = cheakCL(cp.x + delta* speed, cp.y, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite1 = this->getChildByName(hitted.name);
			//auto remove1 = RemoveSelf::create();
			
			log("no");
			auto monsterP = hittedSprite1->getPosition();
			auto monsterS = hittedSprite1->getContentSize();
			int mwith = hittedSprite1->getScale()*monsterS.width;
			int mheig = monsterS.height*hittedSprite1->getScale();

			hittedSprite1->runAction(remove);

			if (cp.y > monsterP.y)
				if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
					sprite->setPosition(Vec2(cp.x, cp.y + 5));
				}
				else { ; }

			else if (cp.y < monsterP.y)
				if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
					sprite->setPosition(Vec2(cp.x, cp.y - 5));
				}
				else { ; }
		}
		else
		{
			if (cp.x - screenO.x < screenSize2.width / 4 * 3)
			{
				sprite->setPosition(Vec2(cp.x + delta * speed, cp.y));
				log("yes");
			}
			else
			{
				sprite->setPosition(Vec2(cp.x + delta * speed, cp.y));
				this->setPosition(Vec2(this->getPosition().x - delta * speed, this->getPosition().y));
				screenO.x += delta * speed;
			}
		}
			//sprite->setPositionX(sprite->getPositionX() + delta * speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)
		&& sprite->getPositionY() >= sprite->getContentSize().height*sprite->getScale()*0.5) {
		cp = sprite->getPosition();
		updateCL();
		PandS hitted = cheakCL(cp.x , cp.y - delta* speed, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			//auto remove = RemoveSelf::create();
			//hittedSprite->runAction(remove);
			log("no");
			auto monsterP = hittedSprite->getPosition();
			auto monsterS = hittedSprite->getContentSize();
			int mwith = hittedSprite->getScale()*monsterS.width;
			int mheig = monsterS.height*hittedSprite->getScale();
			hittedSprite ->runAction(remove);

			if (cp.x > monsterP.x)
				if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
					sprite->setPosition(Vec2(cp.x + 5, cp.y));
				}
				else { ; }

			else if (cp.x < monsterP.x)
				if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
					sprite->setPosition(Vec2(cp.x - 5, cp.y));
				}
				else { ; }
		}
		else
		{
			if (cp.y - screenO.y > screenSize2.height / 4 )
			{
				sprite->setPosition(Vec2(cp.x , cp.y - delta * speed));
				log("yes");
			}
			else
			{
				sprite->setPosition(Vec2(cp.x , cp.y - delta * speed));
				this->setPosition(Vec2(this->getPosition().x , this->getPosition().y + delta * speed));
				screenO.y -= delta * speed;
			}
		}
			//sprite->setPositionY(sprite->getPositionY() - delta * speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)
		){//&& sprite->getPositionY() <= screenSize2.height) {
		cp = sprite->getPosition();
		updateCL();
		PandS hitted = cheakCL(cp.x , cp.y + delta* speed, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			//auto remove = RemoveSelf::create();
			//hittedSprite->runAction(remove);
			log("no");
			auto monsterP = hittedSprite->getPosition();
			auto monsterS = hittedSprite->getContentSize();
			int mwith = hittedSprite->getScale()*monsterS.width;
			int mheig = monsterS.height*hittedSprite->getScale();
			hittedSprite->runAction(remove);

			if (cp.x > monsterP.x)
				if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
					sprite->setPosition(Vec2(cp.x + 5, cp.y));
				}
				else { ; }

			else if (cp.x < monsterP.x)
				if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
					sprite->setPosition(Vec2(cp.x - 5, cp.y));
				}
				else { ; }
		}
		else
			if (cp.y - screenO.y < screenSize2.height *3/ 4)
			{
				sprite->setPosition(Vec2(cp.x, cp.y + delta * speed));
				log("yes");
			}
			else
			{
				sprite->setPosition(Vec2(cp.x, cp.y + delta * speed));
				this->setPosition(Vec2(this->getPosition().x, this->getPosition().y - delta * speed));
				screenO.y += delta * speed;
			}
			//sprite->setPositionY(sprite->getPositionY() + delta * speed);

	}
#if 0
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {

		auto bullet = Sprite::create("CloseNormal.png");

		auto startPos = sprite->getPosition() + Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(1000, 0);

		//ennPos is equal to the sum of startPos and bullet distance.

		auto duration = (endPos.x - startPos.x) / 1000;

		bullet->setPosition(sprite->getPosition() + Point(sprite->getContentSize().width / 10, 0));

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);

		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));

	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {

		auto bullet = Sprite::create("CloseNormal.png");

		auto startPos = sprite->getPosition() - Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(-1000, 0);

		auto duration = (startPos.x - endPos.x) / 1000;

		bullet->setPosition(sprite->getPosition() - Point(sprite->getContentSize().width / 10, 0));

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {

		auto bullet = Sprite::create("CloseNormal.png");

		auto startPos = sprite->getPosition() + Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, 1000);

		auto duration = (endPos.y - startPos.y) / 1000;

		bullet->setPosition(sprite->getPosition() - Point(0, sprite->getContentSize().height / 10));

		this->addChild(bullet);

		auto fire = MoveTo::create(duration,endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {

		auto bullet = Sprite::create("CloseNormal.png");

		auto startPos = sprite->getPosition() - Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, -1000);

		auto duration = (startPos.y - endPos.y) / 1000;

		bullet->setPosition(sprite->getPosition() + Point(0, sprite->getContentSize().height / 10));

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
#endif
}

void GameStartPage::fire(float dt) {
	auto sprite = this->getChildByName("playerl")->getChildByTag(10);

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		//auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() - Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, -500);

		auto duration = (startPos.y - endPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		//auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, 500);

		auto duration = (endPos.y - startPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		//auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(500, 0);

		auto duration = (endPos.x - startPos.x) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		//auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() - Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(-500, 0);

		auto duration = (startPos.x - endPos.x) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
}


void GameStartPage::initCL()
{
	Vector<Node*> childList = this->getChildren();

	for (Node* i : childList)
	{
		//if it is player
		if (i->getTag() == 1)
			continue;
		//if it is monster or box
		else if (i->getTag() == 2)
		{
			PandS vampire;
			vampire.name = i->getName();
			vampire.x = i->getPosition().x;
			vampire.y = i->getPosition().y;
			vampire.height = i->getContentSize().height*i->getScale();
			vampire.width = i->getContentSize().width*i->getScale();
			cl.changed.push_back(vampire);
			//cl.changed.
		}
		//if it is wall
		else if (i->getTag() == 3)
		{
			PandS wall;
			wall.name = i->getName();
			wall.x = i->getPosition().x;
			wall.y = i->getPosition().y;
			wall.height = i->getContentSize().height*i->getScale();
			wall.width = i->getContentSize().width*i->getScale();
			cl.fixed.push_back(wall);
		}
		for (PandS i : cl.changed)
		{
			log("mx %f", i.x);
			log("my %f", i.y);
			log("mw %d", i.width);
			log("mh %d", i.height);
		}
	}
}

void GameStartPage::updateCL()
{
	cl.changed.clear();
	Vector<Node*> childList = this->getChildren();
	for (Node* i : childList)
	{
		//if it is monster or box
		if (i->getTag() == 2)
		{
			PandS vampire;
			vampire.name = i->getName();
			vampire.x = i->getPosition().x;
			vampire.y = i->getPosition().y;
			vampire.height = i->getContentSize().height*i->getScale();
			vampire.width = i->getContentSize().width*i->getScale();
			cl.changed.push_back(vampire);
			//cl.changed.push_back
			//cl.changed.
		}
	}
}

PandS GameStartPage::cheakCL(float x1, float y1, int w1, int h1)
{
	/*auto cp = sprite->getPosition();
	auto playerP = sprite->getPosition();
	auto playerS = sprite->getContentSize();
	int pwith = sprite->getScale()*playerS.width;
	int pheig = playerS.height*sprite->getScale();*/
	PandS tem;
	tem.height = -1;
	tem.name = "-1";
	tem.width = -1;
	tem.x = -1;
	tem.y = -1;
	for (PandS i : cl.changed)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{
			log("mx %f", i.x);
			log("my %f", i.y);
			log("mw %d", i.width);
			log("mh %d", i.height);
			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	return tem;
}