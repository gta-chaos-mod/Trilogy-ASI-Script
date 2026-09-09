#include "IPC.h"

#include "EffectHandler.h"

#include <libsharedmemory/libsharedmemory.hpp>

void
IPC::Setup ()
{
    std::thread ipc_thread (
        [] ()
        {
            lsm::SharedMemoryQueue reader{"ChaosModEffect", 10, 1024, true,
                                          false};

            while (true)
            {
                std::string msg;
                if (reader.dequeue (msg))
                {
                    nlohmann::json json = nlohmann::json::parse (msg);

                    EffectHandler::HandleFunction (json);
                }
            }
        });

    ipc_thread.detach ();
}
