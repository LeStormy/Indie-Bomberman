/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-16T10:52:00+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-05-29T19:49:33+02:00
 */

#ifndef ISCREEN_HPP_
# define ISCREEN_HPP_

#include <iostream>
#include "Indie.hpp"
#include "Settings.hpp"

class IScreen {
public:
  virtual ~IScreen() {}
  virtual void sceneSetter(const Settings &settings) = 0;

private:
};

#endif
