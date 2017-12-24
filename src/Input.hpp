/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-18T16:57:53+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-16T19:54:18+02:00
 */



//
// Created by baptiste on 5/12/17.
//

#ifndef WURTZ_TIERS_INPUT_HPP
#define WURTZ_TIERS_INPUT_HPP

#include <irrlicht/irrlicht.h>
#include <irrlicht/IEventReceiver.h>
#include <array>

/* A modifier */
struct KeyMap
{
//    KeyMap(std::array<irr::EKEY_CODE, 5> keyBind) : up(keyBind[0]), down(keyBind[1]), right(keyBind[2]), left(keyBind[3]), action(keyBind[4]) {}

  inline bool isIn(const irr::EKEY_CODE key) const { return (key == (up || down || right || left || action)); }

  irr::EKEY_CODE    up;
  irr::EKEY_CODE    down;
  irr::EKEY_CODE    left;
  irr::EKEY_CODE    right;
  irr::EKEY_CODE    action;
};

class Input : public irr::IEventReceiver
{
  public:
    Input(const std::array<KeyMap, 4> &playerKeyMap);
    Input(const Input &cpy) = delete;
    virtual ~Input() = default;
    Input &operator=(const Input &cpy) = delete;

  public:
    virtual bool                    OnEvent(const irr::SEvent& event);
    std::array<bool, 5>             getPlayerAction(const uint8_t id) const;

    void			changeKeys(const std::array<KeyMap, 4> &);

private:
    bool                            _key[irr::KEY_KEY_CODES_COUNT] = {0};
    std::array<KeyMap, 4>     _playerKeyMap;
};

#endif //WURTZ_TIERS_INPUT_HPP
