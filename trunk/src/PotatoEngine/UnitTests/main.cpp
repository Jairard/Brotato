#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <Core/compil.hpp>

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);
#ifdef POT_COMPILER_MSC
	system("pause");
#endif
	return result;
}

/*
TODO:
- Core/Tools
- Core/Transform
- Core/Vector2
- Stem
- PotatoDNA
*/
