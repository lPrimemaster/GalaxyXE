#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../Models/model.h"
#include "../Models/loader.h"

class ModelManager
{
private:
	typedef std::map<std::string, std::map<std::string, Model*>> GXE_Model_Buffer; // make this a double map <--
	typedef std::map<std::string, std::vector<std::string>> GXE_Loc_Buffer;

public:
	ModelManager() = default;
	~ModelManager();

	void createModelType(const std::string& identifier);
	void deleteModelType(const std::string& identifier);

	//Use with caution - Deletes all data from the RAM - CPU won't be able to access it directly. VRAM should stay intact after this.
	void deleteAllData();

	void loadModels();

	GXE_Model_Buffer& operator()()
	{
		return buffer;
	}

	GXE_Loc_Buffer& paths()
	{
		return loc;
	}

private:
	GXE_Model_Buffer buffer;
	GXE_Loc_Buffer loc;
	Loader loader; //VRAM POINTERS LIVE HERE. DO NOT ERASE AT ANY CIRCUMSTANCE!

};

