#include "App.h"

/// <summary>
/// Main loop
/// </summary>
int main()
{
	App* app = new App();
	app->run();
	delete app;

	return 0;
}