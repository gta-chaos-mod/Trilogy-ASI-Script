#pragma once

#include <filesystem>

#include "plugin.h"

#include "cpptoml.h"

class Config
{
private:
	static std::shared_ptr<cpptoml::table> config;

public:
	static void Init();

	template <class T>
	static T GetOrDefault(std::string key, T default_val) {
		if (!config) {
			return default_val;
		}

		return config->get_qualified_as<T>(key).value_or(default_val);
	}
};
