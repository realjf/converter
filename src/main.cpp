#include <CLI/CLI.hpp>
#include <map>
#include <functional>
#include <iostream>

enum class Converter : int { EPUB_TO_PDF };

constexpr const char* ConverterToString(Converter converter) throw() {
    switch (converter) {
        case Converter::EPUB_TO_PDF:
            return "0";
        default:
            return "0";
    }
}

int main(int argc, char** argv) {
    CLI::App app{"a ebook converter"};

#ifdef _WIN32
    // allow /a, /f filename, /long, /file filename, /file:filename
    app.allow_windows_style_options();
#endif

    std::string input_file = "";
    CLI::Option* opt1 = app.add_option("-f,--file", input_file, "Filename to convert");
    if (opt1 != NULL) {
        if (!opt1->check(CLI::ExistingFile)) {
            return -1;
        }
    }
    std::string output = "";
    CLI::Option* opt2 = app.add_option("-o,--output", output, "Output filename");
    std::string input_directory = "";
    CLI::Option* opt3 = app.add_option("-d,--dir", input_directory, "Specify a directory that contains ebook file to convert");

    Converter converter{Converter::EPUB_TO_PDF};
    std::map<std::string, Converter> converter_map{{"epub_to_pdf", Converter::EPUB_TO_PDF}};
    CLI::Option* opt4 = app.add_option("-c,--converter", converter, "converter settings");
    std::function<std::string()> default_converter_func = []() { return ConverterToString(Converter::EPUB_TO_PDF); };
    opt4->default_function(default_converter_func);
    opt4->transform(CLI::CheckedTransformer(converter_map, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);

    // start to convert

    return 0;
}