#pragma once
#ifndef OPERATORFACTORYTESTUTILITY_H_
#define OPERATORFACTORYTESTUTILITY_H_

#include <string>
#include <typeinfo>
void validateFactoryRegistration(const std::string & opName, const std::type_info &expectedType);

#endif
