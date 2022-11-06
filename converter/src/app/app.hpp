#pragma once

#include "core/core.hpp"

int main(int argc, char** argv);

namespace Converter {

    class Application {
       public:
        Application();
        virtual ~Application();

        inline static Application& Get() { return *s_Instance; }

        void Close();

        void Run(int argc, char** argv);

       private:
        bool m_Running = true;

       private:
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication();
}  // namespace Converter