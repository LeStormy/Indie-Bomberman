/**
 * @Author: Raphael Betrand <raph>
 * @Date:   2017-05-23T11:27:46+02:00
 * @Email:  raphael.beltrand@epitech.eu
 * @Last modified by:   raph
 * @Last modified time: 2017-06-07T18:37:58+02:00
 */

#ifndef WARNING_HPP_
# define WARNING_HPP_

#include <functional>
#include "ErrorMessage.hpp"
#include "Core.hpp"

template<typename T, typename U>
class Warning : public APopUp {
public:
    Warning(const std::function<void(T)> &fct1, const std::function<void(U)> &fct2, T arg1, U arg2,
            const std::string &message = "Something went wrong", const bool ok = true, const bool dismiss = false)
            : okFct(fct1), dismissFct(fct2), _args1(arg1), _args2(arg2) {
        this->init(message, ok, dismiss);
    }
    void Ok() const { okFct(_args1); }
    void Dismiss() const { dismissFct(_args2); }

private:
    const std::function<void(T)> okFct;
    const std::function<void(U)> dismissFct;
    T                            _args1;
    U                            _args2;
};

class Alert : public std::exception, public APopUp {
public:
    Alert(const std::string& msg) : msg_(msg) { /*this->init(msg);*/ }
    virtual ~Alert() throw (){}
    void Ok() const { }
    void Dismiss() const { }
    virtual const char* what() const throw (){
       return msg_.c_str();
    }

private:
    std::string msg_;
};

class MessagePop : public APopUp {
public:
  MessagePop(const std::string &msg) {
    this->init(msg, false, false, IMAGE("DarkFilterPopUp"));
  }
  virtual ~MessagePop() { };
  void Ok() const { }
  void Dismiss() const { }
};


#endif
