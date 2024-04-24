#include "BaseFieldObject.h"

std::list<std::unique_ptr<BaseFieldObject>> BaseFieldObject::manageBaseFieldObjectList;

void BaseFieldObject::ManagerBaseFieldObject(){
	for (std::list<std::unique_ptr<BaseFieldObject>>::iterator itr = manageBaseFieldObjectList.begin(); itr != manageBaseFieldObjectList.end();) {
		BaseFieldObject* obj = (*itr).get();
		if (obj->isDelete) {
			itr = manageBaseFieldObjectList.erase(itr);
			continue;
		}

		obj->Update();
		obj->Draw();
		
		itr++;
	}
}

void BaseFieldObject::Clear(){
	manageBaseFieldObjectList.clear();
}
