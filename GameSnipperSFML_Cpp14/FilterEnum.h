#pragma once
#include <map>

enum _entityCategory {
	TILE = 0x0001,
	ENEMY = 0x0002,
	PLAYER = 0x0004,
	OBJECT = 0x0008,
};





class FilterEnum
{
public:
	FilterEnum() {};
	~FilterEnum() {};
	
	static unsigned short getValue(std::string val)
	{

		std::map<std::string, short>::iterator it;
		it = vcreate_map.find(val);
		if (it != vcreate_map.end()) {
		
		return	static_cast<unsigned short>(it->second);
		}

	}
	typedef  std::map<std::string, short> create_map;
	static create_map vcreate_map;
private:





};





