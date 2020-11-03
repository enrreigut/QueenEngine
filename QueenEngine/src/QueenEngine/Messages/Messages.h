#pragma once

typedef const char* const msg;

//GLFW
msg g_INIT_WIN_GLFW =						"Initialising GLFW...";
msg g_ERROR_INIT_WIN_GLFW =					"GLFW could not be initialised!";
msg g_INIT_SUCCESS_WIN_GLFW =				"Initialised GLFW!";

//GLEW
msg g_INIT_WIN_GLEW = "Initialising GLEW...";
msg g_ERROR_INIT_WIN_GLEW = "GLEW could not be initialised!";
msg g_INIT_SUCCESS_WIN_GLEW = "Initialised GLEW!";

//Log Manager

msg g_LOG_MAN_INFO_START =					"Log Manager has started... Hello!";
msg g_LOG_MAN_INFO_CREATE =					"Logger with name '{v}' has been created";
msg g_LOG_MAN_INFO_SHUTDOWN =				"Log Manager is shutted down... Bye!";
msg g_LOG_MAN_INFO_DELETE =					"{v} has been deleted";
msg g_LOG_MAN_INFO_DESTROYED=				"Log Manager has been destroyed";

msg g_LOG_MAN_ERROR_ALREADY_STARTED =		"Log Manager has already been started!";
msg g_LOG_MAN_ERROR_NOT_STARTED =			"Log Manager has not been started!";
msg g_LOG_MAN_ERROR_DUPLPICATE =			"There is already a Logger with that name";
msg g_LOG_MAN_ERROR_DELETE_LOGGER =			"Error deleting logger: {v}";
msg g_LOG_MAN_ERROR_DONT_EXIST =			"Logger with name {v} do not exist!";

//Memory Manager
msg g_MEM_MAN_INFO_START =					"Memory Manager has started... Hello!";
msg g_MEM_MAN_INFO_SHUTDOWN=				"Memory Manager is shutted down... Bye!";
msg g_MEM_MAN_INFO_DESTROYED =				"Memory Manager has been destroyed.";

msg g_MEM_MAN_ERROR_ALREADY_STARTED =		"Memory Manager has already been started!";
msg g_MEM_MAN_ERROR_NOT_STARTED =			"Memory Manager has not been started!";

//Window Manager
msg g_WIN_MAN_INFO_START =					"Window  Manager has started... Hello!";
msg g_WIN_MAN_INFO_SHUTDOWN =				"Window  Manager is shutted down... Bye!";
msg g_WIN_MAN_INFO_DESTROYED =				"Window  Manager has been destroyed";

msg g_WIN_MAN_ERROR_ALREADY_STARTED =		"Window  Manager has already been started!";
msg g_WIN_MAN_ERROR_NOT_STARTED =			"Window  Manager has not been started!";
msg g_WIN_MAN_ERROR_DESTROY_ALL_WINDOWS =	"Error destroying all Windows!";

//Window msgs
msg g_WIN_INIT =							"Initialising Window with title: '{v}', width: {v} and height: {v}";
msg g_WIN_INIT_SUCCESS =					"Window Created!";
msg g_WIN_ERROR_INIT =						"Window could not be initialised!";
msg g_WIN_ERROR_DUPLICATE =					"Window with name '{v}' already created";
msg g_WIN_ERROR_NOT_EXIST =					"Window with name '{v}' do not exist";
msg g_WIN_ERROR_UNEXPECTED =				"Unexpected deleting error occcured!";

//Callbacks msgs
msg g_WIN_CALLBACK_RESIZE =					"Window Resize Event: w({v}), h({v})";
msg g_WIN_CALLBACK_KEYINPUT =				"Window Key Event: Keycode {v}: {v}";

//Event Manager
msg g_EVENT_MAN_INFO_START =				"Event Manager has started... Hello!";
msg g_EVENT_MAN_INFO_DESTROYED=				"Event Manager has been destroyed.";
msg g_EVENT_MAN_INFO_SHUTDOWN =				"Event Manager is shutted down... Bye!";

msg g_EVENT_MAN_ERROR_ALREADY_STARTED =		"Event Manager has already been started!";
msg g_EVENT_MAN_ERROR_NOT_STARTED =			"Event Manager has not been started!";

//Input Manager
msg g_INPUT_MAN_INFO_START = "Input Manager has started... Hello!";
msg g_INPUT_MAN_INFO_DESTROYED = "Input Manager has been destroyed.";
msg g_INPUT_MAN_INFO_SHUTDOWN = "Input Manager is shutted down... Bye!";

msg g_INPUT_MAN_ERROR_ALREADY_STARTED = "Input Manager has already been started!";
msg g_INPUT_MAN_ERROR_NOT_STARTED = "Input Manager has not been started!";

//ImGUI Manager
msg g_IMGUI_MAN_INFO_START = "ImGUI Manager has started... Hello!";
msg g_IMGUI_MAN_INFO_SHUTDOWN = "ImGUI Manager is shutted down... Bye!";
msg g_IMGUI_MAN_INFO_DESTROYED = "ImGUI Manager has been destroyed.";

msg g_IMGUI_MAN_ERROR_ALREADY_STARTED = "ImGUI Manager has already been started!";
msg g_IMGUI_MAN_ERROR_NOT_STARTED = "ImGUI Manager has not been started!";

//Renderer Manager
msg g_REN_MAN_INFO_START = "Memory Manager has started... Hello!";
msg g_REN_MAN_INFO_SHUTDOWN = "Memory Manager is shutted down... Bye!";
msg g_REN_MAN_INFO_DESTROYED = "Memory Manager has been destroyed.";

msg g_REN_MAN_ERROR_ALREADY_STARTED = "Memory Manager has already been started!";
msg g_REN_MAN_ERROR_NOT_STARTED = "Memory Manager has not been started!";

msg g_REN_MAN_TRACE_LOADING_SHADER = "Loading shaders : \n\t\t\t\t\t\t{v} \n\t\t\t\t\t\t{v}";

//Scene Manager
msg g_SCN_MAN_INFO_START = "Scene Manager has started... Hello!";
msg g_SCN_MAN_INFO_SHUTDOWN = "Scene Manager is shutted down... Bye!";
msg g_SCN_MAN_INFO_DESTROYED = "Scene Manager has been destroyed.";

msg g_SCN_MAN_ERROR_ALREADY_STARTED = "Scene Manager has already been started!";
msg g_SCN_MAN_ERROR_NOT_STARTED = "Scene Manager has not been started!";