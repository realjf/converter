#pragma once

extern Converter::Application* Converter::CreateApplication();

int main(int argc, char** argv) {
    Converter::Log::Init();

    auto app = Converter::CreateApplication();

    app->Run(argc, argv);

    delete app;

    return 0;
}
