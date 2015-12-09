#include "ZJBatchNode.h"
#include "DataInputStream.h"
NAMESPACE_ZJG_BEGIN
#define kCCDefaultMyColor	ccc3(255,255,255)

ZJBatchNode::ZJBatchNode(void)
{
	m_blendFunc.src = CC_BLEND_SRC;
	m_blendFunc.dst = CC_BLEND_DST;
	
	dic_moduleKeys = NULL;
	dic_textureAtlas = CCDictionary::create();
	CC_SAFE_RETAIN(dic_textureAtlas);

	myColor = kCCDefaultMyColor;
	initConfig = false;
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
}


ZJBatchNode::~ZJBatchNode(void)
{

}

void ZJBatchNode::Clean()
{
	if(dic_moduleKeys > 0)
	{
		dic_moduleKeys->removeAllObjects();
	}

	if(dic_textureAtlas->count() > 0)
	{
		dic_textureAtlas->removeAllObjects();
	}
	
	for(int i = equips.size()-1;i>=0;i--)
	{
		CC_SAFE_DELETE(equips[i]);
	}
	equips.clear();
	map_curequipInfo.clear();
	initConfig = false;
}

void ZJBatchNode::release()
{
	if(this->m_uReference==1)
	{
		if(dic_moduleKeys > 0)
		{
			dic_moduleKeys->removeAllObjects();
		}

		if(dic_textureAtlas->count() > 0)
		{
			dic_textureAtlas->removeAllObjects();
		}
		for(int i = equips.size()-1;i>=0;i--)
		{
			CC_SAFE_DELETE(equips[i]);
		}
		equips.clear();
		map_curequipInfo.clear();
		CC_SAFE_RELEASE(dic_textureAtlas);
		CC_SAFE_RELEASE(dic_moduleKeys);
	}
	CCSpriteBatchNode::release();
}

void ZJBatchNode::changeEquip(int orgImgIndex,int equipIndex)
{
	if(map_curequipInfo.size()>0 && equipIndex == 0)
	{
		for(int i=0;i<map_curequipInfo.size();i++)
		{
			if(map_curequipInfo[i]->key == orgImgIndex)
			{
				map_curequipInfo.erase(map_curequipInfo.begin()+i);
				return;
			}
		}
	}
	if(orgImgIndex < 0 || equipIndex<=0 ||equips.size() ==0)
	{
		map_curequipInfo.clear();
	}
	else 
	{
		for(int i=0;i<equips.size();i++)
		{
			if(equips[i]->key == orgImgIndex)
			{
				if(equipIndex <= 0 || equipIndex>=equips[i]->equipinfo.size())
				{
					//map_curequipInfo.clear();
					return;
				}
				equips[i]->changeID = equipIndex; 
				//map_curequipInfo.clear();
				//map_curequipInfo.push_back(equips[i]->equipinfo[0]);
				//map_curequipInfo.push_back(equips[i]->equipinfo[equipIndex]);
				map_curequipInfo.push_back(equips[i]);
				break;
			}
		}
	}
}

void ZJBatchNode::draw(void)
{
	CC_NODE_DRAW_SETUP();
	ccGLBlendFunc( m_blendFunc.src, m_blendFunc.dst );
}

CCTextureAtlas* ZJBatchNode::getTextureAtlas(int moduleID,int textureid)
{
	CCTextureAtlas* tex = NULL;
	char key[64];

	if(!this->map_curequipInfo.empty())
	{
		int index = -1;
		for(int i=0;i<this->map_curequipInfo.size();i++)
		{
			for(int j=0;j<map_curequipInfo[i]->equipinfo[0].size();j++)
			{
				if(map_curequipInfo[i]->equipinfo[0][j]== moduleID)
				{
					moduleID =this->map_curequipInfo[i]->equipinfo[map_curequipInfo[i]->changeID][j];
					break;
				}
			}
			
		}
	}

	memset(key,0,sizeof(key));
	sprintf(key,"%d.single",textureid);
	tex = (CCTextureAtlas*)dic_textureAtlas->objectForKey(key);
	if(tex != NULL){
		return tex;
	}
	CC_SAFE_DELETE(tex);
	if(dic_moduleKeys == NULL)
	{
		return NULL;
	}
	CCString* moduleKey =  (CCString*)dic_moduleKeys->objectForKey(moduleID);
	if(moduleKey == NULL)return NULL;
	return (CCTextureAtlas*)dic_textureAtlas->objectForKey(moduleKey->m_sString);
}

void ZJBatchNode::setTextureAlas_singlePng(CCTexture2D *texture,string key)
{
	if(dic_textureAtlas->objectForKey(key) == NULL)
	{
		CCTextureAtlas* textureAtlas = CCTextureAtlas::createWithTexture(texture,2);
		dic_textureAtlas->setObject(textureAtlas,key);
	}
}
void ZJBatchNode::setTextureAlas(CCTexture2D *texture,string key,int binFileIndex)
{
	if(dic_textureAtlas->objectForKey(key) == NULL)
	{
		CCTextureAtlas* textureAtlas = CCTextureAtlas::createWithTexture(texture,2);
		dic_textureAtlas->setObject(textureAtlas,key);
	    //¼ÓÔØÅäÖÃÎÄ¼þ
		if(!initConfig)
		{
			initConfig = true;
			dic_moduleKeys = CCDictionary::create();
			CC_SAFE_RETAIN(dic_moduleKeys);

			char str[64];
			memset(str,0,sizeof(str));
			sprintf(str,"resource/%d.bin",binFileIndex);
			std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
			DataInputStream* dis = DataInputStream::openFile(fullPath.c_str(),"rb");
			int count = dis->readInt();
			for(int i = 0;i<count;i++)
			{
				dis->readString();
			}
			for(int i = 0;i<count;i++)
			{	
				CCString* key = CCString::create(dis->readString());
				int pCount = dis->readInt();
				for(int j=0;j<pCount;j++)
				{
					int PName = dis->readInt();
					if(dic_moduleKeys->objectForKey(PName) ==NULL)
					{
						dic_moduleKeys->setObject(key,PName);
					}
				}
			}
			DataInputStream::closeFile(dis);
		}
	}
}

void ZJBatchNode::removeAllChildrenWithCleanup(bool cleanup)
{
	CCNode::removeAllChildrenWithCleanup(cleanup);
}
NAMESPACE_ZJG_END