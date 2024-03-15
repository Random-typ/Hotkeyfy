#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include "resource.h"

struct config_metadata
{
	uint64_t count : 56;
	uint64_t consume : 1;
	uint64_t reserved : 7;
};

class config
{
public:
	static std::vector<DWORD> getHotkeys(const std::wstring& _action);
	
	static void setHotkeys(const std::wstring& _action, const std::vector<DWORD>& _keys);
	
	// @returns true if successful, false otherwise
	static void load(const std::wstring& _path);

	// @returns true if successful, false otherwise
	static void save();
private:
	static std::map<std::wstring, std::pair<std::vector<DWORD>, config_metadata>> hotkeys;
	static std::wstring path;
};

