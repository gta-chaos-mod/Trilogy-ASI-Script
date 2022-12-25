#include "util/Config.h"
#include "util/Websocket.h"

#include <CAudioEngine.h>
#include <efsw/efsw.hpp>

class FileUpdateListener : public efsw::FileWatchListener
{
public:
    void
    handleFileAction (efsw::WatchID watchid, const std::string &dir,
                      const std::string &filename, efsw::Action action,
                      std::string oldFilename) override
    {
        if (action != efsw::Actions::Modified) return;
        if (filename != Config::GetConfigFilename ()) return;

        bool previousCCMode = CONFIG_CC_ENABLED;

        Config::ReloadConfig ();

        if (previousCCMode != CONFIG_CC_ENABLED) Websocket::Setup ();

#ifdef GTASA
        AudioEngine.ReportFrontendAudioEvent (AE_FRONTEND_DISPLAY_INFO, 0.0f,
                                              1.0f);
#endif
    }
};