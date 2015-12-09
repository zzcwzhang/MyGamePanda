#include "MapList.h"
#include "Atkable/Building.h"
#include "Tower/Footman.h"
#include "GameState.h"



#define kTag_LIFE (10)
#define kTag_LIFE_STRING (20)



MapList::MapList()
{
	mapHP = 100;
	m_tollgate = 0;
}

int MapList::getBossLifeTime(int mapNum)
{
	/*if (mapNum>0)
	{
	CCLog("getBossLifeTime error:mapNum>=0");
	return 0;
	}
	CCLog("mapNum %d",mapNum);*/
	return 0;
}

MapList* MapList::create( int tollgate )
{
	MapList*maplist = new MapList;
	if (maplist && maplist->initMap(tollgate))
	{
		maplist->autorelease();
		return maplist;
	}
	CC_SAFE_DELETE(maplist);
	return NULL;
}

bool MapList::initMap(int tollgate)
{
	m_tollgate = tollgate;
	//CCNode::init();

	char str[256];
	memset(str,0,sizeof(str));
	sprintf(str,"tmx/map%d.tmx",tollgate);
	//瓦片地图;
	tmxMap = CCTMXTiledMap::create(str);
	tmxMap->setAnchorPoint(ccp(0,0));
	tmxMap->setPosition(ccp(0,0));
	this->addChild(tmxMap,-10);
	//背景;
	BGView = CCSprite::create(BGImage1);
	BGView->setAnchorPoint(CCPointZero);
	BGView->setPosition(CCPointZero);
	this->addChild(BGView,-20);

	//测试cells;
	//for (int i = 0;i<cells.size();i++)
	//{
	//	CCRect rect = cells[i]->CellRect;
	//	CCLog("rect %f %f",rect.getMinX(),rect.getMinY());
	//}



	getPointArray();

	return true;
}

void MapList::changeBGView(const char*str)
{
	BGView->initWithFile(str);
}

int MapList::getTowerList( int mapNum,int index )
{
	return 0;
}

int MapList::getBossHP( int mapNum )
{
	if (mapNum>0)
	{
		CCLog("getBossLifeTime error:mapNum>=0");
		return 0;
	}
	CCLog("mapNum %d",mapNum);
	return 0;
}

