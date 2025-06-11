#include <iostream>
#include "common/detached_tasks.h"
#include "common/settings.h"

#include "core/core.h"

#include "core/frontend/applets/default_applets.h"
#include "core/frontend/framebuffer_layout.h"
#include "input_common/main.h"
#include "network/network.h"
#include "video_core/gpu.h"
#include "video_core/renderer_base.h"

#include "citra_emc/gles_emu_window/emu_window_sdl2.h"
#include "citra_emc/gles_emu_window/emu_window_sdl2_gl.h"

void LaunchEmcFrontend(int argc, char** argv) {
    std::cout << "Welcome to Azahar" << std::endl;

    Common::DetachedTasks detached_tasks;

    Common::Log::Initialize();
    Common::Log::Start();

    std::cout << "Logging inititialized" << std::endl;

    std::string filepath = "rom.3ds";

    auto& system = Core::System::GetInstance();

    Frontend::RegisterDefaultApplets(system);


    std::cout << "Created system and registered default applets" << std::endl;

    EmuWindow_SDL2::InitializeSDL2();

    std::cout << "SDL Initialized" << std::endl;

    const auto create_emu_window = [&](bool fullscreen,
                                       bool is_secondary) -> std::unique_ptr<EmuWindow_SDL2> {
        return std::make_unique<EmuWindow_SDL2_GL>(system, fullscreen, is_secondary);
    };

    const auto emu_window{create_emu_window(true, false)};

    std::cout << "Created window" << std::endl;

    const auto scope = emu_window->Acquire();

    const Core::System::ResultStatus load_result{system.Load(*emu_window, filepath, nullptr)};

    std::cout << "Loaded ROM" << std::endl;

    switch (load_result) {
    case Core::System::ResultStatus::ErrorGetLoader:
        std::cout << "Failed to obtain loader for " << filepath << std::endl;

        LOG_CRITICAL(Frontend, "Failed to obtain loader for {}!", filepath);
        exit(-1);
    case Core::System::ResultStatus::ErrorLoader:
        std::cout << "Failed to load ROM!" << std::endl;

        LOG_CRITICAL(Frontend, "Failed to load ROM!");
        exit(-1);
    case Core::System::ResultStatus::ErrorLoader_ErrorEncrypted:
        std::cout << "The application that you are trying to load must be decrypted before "
                     "being used with Azahar. \n\n For more information on dumping and "
                     "decrypting applications, please refer to: "
                     "https://web.archive.org/web/20240304210021/https://citra-emu.org/"
                     "wiki/dumping-game-cartridges/"
                  << std::endl;

        LOG_CRITICAL(Frontend,
                     "The application that you are trying to load must be decrypted before "
                     "being used with Azahar. \n\n For more information on dumping and "
                     "decrypting applications, please refer to: "
                     "https://web.archive.org/web/20240304210021/https://citra-emu.org/"
                     "wiki/dumping-game-cartridges/");
        exit(-1);
    case Core::System::ResultStatus::ErrorLoader_ErrorInvalidFormat:
        std::cout << "Error while loading ROM: The ROM format is not supported." << std::endl;

        LOG_CRITICAL(Frontend, "Error while loading ROM: The ROM format is not supported.");
        exit(-1);
    case Core::System::ResultStatus::ErrorNotInitialized:
        std::cout << "CPUCore not initialized" << std::endl;

        LOG_CRITICAL(Frontend, "CPUCore not initialized");
        exit(-1);
    case Core::System::ResultStatus::ErrorSystemMode:
        std::cout << "Failed to determine system mode!" << std::endl;

        LOG_CRITICAL(Frontend, "Failed to determine system mode!");
        exit(-1);
    case Core::System::ResultStatus::Success:
        std::cout << "Loaded Successfully!" << std::endl;

        break; // Expected case
    default:
        std::cout << "Error while loading ROM: " << system.GetStatusDetails() << std::endl;

        LOG_ERROR(Frontend, "Error while loading ROM: {}", system.GetStatusDetails());
        break;
    }

    std::thread main_render_thread([&emu_window] { emu_window->Present(); });
    std::atomic_bool stop_run;

    system.GPU().Renderer().Rasterizer()->LoadDefaultDiskResources(
        stop_run, [](VideoCore::LoadCallbackStage stage, std::size_t value, std::size_t total) {
            LOG_DEBUG(Frontend, "Loading stage {} progress {} {}", static_cast<u32>(stage), value,
                      total);
        });

    std::cout << "Loaded Disk Resources. Launching!" << std::endl;

    while (emu_window->IsOpen()) {
        const auto result = system.RunLoop();

        switch (result) {
        case Core::System::ResultStatus::ShutdownRequested:
            emu_window->RequestClose();
            break;
        case Core::System::ResultStatus::Success:
            break;
        default:
            LOG_ERROR(Frontend, "Error in main run loop: {}", result, system.GetStatusDetails());
            break;
        }
    }

    std::cout << "Ending..." << std::endl;

    emu_window->RequestClose();
    main_render_thread.join();

    Network::Shutdown();
    InputCommon::Shutdown();

    system.Shutdown();

    detached_tasks.WaitForAllTasks();

    std::cout << "Bye Bye!" << std::endl;

}
