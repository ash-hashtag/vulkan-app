#include <Application/Application.h>

int main() {

	Application app;
	
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
#ifdef NDEBUG
		std::cin.get();
#endif 
		return EXIT_FAILURE;
	}
	LOGTST("main ended");
#ifdef NDEBUG
	std::cin.get();
#endif 
	
	return EXIT_SUCCESS;
}