#pragma once
#include <CLI/CLI.hpp>

namespace Converter {
    class Cli {
       private:
        CLI::App m_App{"a ebook converter"};
        int m_Argc;
        char** m_Argv;
        bool m_Running = false;

       public:
        Cli(int argc, char** argv);
        void Init();
        void Run();
        void Exit(int code);
        virtual ~Cli() = default;
    };
}  // namespace Converter