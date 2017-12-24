/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T16:57:53+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T22:51:50+02:00
 */

#include "Core.hpp"
#include "FileChecker.hpp"

#ifdef  linux
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main()
{
  const char *homedir;

  std::srand(std::time(NULL));

  if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
  }

  Core core;
  Core::AssetsDir = std::string(homedir) + "/.local/Indie";

	FileChecker fc;
	if (!fc.checkAllFiles())
    std::cerr << "Missing Files!!" << std::endl;

  core.run();
  return (0);
}
#endif

#ifdef  _WIN32
#include <Windows.h>
#include <Shlobj.h>
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	Core core;

  std::srand(static_cast<size_t>(std::time(NULL)));

	WCHAR path[256];
	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
    std::wstring home(path);
    Core::AssetsDir = std::string(home.begin(), home.end()) + "\\Indie";
  }

	FileChecker fc;
	if (!fc.checkAllFiles())
  {
    std::cerr << "Missing Files!" << std::endl;
    return 1;
  }
  core.run();
  return (0);
}

#endif
