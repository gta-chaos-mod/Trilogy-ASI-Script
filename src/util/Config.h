// Copyright (c) 2019 Lordmau5
#pragma once

#include <filesystem>

#include "common.h"
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

	template <class T>
	static cpptoml::option<std::vector<T>> GetOrDefaultArray(std::string key) {
		if (!config) {
			return cpptoml::option<std::vector<T>>();
		}

		return config->get_qualified_array_of<T>(key);
	}
};
