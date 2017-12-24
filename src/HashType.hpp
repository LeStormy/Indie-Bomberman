//
// Created by wurtz on 5/31/17.
//

#ifndef INDIESTUDIO_HASHTYPE_HPP
#define INDIESTUDIO_HASHTYPE_HPP

struct EnumClassHash
{
  template <typename T>
  std::size_t operator()(T t) const
  {
    return static_cast<std::size_t>(t);
  }
};

template <typename Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

#endif //INDIESTUDIO_HASHTYPE_HPP
