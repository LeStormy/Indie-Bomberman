//
// Created by baptiste on 5/11/17.
//

#ifndef MESHPATHGETTER_HPP
# define MESHPATHGETTER_HPP

#include "Indie.hpp"

struct MeshPathFromEnum
{
  // TODO : Change default value
  template <typename T>
  static const path		getMeshPath(const T, const Indie::Biome = Indie::VOLCANO, const int height = 0);
  template <typename T>
  static const path		getTexturePath(const T, const Indie::Biome biome = Indie::VOLCANO, const int height = 0);
};

#endif // !MESHPATHGETTER_HPP
