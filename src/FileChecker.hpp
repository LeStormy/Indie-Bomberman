/**
 * @Author: raph
 * @Date:   2017-06-18T12:41:39+02:00
 * @Last modified by:   raph
 * @Last modified time: 2017-06-18T18:34:57+02:00
 */

#ifndef FILECHECKER_HPP_
# define FILECHECKER_HPP_

#include <iostream>
#include <vector>
#include "Core.hpp"

# define AUDIO_PATH(V) Core::AssetsDir + "/Media/Audio/" + (V)
# define IMG_PATH(V) Core::AssetsDir + "/Media/Images/" + (V)
# define MESH_PATH(V) Core::AssetsDir + "/Media/Mesh/" + (V)
# define TXT_PATH(V) Core::AssetsDir + "/Media/Images/Mesh/" + (V)

class FileChecker {
public:
	FileChecker();
	~FileChecker();

	bool checkAllFiles() const;

private:
	std::vector<std::string> Files;
};

#endif