void MapList::getPointArray()
{
	do 
	{
		CCTMXObjectGroup* group = tmxMap->objectGroupNamed("object");//第一步，获取对象层 ;
		if (!group)
		{
			return;
		}
		else
		{
			/*marke*/
			//pathOfIndex++;
		}
		CCArray* objects = group->getObjects();//获取层上对象集合;

		CCDictionary* dict = NULL; 

		CCObject* pObj = NULL; 
		CCPoint guaidian[MAX_GUAIDIAN];

		for (int i = 0;i<MAX_GUAIDIAN;i++)
		{
			guaidian[i] = ccp(-1,-1);
		}


		///////////////////////////////////////////

		//遍历对象集合中的对象; 
		//创建障碍物;
		//自动设置障碍物Zoder;
		//创建拐点列表，检测跳跃点;
		//设置刷怪点花草;

		CCARRAY_FOREACH(objects, pObj)		
		{ 

			dict = (CCDictionary*)pObj;// 

			if(!dict) 

				break; 

			//读取拐点

			char* key = "waypoint";
			CCString *str = (CCString*)dict->objectForKey(key); 
			if (str)
			{
				int a = atoi(str->getCString());
				key = "x"; 
				float x = ((CCString*)dict->objectForKey(key))->floatValue();
				key = "y"; 
				float y = ((CCString*)dict->objectForKey(key))->floatValue();
				CCPoint ppt = ccp(x,y);

				//先把拐点按顺序存到队列，再加入列表，防止乱序;
				guaidian[a] = ppt ;


				//判断是否为跳跃点;

				key = "jump";

				if ((CCString*)dict->objectForKey(key))
				{
					guaidian[a] = ccp(-x,-y) ;
					//	CCLog("jump point %d",a);

					//addenemy.png
					CCSprite* enemy = CCSprite::createWithSpriteFrameName("addenemy.png");
					enemy->setPosition(ccp(x,y)+ccp(30,30));
					addChild(enemy,5);

					CCRotateBy* rb = CCRotateBy::create(0.5,60);
					enemy->runAction(CCRepeatForever::create(rb));
				}

				key = "jumped";

				if ((CCString*)dict->objectForKey(key))
				{

					//addenemy.png
					CCSprite* enemy = CCSprite::createWithSpriteFrameName("addenemy.png");
					enemy->setPosition(ccp(x,y)+ccp(30,30));
					addChild(enemy,5);

					CCRotateBy* rb = CCRotateBy::create(0.5,-60);
					enemy->runAction(CCRepeatForever::create(rb));
				}		

				//设置花草;
				if (a ==1)
				{
					CCSprite* sp1 = CCSprite::createWithSpriteFrameName("g_start.png");
					sp1->setAnchorPoint(ccp(0,0));
					sp1->setPosition(ppt+ccp(0,0) );
					addChild(sp1,0);
				}

			}

			
			do 
			{
				//可建造格子查询;
				key = "type";
				str = (CCString*)dict->objectForKey(key); 
				if (str)
				{
					int a = atoi(str->getCString());
					if (a ==1)
					{
						key = "x"; 
						float x = ((CCString*)dict->objectForKey(key))->floatValue();
						key = "y"; 
						float y = ((CCString*)dict->objectForKey(key))->floatValue();
						CCPoint ppdraw = ccp(x,y) ;
						int cellNum =(int)(x/ZC_RECTSIZE+(y/ZC_RECTSIZE*9));
						//CCLog("err %d",cellNum);
						/*if (cellNum ==144)
						{
							CCLog("error");
						}*/
						Cell* cel = cells[cellNum];
						cel->curObject = eSpace;
					}	
				}
			} while (0);
			



			//添加障碍物
			key = "obstacle";

			str = (CCString*)dict->objectForKey(key); 
			if (str)
			{
				int a = atoi(str->getCString());

				key = "x"; 

				float x = ((CCString*)dict->objectForKey(key))->floatValue();

				key = "y"; 

				float y = ((CCString*)dict->objectForKey(key))->floatValue();

				key = "obstacle";

				int tsort = ((CCString*)dict->objectForKey(key))->intValue();

				CCPoint ppt = ccp(x,y);

				Building* bud = Building::create(a);
				bud->setPosition(ppt+ccp(ZC_RECTSIZE/2,0));
				bud->setAutoZoder(false);
				addChild(bud);
				bud->sitDownCell();
				// 
				// 				//获取奖励塔信息; 在tilemap 的类型决定塔的种类 -4代表4格障碍，-1代表随机 -2代表炸弹 -3代表空
				// 				CCTMXObjectGroup* group2 =  tmxMap->objectGroupNamed("tower");//第一步，获取对象层 ;
				// 				if (group2)
				// 				{
				// 					CCArray* objects2 = group2->getObjects();//获取层上对象集合;
				// 
				// 					CCDictionary* dict2 = NULL; 
				// 
				// 					CCObject* pObj2 = NULL;
				// 
				// 					CCARRAY_FOREACH(objects2, pObj2)//遍历对象集合中的对象;
				// 					{ 
				// 						dict2 = (CCDictionary*)pObj2;
				// 						if(!dict2) break;
				// 
				// 						char* tkey = "x";
				// 						float tx = ((CCString*)dict2->objectForKey(tkey))->floatValue();
				// 						tkey = "y";
				// 						float ty = ((CCString*)dict2->objectForKey(tkey))->floatValue();
				// 
				// 						if (tx ==x&&ty == y)
				// 						{
				// 							tkey = "type";
				// 							int resort = ((CCString*)dict2->objectForKey(tkey))->intValue();
				// 						
				// 							if (resort!=-4)
				// 							{
				// 								
				// 								obs->setRewardTower(resort);
				// 								CCLog("%f %f %d",tx,ty,resort);
				// 							}
				// 							else if (resort==-4)
				// 							{
				// 
				// 								for (int i = 0;i<4;i++)
				// 								{
				// 									int sortf;
				// 									CCString* keys = CCString::createWithFormat("tower%d",i);
				// 									sortf = ((CCString*)dict2->objectForKey(keys->getCString()))->intValue();
				// 									obs->setRewardTower(sortf,i);
				// 								}
				// 								//obs->rewardTower[3];
				// 								//obs->rewardTower[3];
				// 							}
				// 
				// 						}
				// 					}
				// 				}

			}


			
		} 

		//添加开场闪框;
		/*marke*/
		//addStartFrame();

		//把点排序后加入到容器中;
		for (int i = 1;i<MAX_GUAIDIAN;i++)
		{

			CCPoint cpi = guaidian[i];
			float pix = cpi.x;
			float piy = cpi.y;
			if (pix == -1&&piy == -1)
			{
				break;
			}
			//guailist.push_back(guaidian[i]);
			pvec.push_back(guaidian[i]+ccp(40,0));
		};

		//终点设置生命爱心心心坐标;
		if (m_tollgate>=0) //判断是否为boss关;
		{
			for (int i = 1;i<MAX_GUAIDIAN;i++)
			{
				CCPoint cpi = guaidian[i];
				float pix = cpi.x;
				float piy = cpi.y;
				if (pix == -1&&piy == -1)
				{
					cocos2d::CCPoint endPoint = guaidian[i-1];

					//创建血泉;
					/*marke*/
					addbloodpoor(endPoint);
					break;
				}
			}
		}

	} while (0);

}

