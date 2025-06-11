#include <iostream>
#include "core/core.h"
// #include "core/dumping/backend.h"
// #include "core/dumping/ffmpeg_backend.h"
#include "core/frontend/applets/default_applets.h"
#include "core/frontend/framebuffer_layout.h"
// #include "core/hle/service/am/am.h"
// #include "core/hle/service/cfg/cfg.h"
// #include "core/movie.h"
#include "input_common/main.h"
// #include "network/network.h"
#include "video_core/gpu.h"
#include "video_core/renderer_base.h"

#include "citra_emc/emu_window_sdl2.h"
#include "citra_emc/emu_window_sdl2_gl.h"

void LaunchEmcFrontend(int argc, char** argv) {
    std::cout << "Welcome to Azahar" << std::endl;


    Common::Log::Initialize();
    Common::Log::Start();

    std::string filepath;

    auto& system = Core::System::GetInstance();

    Frontend::RegisterDefaultApplets(system);

    EmuWindow_SDL2::InitializeSDL2();

    // const auto create_emu_window = [&](bool fullscreen,
    //                                    bool is_secondary) -> std::unique_ptr<EmuWindow_SDL2> {
    //     return std::make_unique<EmuWindow_SDL2_GL>(system, fullscreen, is_secondary);
    // };

    // const auto emu_window{create_emu_window(true, false)};
    // // const auto secondary_window = nullptr;

    // const auto scope = emu_window->Acquire();

    // const Core::System::ResultStatus load_result{system.Load(*emu_window, filepath, nullptr)};

    // switch (load_result) {
    // case Core::System::ResultStatus::ErrorGetLoader:
    //     std::cout << "Failed to obtain loader for " << filepath << std::endl;
    //     exit(-1);
    // case Core::System::ResultStatus::ErrorLoader:
    //     std::cout << "Failed to load ROM!" << std::endl;
    //     exit(-1);
    // case Core::System::ResultStatus::ErrorLoader_ErrorEncrypted:
    //     // LOG_CRITICAL(Frontend,
    //     //              "The application that you are trying to load must be decrypted before "
    //     //              "being used with Azahar. \n\n For more information on dumping and "
    //     //              "decrypting applications, please refer to: "
    //     //              "https://web.archive.org/web/20240304210021/https://citra-emu.org/"
    //     //              "wiki/dumping-game-cartridges/");
    //     exit(-1);
    // case Core::System::ResultStatus::ErrorLoader_ErrorInvalidFormat:
    //     std::cout << "Error while loading ROM: The ROM format is not supported." << std::endl;
    //     exit(-1);
    // case Core::System::ResultStatus::ErrorNotInitialized:
    //     std::cout << "CPUCore not initialized" << std::endl;
    //     exit(-1);
    // case Core::System::ResultStatus::ErrorSystemMode:
    //     std::cout << "Failed to determine system mode!" << std::endl;
    //     exit(-1);
    // case Core::System::ResultStatus::Success:
    //     break; // Expected case
    // default:
    //     std::cout << "Error while loading ROM" << std::endl;
    //     // LOG_ERROR(Frontend, "Error while loading ROM: {}", system.GetStatusDetails());
    //     break;
    // }

    // std::thread main_render_thread([&emu_window] { emu_window->Present(); });
    // std::atomic_bool stop_run;

}
