#include "cli.hpp"

namespace Converter {

    enum class Converter_Type : int { EPUB_TO_PDF };

    constexpr const char* ConverterToString(Converter_Type converter) throw() {
        switch (converter) {
            case Converter_Type::EPUB_TO_PDF:
                return "0";
            default:
                return "0";
        }
    }

    Cli::Cli(int argc, char** argv) {
        m_Argc = argc;
        m_Argv = argv;
    }

    void Cli::Init() {
#ifdef _WIN32
        // allow /a, /f filename, /long, /file filename, /file:filename
        m_App.allow_windows_style_options();
#endif

        std::string input_file = "";
        CLI::Option* input_opt = m_App.add_option("-f,--file", input_file, "Filename to convert");
        if (input_opt != NULL) {
            if (!input_opt->check(CLI::ExistingFile)) {
                return Exit(1);
            }
        }
        std::string output = "";
        CLI::Option* output_opt = m_App.add_option("-o,--output", output, "The converted results output path");
        std::string input_directory = "";
        CLI::Option* input_dir_opt = m_App.add_option("-d,--dir", input_directory, "Specify a directory that contains ebook file to convert");

        Converter_Type converter{Converter_Type::EPUB_TO_PDF};
        std::map<std::string, Converter_Type> converter_map{{"epub_to_pdf", Converter_Type::EPUB_TO_PDF}};
        CLI::Option* converter_opt = m_App.add_option("-c,--converter", converter, "converter settings");
        std::function<std::string()> default_converter_func = []() { return ConverterToString(Converter_Type::EPUB_TO_PDF); };
        converter_opt->default_function(default_converter_func);
        converter_opt->capture_default_str()->required()->transform(CLI::CheckedTransformer(converter_map, CLI::ignore_case));

        try {
            (m_App).parse((m_Argc), (m_Argv));
        } catch (const CLI::ParseError& e) {
            return Exit((m_App).exit(e));
        }

        m_Running = true;
        // Todo: start to convert
    }

    void Cli::Run() {
        while (m_Running) {
        }
    }

    void Cli::Exit(int code) {
        m_Running = false;
    }

}  // namespace Converter