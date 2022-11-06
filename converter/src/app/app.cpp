#include "app.hpp"
#include "log/log.hpp"
#include "cli/cli.hpp"

namespace Converter {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        C_CORE_INFO("app created");
    }

    Application::~Application() {
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::Run(int argc, char** argv) {
        while (m_Running) {
            Cli* cli = new Cli(argc, argv);
            cli->Init();
            cli->Run();
            Close();
        }
    }

}  // namespace Converter