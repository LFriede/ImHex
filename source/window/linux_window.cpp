#include "window.hpp"

#if defined(OS_LINUX)

    #include <hex/helpers/utils.hpp>
    #include <nlohmann/json.hpp>
    #include <sys/wait.h>

    namespace hex {

        void Window::initNative() {

        }

        void Window::setupNativeWindow() {
            bool themeFollowSystem = ContentRegistry::Settings::getSetting("hex.builtin.setting.interface", "hex.builtin.setting.interface.color") == 0;
            EventManager::subscribe<EventOSThemeChanged>(this, [themeFollowSystem]{
                if (!themeFollowSystem) return;

                std::array<char, 128> buffer = { 0 };
                std::string result;

                // TODO: In the future maybe support more DEs instead of just GNOME
                FILE* pipe = popen("gsettings get org.gnome.desktop.interface gtk-theme 2>&1", "r");
                if (pipe == nullptr) return;

                while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
                    result += buffer.data();

                auto exitCode = WEXITSTATUS(pclose(pipe));
                if (exitCode != 0) return;

                EventManager::post<RequestChangeTheme>(hex::containsIgnoreCase(result, "dark") ? 1 : 2);
            });

            if (themeFollowSystem)
                EventManager::post<EventOSThemeChanged>();
        }

        void Window::updateNativeWindow() {

        }

        void Window::drawTitleBar() {

        }

    }

#endif