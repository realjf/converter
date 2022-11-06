#include "converter.hpp"
#include "core/entry_point.hpp"

namespace Converter {

    class ConvCli : public Application {
       public:
        ConvCli() : Application() {
        }

        virtual ~ConvCli() = default;
    };

    Application* CreateApplication() {
        return new ConvCli();
    }
}  // namespace Converter