void MapList::addbloodpoor( CCPoint poor_Point )
{
	CCSprite* life = CCSprite::createWithSpriteFrameName("life00.png");
	life->setAnchorPoint(ccp(0.5,0.5));
	life->setPosition(poor_Point+ccp(30,60));
	addChild(life,VIEW_HEIGHT-(int)getPositionY(),kTag_LIFE);

	CCString* lc = CCString::createWithFormat("%d",mapHP);
	CCLabelTTF* lblife = CCLabelTTF::create(lc->getCString(),"fonts/Marker Felt.ttf",30);
	lblife->setPosition(ccp(65,60));
	life->addChild(lblife,VIEW_HEIGHT-(int)getPositionY(),kTag_LIFE_STRING);

}

void MapList::hartBloodpoor( int demon_atk )
{
	mapHP -=demon_atk;

	CCLabelTTF* lblife = (CCLabelTTF*)getChildByTag(kTag_LIFE)->getChildByTag(kTag_LIFE_STRING);
	CCString* lc = CCString::createWithFormat("%d",mapHP);
	lblife->setString(lc->getCString());

	if (mapHP <= 0)
	{
		removeAllChildrenWithCleanup(true);
	}

}

Cell* MapList::getTouch( float px, float py )
{

	CCPoint touchPoint = ccp(px,py);

	//遍历所有格子，并根据格子状态决定;
	for (int i = 0;i<cells.size();i++)
	{
		Cell* tcell = cells[i];
		CCRect rect = tcell->CellRect;
		if (rect.containsPoint(touchPoint))
		{
			return tcell;
		}
	}

	return 0;
}

void MapList::update()
{
	////检测所有人血量，清除尸体返回金钱;

	CCObject* obj;
	CCARRAY_FOREACH_REVERSE(Atkable::AtkableArray,obj)
	{
		Atkable* atk = (Atkable*)obj;
		if (atk->getKingdom() == OBJ_MONSTER)
		{
			if (atk->getCurHP()<=0)
			{
				SetSmoke(atk->getMidPoint());
				atk->Destroyed();
				m_game->pay(-14);
				//奖励;
				//changeCoin(14);
				//CCPoint atkpot = atk->getMidPoint();
				//FlyCoin(14,atkpot);
				//SetSmoke(atkpot);
			}
		}
		else if (atk->getKingdom() == OBJ_OBSTACLE)
		{
			if (atk->getCurHP()<=0)
			{
				SetSmoke(atk->getMidPoint());
				atk->Destroyed();
				//奖励;
				int rmoney = atk->getRewardMoney();
				m_game->pay(-100);
				//changeCoin(rmoney);
				//CCPoint atkpot = atk->getMidPoint();
				//FlyCoin(rmoney,atkpot);
				//SetSmoke(atkpot);
			}
		}

	}
}


void MapList::SetSmoke( CCPoint pointed )
{
	CCSprite* smoke = CCSprite::createWithSpriteFrameName("addEnemy1.png"); 	
	smoke->setPosition(pointed);
	smoke->setScale(0.5);
	addChild(smoke,VIEW_HEIGHT-pointed.y);
	CCAnimation* addEnemy = CCAnimationCache::sharedAnimationCache()->animationByName("addEnemy");
	CCAnimate* ade = CCAnimate::create(addEnemy);
	CCSequence* sq2 = CCSequence::create(ade,CCRemoveSelf::create(),NULL);
	smoke->runAction(sq2);
}

MapList::~MapList()
{
	CCLog("~mapList");
	Atkable::AtkableArray->removeAllObjects();
	Shooter::shooterArray->removeAllObjects();
}

