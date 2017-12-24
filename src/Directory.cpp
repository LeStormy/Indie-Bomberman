/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-17T16:34:00+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:33:45+02:00
 */

#include "Directory.hpp"

Directory::Directory()
{
}

Directory::~Directory()
{
}

std::vector<std::string> Directory::getFiles(const std::string &extension, const std::string &path, bool keepExt) const
{
  DIR       *_dir;
  std::vector<std::string> ret = {};

  if (!(_dir = opendir(path.c_str())))
    return ret;
  struct stat		   dirstat;
  struct dirent   *dirstruct;
  while ((dirstruct = readdir(_dir)) != NULL)
  {
      std::string fullPath(path + dirstruct->d_name);
      if (stat(fullPath.c_str(), &dirstat) == 0)
      {
        if (S_ISREG(dirstat.st_mode))
        {
          std::string file(dirstruct->d_name);
          if (extension == "" ||
              (file.find('.') != std::string::npos
               && file.substr(file.rfind(".")) == extension))
            {
              if (keepExt == false)
                ret.push_back(file.substr(0, file.rfind(".")));
              else
                ret.push_back(file);
            }
        }
      }
  }
  closedir(_dir);
  return ret;
}
