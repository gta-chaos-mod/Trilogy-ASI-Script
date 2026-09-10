#include "IPC.h"

#include "Websocket.h"

#include <libsharedmemory/libsharedmemory.hpp>

void
IPC::Setup ()
{
    std::thread ipc_thread (
        [] ()
        {
            std::unique_ptr<lsm::SharedMemoryQueue> reader;

            // Connect to reader
            while (!reader)
            {
                try
                {
                    reader = std::make_unique<lsm::SharedMemoryQueue> (
                        "ChaosModEffect", 10, 1024, false, false);
                }
                catch (...)
                {
                    std::this_thread::sleep_for (
                        std::chrono::milliseconds (500));
                }
            }

            // Read messages
            while (true)
            {
                std::string msg;
                if (reader->dequeue (msg))
                {
                    Websocket::CallFunction (msg);
                }
                else
                {
                    std::this_thread::sleep_for (
                        std::chrono::milliseconds (10));
                }
            }
        });

    ipc_thread.detach ();
}
