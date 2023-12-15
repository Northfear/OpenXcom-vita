/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <sstream>
#include "version.h"
#include "Engine/Logger.h"
#include "Engine/CrossPlatform.h"
#include "Engine/Game.h"
#include "Engine/Options.h"
#include "Menu/StartState.h"

#ifdef __vita__
#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>

int _newlib_heap_size_user = 275 * 1024 * 1024;

void *memcpy(void *destination, const void *source, size_t n)
{
	return sceClibMemcpy(destination, source, n);
}

void *memset(void *destination, int c, size_t n)
{
	return sceClibMemset(destination, c, n);
}

void *memmove(void *destination, const void *source, size_t n)
{
	return sceClibMemmove(destination, source, n);
}

int memcmp(const void *arr1, const void *arr2, size_t n)
{
	return sceClibMemcmp(arr1, arr2, n);
}
#endif

/** @mainpage
 * @author OpenXcom Developers
 *
 * OpenXcom is an open-source clone of the original X-Com
 * written entirely in C++ and SDL. This documentation contains info
 * on every class contained in the source code and its public methods.
 * The code itself also contains in-line comments for more complicated
 * code blocks. Hopefully all of this will make the code a lot more
 * readable for you in case you which to learn or make use of it in
 * your own projects, though note that all the source code is licensed
 * under the GNU General Public License. Enjoy!
 */

using namespace OpenXcom;

// Crash handling routines
#ifdef _MSC_VER
#include <windows.h>
LONG WINAPI crashLogger(PEXCEPTION_POINTERS exception)
{
	CrossPlatform::crashDump(exception, "");
	return EXCEPTION_CONTINUE_SEARCH;
}
#else
#include <signal.h>
void signalLogger(int sig)
{
	CrossPlatform::crashDump(&sig, "");
	exit(EXIT_FAILURE);
}

#include <exception>
void exceptionLogger()
{
	static bool logged = false;
	std::string error;
	try
	{
		if (!logged)
		{
			logged = true;
			throw;
		}
	}
	catch (const std::exception &e)
	{
		error = e.what();
	}
	catch (...)
	{
		error = "Unknown exception";
	}
	CrossPlatform::crashDump(0, error);
	abort();
}
#endif

Game *game = 0;

// If you can't tell what the main() is for you should have your
// programming license revoked...
int main(int argc, char *argv[])
{
#ifdef _MSC_VER
	// Uncomment to check memory leaks in VS
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	SetUnhandledExceptionFilter(crashLogger);
	// Uncomment to debug crash handler
	// AddVectoredContinueHandler(1, crashLogger);
#else
	signal(SIGSEGV, signalLogger);
	std::set_terminate(exceptionLogger);
#endif

	CrossPlatform::getErrorDialog();

#ifndef NDEBUG
	Logger::reportingLevel() = LOG_DEBUG;
#else
	Logger::reportingLevel() = LOG_INFO;
#endif

#ifdef __vita__
	scePowerSetArmClockFrequency(444);
	scePowerSetBusClockFrequency(222);
	scePowerSetGpuClockFrequency(222);
	scePowerSetGpuXbarClockFrequency(166);

	char *vitaArgv[7];
	vitaArgv[1] = "-data";
	vitaArgv[2] = "ux0:data/OpenXcom/";
	vitaArgv[3] = "-user";
	vitaArgv[4] = "ux0:data/OpenXcom/";
	vitaArgv[5] = "-cfg";
	vitaArgv[6] = "ux0:data/OpenXcom/";
	argv = vitaArgv;
	argc = 7;
#endif

	if (!Options::init(argc, argv))
		return EXIT_SUCCESS;
	std::ostringstream title;
	title << "OpenXcom " << OPENXCOM_VERSION_SHORT << OPENXCOM_VERSION_GIT;
	if (Options::verboseLogging)
		Logger::reportingLevel() = LOG_VERBOSE;
	Options::baseXResolution = Options::displayWidth;
	Options::baseYResolution = Options::displayHeight;

	game = new Game(title.str());
	State::setGamePtr(game);
	game->setState(new StartState);
	game->run();

	// Comment this for faster exit.
	delete game;
#ifdef __vita__
	sceKernelExitProcess(0);
#endif
	return EXIT_SUCCESS;
}


#ifdef __MORPHOS__
const char Version[] = "$VER: OpenXCom " OPENXCOM_VERSION_SHORT " (" __AMIGADATE__  ")";
#endif
