extern "C"
{
#include "Global.h"
#include "List.h"
}



int main()
{
	int asdf = 324;
	int fdas = 432;
	List test1 = { .Data = (void*)asdf, .ElementSize = 34, .ItemCount = 23, .Capacity = 234};
	List test2 = { .Data = (void*)fdas, .ElementSize = 64, .ItemCount = 13, .Capacity = 734 };

	GameEngine_CreateGraphicsWindow("Game", 1280, 720);

	List list;
	List_StartUp(&list, sizeof(testing));
	List_Add(&list, &test1);
	List_Add(&list, &test2);
	List_Add(&list, &test1);
	List_Add(&list, &test2);
	List_Add(&list, &test1);

	List index0 = *(List*)List_Get(&list, 0);
	List index1 = *(List*)List_Get(&list, 1);
	List index2 = *(List*)List_Get(&list, 2);
	List index3 = *(List*)List_Get(&list, 3);
	List index4 = *(List*)List_Get(&list, 4);

	while (global.Window.Event.type != SDL_QUIT)
	{
		GameEngine_PollEvents();
		if (global.Keyboard.KeyPressed[INPUTKEY_Z] == KS_Held)
		{
			int a = 234;
		}
		//int width = 0, height = 0;
		//glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//while (width == 0 || height == 0) {
		//	glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//	glfwWaitEvents();
		//}
	}

	//SDL_GameControllerClose();
	GameEngine_DestroyWindow();
	return 0;
}

