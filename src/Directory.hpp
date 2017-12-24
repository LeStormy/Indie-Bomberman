/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-17T16:34:40+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:32:48+02:00
 */

#ifndef DIRECTORY_HPP_
# define DIRECTORY_HPP_

#ifdef  linux
#include <dirent.h>
#endif

#ifdef  _WIN32
#include <windirent.h>
#endif

#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <string>

class Directory {
public:
  Directory();
  ~Directory();

  std::vector<std::string> getFiles(const std::string &extension, const std::string &path, bool keepExt) const;

private:
};

#endif
