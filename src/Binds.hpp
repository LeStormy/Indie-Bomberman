/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T16:57:53+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-07T18:48:14+02:00
 */



//
// Created by baptiste on 5/18/17.
//

#ifndef WURTZ_TIERS_BINDS_HPP
#define WURTZ_TIERS_BINDS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "Input.hpp"
#include "Indie.hpp"

class Binds {
public:
  Binds() : _fileName("../Misc/Bind/bind.txt") {
    _bindFile = getFileContents();
	if (_bindFile.length() < 20)
	{
		// Message d'erreur : Back To Default ? Set Bind ?
	}
  }

  ~Binds() {
    std::ofstream out(_fileName, std::ios::out | std::ios::binary);

    if (out) {
      out << _bindFile.c_str();
      out.close();
    }
  }

  void        bind(irr::EKEY_CODE key, uint8_t playerId, Indie::ActionPlayer keyType) {
    _bindFile[5 * playerId + static_cast<uint8_t>(keyType)] = static_cast<uint8_t>(key);
  }

  std::array<KeyMap, 4>        getKeyMapBinding() {
    std::array<KeyMap, 4>   keyMap;

    for (uint8_t i = 0; i < keyMap.size(); i++) {
      int j = i * 5;
      keyMap[i].up = static_cast<irr::EKEY_CODE>(_bindFile[j++]);
      keyMap[i].down = static_cast<irr::EKEY_CODE>(_bindFile[j++]);
      keyMap[i].right = static_cast<irr::EKEY_CODE>(_bindFile[j++]);
      keyMap[i].left = static_cast<irr::EKEY_CODE>(_bindFile[j++]);
      keyMap[i].action = static_cast<irr::EKEY_CODE>(_bindFile[j++]);
    }
    return (keyMap);
  }


private:
  std::string getFileContents()
  {
    std::ifstream in(_fileName, std::ios::in | std::ios::binary);
    if (in)
    {
      std::string contents;
      in.seekg(0, std::ios::end);
      contents.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&contents[0], contents.size());
      in.close();
      return(contents);
    }
    throw std::runtime_error(_fileName + " can't be opened.");
  }

private:
  std::string     _fileName;
  std::string     _bindFile;
};


#endif //WURTZ_TIERS_BINDS_HPP
