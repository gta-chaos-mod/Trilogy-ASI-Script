// Copyright (c) 2019 Lordmau5
#include "ReloadAutosave.h"

ReloadAutosave::ReloadAutosave(int _duration, std::string _description)
	: EffectPlaceholder(_duration, _description) {}

void ReloadAutosave::Enable() {
	HookHandler::DoLoadAutoSave();
}
